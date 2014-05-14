#include <stdio.h>
#include<string.h>
#include "typedef.h"
#include "host_communication.h"
#include "host_commands.h"
#include "slave.h"

/*uint8_t (*usp_tx)(uint8_t *buff, uint8_t size);
  uint8_t (*usp_rx)(uint8_t *buff, uint8_t size);
  uint8_t (*dwn_tx)(uint16_t command);
  uint8_t (*dwn_rx)( uint8_t *data );*/
t_host_comm host_comm;

/******************************************************************************
 * Function Name : host_RegisterTxRx
 * Description : Register function to send and receive.
 * Argument : none
 * Return Value : none
 ******************************************************************************/
void host_RegisterTxRx(fn down_tx, fn down_rx)
{
	host_comm.dwn_tx = down_tx;
	host_comm.dwn_rx = down_rx;
}

uint32_t host_CommandType(uint32_t command)
{
	uint32_t ret = 0;
	command = command >> 24;
	printf("\ncommandtype %x", command);
	if((command & 0xFF) == MASTER_COMMAND)
		ret = MASTER_COMMAND;
	else if((command & 0xFF) == SLAVE_COMMAND) 
		ret = SLAVE_COMMAND;
	else
		ret = NOT_SUPPORTED;
	return ret;
}

uint32_t host_AnalyzeMasterResponse(uint16_t cmd, uint8_t *response)
{
	uint32_t ret = 0;

	//printf("\nresponse %d %d %d", response[0], response[1], response[2]);
	switch(cmd){
		case ENUMERATE:
			if((response[0] == RESPONSE_1BYTE) && (response[1] == ACK)){
				printf("\nHost Enumerated");
			}
			break;
		case DEVICE_COUNT:
			if((response[0] == RESPONSE_1BYTE) ){
				printf("\nslave count = %d", response[1]);
				set_slave_count(response[1]);
			}
			break;
		default:
			printf("\nNot Supported %d", cmd);
			break;
	}
	return ret;
}
/******************************************************************************
 * Function Name : host_ProcessMasterCommand
 * Description : Function to read data from circular buffer.
 * Argument : none
 * Return Value : none
 ******************************************************************************/

static void host_SendMasterCommand(uint32_t cmd)
{
	static uint8_t command[4];
	static uint8_t response[3];
	uint32_t flag = 1;
	cmd = (cmd & 0xFF0000) >> 16;
	while(flag){
		switch(cmd){
			case ENUMERATE:
				ENUMERATE_CMD(command, 0x0);
				break;
			case DEVICE_COUNT:
				DEVICE_COUNT_CMD(command);
				break;
			default:
				printf("\nNot Supported %d:", cmd);
				break;
		}

		if(host_comm.dwn_tx(command, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
		if(host_comm.dwn_rx(response, HOST_BACKWARD_FRAME_SIZE) != 0){
			fprintf(stderr, "response not received");
			return;
		}

		flag = host_AnalyzeMasterResponse(cmd, response);
		/*	else{
			} 
			}	*/
	}
}

static uint8_t host_SlaveCommand(uint16_t command)
{
	uint8_t cmd;
	command = (command & 0xFF00) >> 8;
	cmd = command;
	if(((cmd >= 144) && (cmd <= 155)) || ((cmd >= 160) && (cmd <= 196))){
		return SLAVE_QUERY_COMMAND;
	}
	else if(((cmd >= 0) && (cmd <= 8)) || ((cmd >= 16) && (cmd <= 31))){
		return SLAVE_DIRECT_ARC_COMMAND;
	}
	else{
		return NOT_SUPPORTED;
	}
}
/******************************************************************************
 * Function Name : host_process_slave_command
 * Description : All slave commands need to be send to downstream device
 * Argument : none
 * Return Value : none
 ******************************************************************************/
static void host_SendSlaveDirectArcCommand(uint8_t add, uint8_t command)
{
		static uint8_t cmd[4];
		cmd[0] = SLAVE_COMMAND;
		cmd[1] = (0 << 7) | (add << 1) | 1;
		cmd[2] = command;
		if(host_comm.dwn_tx(cmd, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
}

/******************************************************************************
 * Function Name : host_process_slave_command
 * Description : All slave commands need to be send to downstream device
 * Argument : none
 * Return Value : none
 ******************************************************************************/
static void host_SendSlaveQueryCommand(uint8_t add, uint8_t command)
{
		static uint8_t cmd[4];
		static uint8_t response[3];
		cmd[0] = SLAVE_COMMAND;
		cmd[1] = (0 << 7) | (add << 1) | 1;
		cmd[2] = command;
		if(host_comm.dwn_tx(cmd, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
		if(host_comm.dwn_rx(response, HOST_BACKWARD_FRAME_SIZE) != 0){
			fprintf(stderr, "response not received");
			return;
		}
}


/******************************************************************************
 * Function Name : host_process_slave_command
 * Description : All slave commands need to be send to downstream device
 * Argument : none
 * Return Value : none
 ******************************************************************************/
static void host_SendSlaveCommand(uint32_t buff)
{
		uint8_t command, add;
		static uint8_t cmd[4];
		add = (buff & 0x0000FF00) >> 8;
		command = (buff & 0x00FF0000) >> 16;
		printf("slave command %x %x", command, add);
		switch(command){
			case DEVICE_MIN:
				DEVICE_MIN_CMD(cmd, add);
				printf("\n cmd0:%x cmd1%x cmd2%x", cmd[0], cmd[1], cmd[2]);
				break;
			case DEVICE_MAX:
				DEVICE_MAX_CMD(cmd, add);
				printf("\n cmd0:%x cmd1%x cmd2%x", cmd[0], cmd[1], cmd[2]);
				break;
			default:
				printf("\n not supported");
				return;
				break;
		}
		if(host_comm.dwn_tx(cmd, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
}
/******************************************************************************
 * Function Name : host_analyze_commdiwand
 * Description : analyze command for slave or master command.
 * Argument : none
 * Return Value : none
 ******************************************************************************/
uint8_t host_AnalyzeCommand(uint32_t cmd)
{
	uint8_t ret = 0;
	uint32_t command = host_CommandType(cmd);

	switch(command){
		case MASTER_COMMAND:
			printf("\nmaster command");
			host_SendMasterCommand(cmd);
			break;
		case SLAVE_COMMAND:
			printf("\nslave command");
			host_SendSlaveCommand(cmd);
			break;
		default:
			printf("\nnot supported command");
			break;
	}
	return ret;
}

/******************************************************************************
 * Function Name : UART1_RxDataCount
 * Description : Function to read data from circular buffer.
 * Argument : none
 * Return Value : none
 ******************************************************************************/


/******************************************************************************
 * Function Name : UART1_RxDataCount
 * Description : Function to read data from circular buffer.
 * Argument : none
 * Return Value : none
 ******************************************************************************/
