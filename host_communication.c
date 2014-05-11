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

uint32_t host_IsMasterCommand(uint16_t command)
{
	uint32_t ret = 0;
	if(command < MASTER_COMMAND_COUNT)
		ret = 1;
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

static void host_SendMasterCommand(uint16_t cmd)
{
	static uint8_t command[4];
	static uint8_t response[3];
	uint32_t flag = 1;
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
/******************************************************************************
 * Function Name : host_process_slave_command
 * Description : All slave commands need to be send to downstream device
 * Argument : none
 * Return Value : none
 ******************************************************************************/
static void host_SendSlaveCommand(uint16_t buff)
{
		uint8_t command, add;
		static uint8_t cmd[4];
		add = buff >> 8;
		command = (uint8_t)(buff);
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
				break;
		}
		if(host_comm.dwn_tx(cmd, HOST_FORWARD_FRAME_SIZE) != HOST_FORWARD_FRAME_SIZE){
			fprintf(stderr, "command send failed");
		}
	/*	uint8_t dwn_data;
		command = buff[0] << 8 | buff[1];
		host_comm.dwn_tx(command);
		while(!host_comm.dwn_rx(&dwn_data))
		;

		host_comm.usp_tx(&dwn_data, 2);*/
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
	uint16_t command = cmd & 0x00FF;

	if(host_IsMasterCommand(command))
		host_SendMasterCommand(cmd);
	else
		host_SendSlaveCommand(cmd);
	/*
	   if(buff[0] = SLAVE_COMMAND){
	   host_ProcessSlaveCommand(buff+1);
	   }
	   else if(buff[0] = MASTER_COMMAND){
	   host_ProcessMasterCommand(buff+1);
	   }else
	   ret = 1;*/
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
