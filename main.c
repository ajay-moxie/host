#include<stdio.h>
#include"serial_windows.h"
#include "host_commands.h"
#include "typedef.h"


menu_commands()
{
	printf("\n-----------------------------");
	printf("\nHome Automation Commands");
	printf("\nEnumerate all: %x", (MASTER_COMMAND << 24) | (ENUMERATE << 16));
	printf("\nEnumerate <address>: %x%x<address>00", MASTER_COMMAND,ENUMERATE);
	printf("\nGet Device Count: %x", (MASTER_COMMAND << 24) | (DEVICE_COUNT << 16));
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
	printf("\n QUERY_ACTUAL_LEVEL: %x", QUERY_ACTUAL_LEVEL);
	printf("\n QUERY_MAX_LEVEL: %x", QUERY_MAX_LEVEL);
	printf("\n QUERY_MIN_LEVEL: %x", QUERY_MIN_LEVEL);
	printf("\n QUERY_POWER_ON_LEVEL:%x", QUERY_POWER_ON_LEVEL);
	printf("\n QUERY_SYSTEL_FAILURE_LEVEL: %x", QUERY_SYSTEL_FAILURE_LEVEL);
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
	open_serial(argv[1]);
	host_RegisterTxRx(write_serial, read_serial);
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

		}
		printf("\ncommand = %x", command);
		host_AnalyzeCommand(command);
	}


}

