#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int gpib_config()
{
	int socket_desc;
	struct sockaddr_in server;
	char *server_addr = "192.168.1.32";
	char *message , server_reply[2000];

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	server.sin_addr.s_addr = inet_addr(server_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons( 1234 );

	//Connect to remote server
	printf("Trying to connect to %s\n", server_addr);
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("GPIB-ETHERNET Module Network Error!");
		return 1;
	}

	//Connect GPIB-Ethernet Module
	message = "++savecfg 0\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "++addr 28\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "++auto 0\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "++ver\n";
	send(socket_desc , message , strlen(message) , 0);
	if( recv(socket_desc, server_reply , 1024 , 0) < 0)
	{
		puts("Reading GPIB-ETHERNET Module Version Failed!");
		return 1;
	}
	puts(server_reply);

	//Request GPIB Instrument Version
	message = "*IDN?\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "++read EOI\n";
	send(socket_desc, message, strlen(message), 0);
	if( recv(socket_desc, server_reply , 1024 , 0) < 0)
	{
		puts("Reading GPIB Instrument Version Failed!");
		return 1;
	}
	puts(message);
	puts(server_reply);

	//Request RF Frequency
	message = "RF?\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "++read EOI\n";
	send(socket_desc, message, strlen(message), 0);
	if( recv(socket_desc, server_reply , 1024 , 0) < 0)
	{
		puts("Inquiring RF parameter Failed!");
		return 1;
	}
	puts(server_reply);

	//Request RF Level
	message = "LEVEL?\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "++read EOI\n";
	send(socket_desc, message, strlen(message), 0);
	if( recv(socket_desc, server_reply , 1024 , 0) < 0)
	{
		puts("Reading RF Output LEVEL Failed!");
		return 1;
	}
	puts(server_reply);

	//Set RF Sweep
	message = "LEVEL:OFF\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "RF:START 10KHZ\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "RF:STOP 150MHZ\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "RF:STEP 400KHZ\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "TIME:RF_SWP 40MS\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "LEVEL:ON\n";
	send(socket_desc , message , strlen(message) , 0);
	message = "SWP:SINGLE\n";
	send(socket_desc , message , strlen(message) , 0);

	return 0;
}

int main(int argc , char *argv[])
{
	if (gpib_config())
	{
		puts("Exit with Error.");
	}
}
