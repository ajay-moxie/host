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
		case MASTER_CONFIGURATION_COMMAND:
			if((response[0] == RESPONSE_1BYTE) && (response[1] == ACK)){
				printf("\nConfigured");
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
//	cmd = (cmd & 0xFF0000) >> 16;
	command[0] = 0xaa;
	command[1] = ((cmd & 0xFF0000) >> 16);
	command[2] = (cmd & 0xFF00) >> 8;
	command[3] = (cmd & 0xFF);
	while(flag){
		switch(command[1]){
			case ENUMERATE:
			case DEVICE_COUNT:
			case MASTER_CONFIGURATION_COMMAND:
				break;
			default:
				printf("\nNot Supported %d:", cmd);
				return;
				break;
		}

		if(host_comm.dwn_tx(command, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
		if(host_comm.dwn_rx(response, HOST_BACKWARD_FRAME_SIZE) != 0){
			fprintf(stderr, "response not received");
			return;
		}

		flag = host_AnalyzeMasterResponse(command[1], response);
	}
}

static uint8_t host_SlaveCommand(uint32_t command)
{
	uint8_t cmd;
	uint8_t direct_arch_power;
	direct_arch_power = (command >> 16) & 0x1;
	cmd = (command >> 8) & 0xFF;
	if(direct_arch_power == 0){
		return SLAVE_DIRECT_ARC_COMMAND;
	}
	if(((cmd >= 144) && (cmd <= 155)) || ((cmd >= 160) && (cmd <= 196))){
		return SLAVE_QUERY_COMMAND;
	}
	else if(((cmd >= 0) && (cmd <= 8)) || ((cmd >= 16) && (cmd <= 31))){
		return SLAVE_INDIRECT_ARC_COMMAND;
	}
	else{
		return NOT_SUPPORTED;
	}
}
/******************************************************************************
 * Function Name : host_SendSlaveDirectArcCommand
 * Description : All slave commands need to be send to downstream device
 * Argument : none
 * Return Value : none
 ******************************************************************************/
static void host_SendSlaveDirectArcCommand(uint8_t add, uint8_t command)
{
		static uint8_t cmd[4];
		cmd[0] = SLAVE_COMMAND;
		cmd[1] = (0 << 7) | (add << 1);
		cmd[2] = command;
		if(host_comm.dwn_tx(cmd, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
}
/******************************************************************************
 * Function Name : host_SendSlaveInDirectArcCommand
 * Description : All slave commands need to be send to downstream device
 * Argument : none
 * Return Value : none
 ******************************************************************************/
static void host_SendSlaveInDirectArcCommand(uint8_t add, uint8_t command)
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
		uint32_t reply;
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
		reply = response[1];
		printf("\nresponse = %x", reply);
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
		static uint8_t cmd;
		add = (buff & 0x00FF0000) >> 16;
		add = add >> 1;
		command = (buff & 0x0000FF00) >> 8;
		cmd = host_SlaveCommand(buff);
		switch(cmd){
			case SLAVE_DIRECT_ARC_COMMAND:
				host_SendSlaveDirectArcCommand(add, command);
				break;
			case SLAVE_INDIRECT_ARC_COMMAND:
				host_SendSlaveInDirectArcCommand(add, command);
				break;
			case SLAVE_QUERY_COMMAND:
				host_SendSlaveQueryCommand(add, command);
		//		DEVICE_MAX_CMD(cmd, add);
		//		printf("\n cmd0:%x cmd1%x cmd2%x", cmd[0], cmd[1], cmd[2]);
				break;
			default:
				printf("\n not supported");
				return;
				break;
		}
	//	if(host_comm.dwn_tx(cmd, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
	//		fprintf(stderr, "command send failed");
	//	}
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
