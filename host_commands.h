#ifndef __HOST_COMMANDS__
#define __HOST_COMMANDS__
#define HOST_FORWARD_FRAME_SIZE 4
#define HOST_BACKWARD_FRAME_SIZE 3
#define NOT_SUPPORTED 0
#define MASTER_COMMAND_COUNT 10
#define SLAVE_COMMAND 0x00
#define SLAVE_QUERY_COMMAND 10
#define SLAVE_DIRECT_ARC_COMMAND 11
	#define DEVICE_MIN MASTER_COMMAND_COUNT + 1
	#define DEVICE_MIN_CMD(cmd, add) (cmd[0] = SLAVE_COMMAND, cmd[1] = ((0 << 7) | (add << 1) | 1), cmd[2] = 0x6)//YAAAAAA1 0000 0110
	#define DEVICE_MAX MASTER_COMMAND_COUNT + 2
	#define DEVICE_MAX_CMD(cmd, add) (cmd[0] = SLAVE_COMMAND, cmd[1] = (0 << 7) | (add << 1) | 1, cmd[2] = 0x5)//YAAAAAA1 0000 0101
#define MASTER_COMMAND 0xAA
	#define ENUMERATE 0x1
	#define DEVICE_COUNT 0x2
#define RESPONSE_1BYTE 0xAA 
#define RESPONSE_2BYTE 0xbb
	#define RESPONSE_OFFSET 0
	#define RESPONSE_1BYTE_OFFSET 1
	#define RESPONSE_2BYTE_OFFSET 2
	#define ACK 0xFF
	#define NAK 0x00
#define RESPONSE_ACK(response) (response[RESPONSE_OFFSET] = RESPONSE_1BYTE, response[RESPONSE_1BYTE_OFFSET] = ACK, response[RESPONSE_2BYTE_OFFSET] = 0)
#define RESPONSE_NAK(response) (response[RESPONSE_OFFSET] = RESPONSE_1BYTE, response[RESPONSE_1BYTE_OFFSET] = NAK, response[RESPONSE_2BYTE_OFFSET] = 0)

#endif
