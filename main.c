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
		}
		printf("\ncommand = %x", command);
		host_AnalyzeCommand(command);
	}


}

