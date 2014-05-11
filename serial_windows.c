#include<windows.h>
#include <stdio.h>
#include<string.h>

HANDLE hSerial;
DCB dcbSerialParams = {0};
COMMTIMEOUTS timeouts = {0};


int open_serial(char *portName)
{
	char port[20] = "";
	strcat(port, "//./");
	strcat(port, portName);
	hSerial = CreateFile( port,  
			GENERIC_READ | GENERIC_WRITE, 
			0, 
			0, 
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);
	if (hSerial == INVALID_HANDLE_VALUE){
		printf("error opening serial port %s", port);
		return 1;
	}
	else printf( "OK\n");

	// Set device parameters (38400 baud, 1 start bit,
	// 1 stop bit, no parity)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error getting device state\n");
		CloseHandle(hSerial);
		return 1;
	}

	dcbSerialParams.BaudRate = CBR_38400;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if(SetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error setting device parameters\n");
		CloseHandle(hSerial);
		return 1;
	}

	return 0;
}

int configure_serial_timeout()
{
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if(SetCommTimeouts(hSerial, &timeouts) == 0)
	{
		fprintf(stderr, "Error setting timeouts\n");
		CloseHandle(hSerial);
		return 1;
	}
	return 0;	
}
int write_serial(char *buff, int size)
{
	DWORD bytes_written;
	if(!WriteFile(hSerial, buff, size, &bytes_written, NULL))
	{
		fprintf(stderr, "serial write Error\n");
		CloseHandle(hSerial);
		return 1;
	}  
	return bytes_written;
}


int read_serial(char *buff, int size)
{
	DWORD bytes_read;
	if(!ReadFile(hSerial, buff, size, &bytes_read, NULL))
	{
		fprintf(stderr, "serial read Error\n");
		CloseHandle(hSerial);
		return 1;
	}  
	return 0;
}
