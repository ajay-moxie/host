#include<stdio.h>
#include<winsock2.h>
#include "typedef.h"
 
#pragma comment(lib,"ws2_32.lib") //Winsock Library
 
static SOCKET s;
int open_wifi(char *addr, uint32_t port)
{
    WSADATA wsa;
    struct sockaddr_in server;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        fprintf(stderr,"WSA Failed. Error Code : %d",WSAGetLastError());
	perror("\nWSA: ");
        return 1;
    }
    
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        fprintf(stderr,"Wifi: Could not create socket : %d" , WSAGetLastError());
    }
    
    server.sin_addr.s_addr = inet_addr(addr);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
 
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        fprintf(stderr,"Wifi: connect error");
        return 1;
    }
}


int write_wifi(char *buff, int size)
{
	DWORD bytes_written;
    	if( (bytes_written = send(s , buff , size , 0)) < 0)
	{
		fprintf(stderr, "Wifi write Error\n");
		return 1;
	} 
        printf("\nWifi: bytes writtent = %d",bytes_written);	
	return bytes_written;
}

int read_wifi(char *buff, int size)
{
	DWORD bytes_read;
    	if((bytes_read= recv(s , buff , size , 0)) == SOCKET_ERROR)
	{
		fprintf(stderr, "\nWifi: read Error\n");
		return 1;
	}  
	return 0;
}
