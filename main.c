#include<stdio.h>
#include "typedef.h"
#include "config.h"
#include"serial_windows.h"
#include "wifi_windows.h"
#include "host_commands.h"

menu_commands()
{
	printf("\n-----------------------------");
	printf("\nHome Automation Commands");
	printf("\nEnumerate all: %x", (MASTER_COMMAND << 24) | (ENUMERATE << 16));
	printf("\nEnumerate <address>: %x%x<address>00", MASTER_COMMAND,ENUMERATE);
	printf("\nGet Device Count: %x", (MASTER_COMMAND << 24) | (DEVICE_COUNT << 16));
	printf("\nConfigure Device %x", MASTER_CONFIGURATION_COMMAND);
	printf("\nIn Direct ARCH POWER Commands %x", SLAVE_INDIRECT_ARC_COMMAND);
	printf("\nDirect ARCH POWER Commands %x", SLAVE_DIRECT_ARC_COMMAND);
	printf("\nslave query commands %x", SLAVE_QUERY_COMMAND);
	printf("\n-----------------------------\n");
}

uint32_t direct_arc_power_commands_menu()
{
	static uint32_t command;
	static uint32_t addr;
	printf("\nLevel<0-ff>:\n");
	scanf("%x",&command);
	printf("\nbroadcase: FF\ngroup:( 4<0-f>\nshort address: <0-3F>\n");
	scanf("%x",&addr);
	return (SLAVE_COMMAND << 24) | (addr << 17) | (command << 8);
}

