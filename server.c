/*
   Live Server on port 8888
   */
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	int recv_size;
	char message[10], server_reply[2000];

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	puts("Bind done");

	//Listen to incoming connections
	listen(s , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);

	if( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET ){
		printf("Connection accepted");
		while(1)
		{

			if((recv_size = recv(new_socket , server_reply , 2000 , 0)) == SOCKET_ERROR){
				puts("recv failed");
			}
			//	server_reply[recv_size] = '\0';
			printf("\nserver:size=%d %x ", recv_size, server_reply[0]);
			printf("\nserver:size=%d %x ", recv_size, server_reply[1]);
			printf("\nserver:size=%d %x ", recv_size, server_reply[2]);
			printf("\nserver:size=%d %x ", recv_size, server_reply[3]);

			//Reply to the client
			message[0] = 0xAA;
			message[1] = 0xFF;
			message[2] = 0x00;
			send(new_socket , message , 3 , 0);
		}
	}

	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
		return 1;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}
