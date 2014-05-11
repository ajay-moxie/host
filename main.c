#include<stdio.h>
#include"serial_windows.h"
#include "host_commands.h"
#include "typedef.h"


menu_commands()
{
	printf("\n-----------------------------");
	printf("\nHome Automation Commands");
	printf("\nEnumerate: %d", ENUMERATE);
	printf("\nGet Device Count: %d", DEVICE_COUNT);
	printf("\nMIN Slave: 0x%x<address eg 01>", DEVICE_MIN);
	printf("\nMAX Slave: 0x%x<address eg 01>", DEVICE_MAX);
	printf("\n-----------------------------\n");
}

main(int argc, char *argv[])
{
	static uint32_t command;
	open_serial(argv[1]);
	host_RegisterTxRx(write_serial, read_serial);
	while(1){
		menu_commands();
		scanf("%x",&command);
		printf("\ncommand = %x", command);
		host_AnalyzeCommand(command);
	}


}