uint32_t master_conf_commands_menu()
{
	static uint32_t command;
	static uint32_t addr;
	printf("\nCONF_RESET %x", CONF_RESET);
	printf("\nCONF_STR_LVL_DTR %x", CONF_STR_LVL_DTR);
	printf("\nCONF_STR_MAX_LVL_DTR %x", CONF_STR_MAX_LVL_DTR);
	printf("\nCONF_STR_MIN_LVL_DTR %x", CONF_STR_MIN_LVL_DTR);
	printf("\nCONF_STR_SYS_FAILURE_DTR %x", CONF_STR_SYS_FAILURE_DTR);
	printf("\nCONF_STR_POWER_ON_LVL_DTR %x", CONF_STR_POWER_ON_LVL_DTR);
	printf("\nCONF_STR_FADE_TIME_DTR %x", CONF_STR_FADE_TIME_DTR);
	printf("\nCONF_STR_FADE_RATE_DTR %x", CONF_STR_FADE_RATE_DTR);
	printf("\nCONF_STR_SCENE0_DTR %x", CONF_STR_SCENE0_DTR);
	printf("\nCONF_STR_SCENE1_DTR %x", CONF_STR_SCENE1_DTR);
	printf("\nCONF_STR_SCENE2_DTR %x", CONF_STR_SCENE2_DTR);
	printf("\nCONF_STR_SCENE3_DTR %x", CONF_STR_SCENE3_DTR);
	printf("\nCONF_STR_SCENE4_DTR %x", CONF_STR_SCENE4_DTR);
	printf("\nCONF_STR_SCENE5_DTR %x", CONF_STR_SCENE5_DTR);
	printf("\nCONF_STR_SCENE6_DTR %x", CONF_STR_SCENE6_DTR);
	printf("\nCONF_STR_SCENE7_DTR %x", CONF_STR_SCENE7_DTR);
	printf("\nCONF_STR_SCENE8_DTR %x", CONF_STR_SCENE8_DTR);
	printf("\nCONF_STR_SCENE9_DTR %x", CONF_STR_SCENE9_DTR);
	printf("\nCONF_STR_SCENE10_DTR %x", CONF_STR_SCENE10_DTR);
	printf("\nCONF_STR_SCENE11_DTR %x", CONF_STR_SCENE11_DTR);
	printf("\nCONF_STR_SCENE12_DTR %x", CONF_STR_SCENE12_DTR);
	printf("\nCONF_STR_SCENE13_DTR %x", CONF_STR_SCENE13_DTR);
	printf("\nCONF_STR_SCENE14_DTR %x", CONF_STR_SCENE14_DTR);
	printf("\nCONF_STR_SCENE15_DTR %x", CONF_STR_SCENE15_DTR);
	printf("\nCONF_RMV_SCENE0_DTR %x", CONF_RMV_SCENE0_DTR);
	printf("\nCONF_RMV_SCENE1_DTR %x", CONF_RMV_SCENE1_DTR);
	printf("\nCONF_RMV_SCENE2_DTR %x", CONF_RMV_SCENE2_DTR);
	printf("\nCONF_RMV_SCENE3_DTR %x", CONF_RMV_SCENE3_DTR);
	printf("\nCONF_RMV_SCENE4_DTR %x", CONF_RMV_SCENE4_DTR);
	printf("\nCONF_RMV_SCENE5_DTR %x", CONF_RMV_SCENE5_DTR);
	printf("\nCONF_RMV_SCENE6_DTR %x", CONF_RMV_SCENE6_DTR);
	printf("\nCONF_RMV_SCENE7_DTR %x", CONF_RMV_SCENE7_DTR);
	printf("\nCONF_RMV_SCENE8_DTR %x", CONF_RMV_SCENE8_DTR);
	printf("\nCONF_RMV_SCENE9_DTR %x", CONF_RMV_SCENE9_DTR);
	printf("\nCONF_RMV_SCENE10_DTR %x", CONF_RMV_SCENE10_DTR);
	printf("\nCONF_RMV_SCENE11_DTR %x", CONF_RMV_SCENE11_DTR);
	printf("\nCONF_RMV_SCENE12_DTR %x", CONF_RMV_SCENE12_DTR);
	printf("\nCONF_RMV_SCENE13_DTR %x", CONF_RMV_SCENE13_DTR);
	printf("\nCONF_RMV_SCENE14_DTR %x", CONF_RMV_SCENE14_DTR);
	printf("\nCONF_RMV_SCENE15_DTR %x", CONF_RMV_SCENE15_DTR);
	printf("\nCONF_ADD_GRP0 %x", CONF_ADD_GRP0);
	printf("\nCONF_ADD_GRP1 %x", CONF_ADD_GRP1);
	printf("\nCONF_ADD_GRP2 %x", CONF_ADD_GRP2);
	printf("\nCONF_ADD_GRP3 %x", CONF_ADD_GRP3);
	printf("\nCONF_ADD_GRP4 %x", CONF_ADD_GRP4);
	printf("\nCONF_ADD_GRP5 %x", CONF_ADD_GRP5);
	printf("\nCONF_ADD_GRP6 %x", CONF_ADD_GRP6);
	printf("\nCONF_ADD_GRP7 %x", CONF_ADD_GRP7);
	printf("\nCONF_ADD_GRP8 %x", CONF_ADD_GRP8);
	printf("\nCONF_ADD_GRP9 %x", CONF_ADD_GRP9);
	printf("\nCONF_ADD_GRP10 %x", CONF_ADD_GRP10);
	printf("\nCONF_ADD_GRP11 %x", CONF_ADD_GRP11);
	printf("\nCONF_ADD_GRP12 %x", CONF_ADD_GRP12);
	printf("\nCONF_ADD_GRP13 %x", CONF_ADD_GRP13);
	printf("\nCONF_ADD_GRP14 %x", CONF_ADD_GRP14);
	printf("\nCONF_ADD_GRP15 %x", CONF_ADD_GRP15);
	printf("\nCONF_RMV_GRP0 %x", CONF_RMV_GRP0);
	printf("\nCONF_RMV_GRP1 %x", CONF_RMV_GRP1);
	printf("\nCONF_RMV_GRP2 %x", CONF_RMV_GRP2);
	printf("\nCONF_RMV_GRP3 %x", CONF_RMV_GRP3);
	printf("\nCONF_RMV_GRP4 %x", CONF_RMV_GRP4);
	printf("\nCONF_RMV_GRP5 %x", CONF_RMV_GRP5);
	printf("\nCONF_RMV_GRP6 %x", CONF_RMV_GRP6);
	printf("\nCONF_RMV_GRP7 %x", CONF_RMV_GRP7);
	printf("\nCONF_RMV_GRP8 %x", CONF_RMV_GRP8);
	printf("\nCONF_RMV_GRP9 %x", CONF_RMV_GRP9);
	printf("\nCONF_RMV_GRP10 %x", CONF_RMV_GRP10);
	printf("\nCONF_RMV_GRP11 %x", CONF_RMV_GRP11);
	printf("\nCONF_RMV_GRP12 %x", CONF_RMV_GRP12);
	printf("\nCONF_RMV_GRP13 %x", CONF_RMV_GRP13);
	printf("\nCONF_RMV_GRP14 %x", CONF_RMV_GRP14);
	printf("\nCONF_RMV_GRP15 %x", CONF_RMV_GRP15);
	printf("\nCONF_STR_SHORT_ADD_DTR %x\n", CONF_STR_SHORT_ADD_DTR);

	scanf("%x",&command);
	printf("\nshort address: <0-3F>\n");
	scanf("%x",&addr);
	return (MASTER_COMMAND << 24) | (MASTER_CONFIGURATION_COMMAND << 16) | (addr << 9) | (1 << 8) | (command );
}

uint32_t slave_query_commands_menu()
{
	static uint32_t command;
	static uint32_t addr;
	printf("\n QUERY_STATUS: %x", QUERY_STATUS);
	printf("\n QUERY_BALLAST: %x", QUERY_BALLAST);
	printf("\n QUERY_LAMP_FAILURE: %x", QUERY_LAMP_FAILURE);
	printf("\n QUERY_LAMP_POWER_ON: %x", QUERY_LAMP_POWER_ON);
	printf("\n QUERY_LIMIT_ERROR: %x", QUERY_LIMIT_ERROR);
	printf("\n QUERY_RESET_STATE: %x", QUERY_RESET_STATE);
	printf("\n QUERY_MISSING_SHORT_ADD: %x", QUERY_MISSING_SHORT_ADD);
	printf("\n QUERY_VERSION_NO: %x", QUERY_VERSION_NO);
	printf("\n QUERY_CONTENT_DTR: %x", QUERY_CONTENT_DTR);
	printf("\n QUERY_DEVICE_TYPE: %x", QUERY_DEVICE_TYPE);
	printf("\n QUERY_PHYSICAL_MIN_LEVEL: %x", QUERY_PHYSICAL_MIN_LEVEL);
	printf("\n QUERY_POWER_FAILURE: %x", QUERY_POWER_FAILURE);
	printf("\n QUERY_HOME_AUTOMATION_DEVICE_ID: %x", QUERY_HOME_AUTOMATION_DEVICE_ID);
	printf("\n QUERY_ACTUAL_LEVEL: %x", QUERY_ACTUAL_LEVEL);
	printf("\n QUERY_MAX_LEVEL: %x", QUERY_MAX_LEVEL);
	printf("\n QUERY_MIN_LEVEL: %x", QUERY_MIN_LEVEL);
	printf("\n QUERY_POWER_ON_LEVEL:%x", QUERY_POWER_ON_LEVEL);
	printf("\n QUERY_SYSTEL_FAILURE_LEVEL: %x", QUERY_SYSTEL_FAILURE_LEVEL);
	printf("\n COMMAND_QUERY_DEVICE_NAME0: %x", COMMAND_QUERY_DEVICE_NAME0);
	printf("\n COMMAND_QUERY_DEVICE_NAME1: %x", COMMAND_QUERY_DEVICE_NAME1);
	printf("\n COMMAND_QUERY_DEVICE_NAME2: %x", COMMAND_QUERY_DEVICE_NAME2);
	printf("\n COMMAND_QUERY_DEVICE_NAME3: %x", COMMAND_QUERY_DEVICE_NAME3);
	printf("\n COMMAND_QUERY_DEVICE_NAME4: %x", COMMAND_QUERY_DEVICE_NAME4);
	printf("\n COMMAND_QUERY_DEVICE_NAME5: %x", COMMAND_QUERY_DEVICE_NAME5);
	printf("\n COMMAND_QUERY_DEVICE_NAME6: %x", COMMAND_QUERY_DEVICE_NAME6);
	printf("\n COMMAND_QUERY_DEVICE_NAME7: %x", COMMAND_QUERY_DEVICE_NAME7);
	printf("\n QUERY_SYSTEL_FADE_RATE: %x", QUERY_SYSTEL_FADE_RATE);
	printf("\n QUERY_SCENE0_LEVEL: %x", QUERY_SCENE0_LEVEL);
	printf("\n QUERY_SCENE1_LEVEL: %x", QUERY_SCENE1_LEVEL);
	printf("\n QUERY_SCENE2_LEVEL: %x", QUERY_SCENE2_LEVEL);
	printf("\n QUERY_SCENE3_LEVEL: %x", QUERY_SCENE3_LEVEL);
	printf("\n QUERY_SCENE4_LEVEL: %x", QUERY_SCENE4_LEVEL);
	printf("\n QUERY_SCENE5_LEVEL: %x", QUERY_SCENE5_LEVEL);
	printf("\n QUERY_SCENE6_LEVEL: %x", QUERY_SCENE6_LEVEL);
	printf("\n QUERY_SCENE7_LEVEL: %x", QUERY_SCENE7_LEVEL);
	printf("\n QUERY_SCENE8_LEVEL: %x", QUERY_SCENE8_LEVEL);
	printf("\n QUERY_SCENE9_LEVEL: %x", QUERY_SCENE9_LEVEL);
	printf("\n QUERY_SCENE10_LEVEL: %x", QUERY_SCENE10_LEVEL);
	printf("\n QUERY_SCENE11_LEVEL: %x", QUERY_SCENE11_LEVEL);
	printf("\n QUERY_SCENE12_LEVEL: %x", QUERY_SCENE12_LEVEL);
	printf("\n QUERY_SCENE13_LEVEL: %x", QUERY_SCENE13_LEVEL);
	printf("\n QUERY_SCENE14_LEVEL: %x", QUERY_SCENE14_LEVEL);
	printf("\n QUERY_SCENE15_LEVEL: %x", QUERY_SCENE15_LEVEL);
	printf("\n QUERY_GROUP_0_7: %x", QUERY_GROUP_0_7);
	printf("\n QUERY_GROUP_8_15: %x", QUERY_GROUP_8_15);
	printf("\n QUERY_RANDOM_ADD_H: %x", QUERY_RANDOM_ADD_H);
	printf("\n QUERY_RANDOM_ADD_M: %x", QUERY_RANDOM_ADD_M);
	printf("\n QUERY_RANDOM_ADD_L: %x\n", QUERY_RANDOM_ADD_L);
	scanf("%x",&command);
	printf("\nshort address: <0-3F>\n");
	scanf("%x",&addr);
	return (SLAVE_COMMAND << 24) | (addr << 17) | (1 << 16) | (command << 8);
}
uint32_t indirect_arc_power_commands_menu()
{
	static uint32_t command;
	static uint32_t addr;
	printf("\nOFF: %x", ARCH_POWER_OFF);
	printf("\nUP: %x", ARCH_POWER_UP);
	printf("\nDOWN: %x", ARCH_POWER_DOWN);
	printf("\nSTEP UP: %x", ARCH_POWER_STEP_UP);
	printf("\nSTEP DOWN: %x", ARCH_POWER_STEP_DOWN);
	printf("\nRECALL MAX: %x", ARCH_POWER_RECALL_MAX);
	printf("\nRECALL MIN: %x", ARCH_POWER_RECALL_MIN);
	printf("\nSTEP DOWN & OFF: %x", ARCH_POWER_STEP_DOWN_OFF);
	printf("\nPOWER ON and STEP UP: %x", ARCH_POWER_ON_AND_STEP_UP);
	printf("\nARCH_POWER_GO_TO_SCENE0: %x",	ARCH_POWER_GO_TO_SCENE0);
	printf("\nARCH_POWER_GO_TO_SCENE1: %x",	ARCH_POWER_GO_TO_SCENE1);
	printf("\nARCH_POWER_GO_TO_SCENE2: %x",	ARCH_POWER_GO_TO_SCENE2);
	printf("\nARCH_POWER_GO_TO_SCENE3: %x",	ARCH_POWER_GO_TO_SCENE3);
	printf("\nARCH_POWER_GO_TO_SCENE4: %x",	ARCH_POWER_GO_TO_SCENE4);
	printf("\nARCH_POWER_GO_TO_SCENE5: %x",	ARCH_POWER_GO_TO_SCENE5);
	printf("\nARCH_POWER_GO_TO_SCENE6: %x",	ARCH_POWER_GO_TO_SCENE6);
	printf("\nARCH_POWER_GO_TO_SCENE7: %x",	ARCH_POWER_GO_TO_SCENE7);
	printf("\nARCH_POWER_GO_TO_SCENE8: %x",	ARCH_POWER_GO_TO_SCENE8);
	printf("\nARCH_POWER_GO_TO_SCENE9: %x",	ARCH_POWER_GO_TO_SCENE9);
	printf("\nARCH_POWER_GO_TO_SCENE10: %x",	ARCH_POWER_GO_TO_SCENE10);
	printf("\nARCH_POWER_GO_TO_SCENE11: %x",	ARCH_POWER_GO_TO_SCENE11);
	printf("\nARCH_POWER_GO_TO_SCENE12: %x",	ARCH_POWER_GO_TO_SCENE12);
	printf("\nARCH_POWER_GO_TO_SCENE13: %x",	ARCH_POWER_GO_TO_SCENE13);
	printf("\nARCH_POWER_GO_TO_SCENE14: %x",	ARCH_POWER_GO_TO_SCENE14);
	printf("\nARCH_POWER_GO_TO_SCENE15: %x\n",	ARCH_POWER_GO_TO_SCENE15);
	scanf("%x",&command);
	printf("\nbroadcase: FF\ngroup:( 4<0-f>\nshort address: <0-3F>\n");
	scanf("%x",&addr);
	return (SLAVE_COMMAND << 24) | (addr << 17) | (1 << 16) | (command << 8);

}
main(int argc, char *argv[])
{
	static uint32_t command;
#ifdef SERIAL_CONFIG
	open_serial(argv[1]);
	host_RegisterTxRx(write_serial, read_serial);
#endif
#ifdef WIFI_CONFIG
	open_wifi(argv[1], atoi(argv[2]));	
	host_RegisterTxRx(write_wifi, read_wifi);
#endif
	while(1){
		menu_commands();
		scanf("%x",&command);
		switch(command){
			case SLAVE_INDIRECT_ARC_COMMAND:
			command = indirect_arc_power_commands_menu();
			break;
			case SLAVE_DIRECT_ARC_COMMAND:
			command = direct_arc_power_commands_menu();
			break;
			case SLAVE_QUERY_COMMAND:
			command = slave_query_commands_menu();
			break;
			case MASTER_CONFIGURATION_COMMAND:
			command = master_conf_commands_menu();
			break;

		}
		printf("\ncommand = %x", command);
		host_AnalyzeCommand(command);
	}


}

