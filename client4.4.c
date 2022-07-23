#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>


int main(int argc , char *argv[])
{
	int socket_sock;
	struct sockaddr_in server;
	char server_reply[1000];
        char buffer[1000] = { 0 };
        char message[sizeof(buffer)];


	//Create socket
	socket_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_sock < 0)
	{
		printf("Create Socket Failed");
	}

	server.sin_addr.s_addr = inet_addr("192.168.8.109"); //Please enter the ip address of your Server VM
	server.sin_family = AF_INET;
	server.sin_port = htons( 8000 );

	//Connect to remote server
	if (connect(socket_sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("connect error");
		return 1 ;
	}

	printf("Connected \n");

       while(1){

	//Send some data
	printf("Client  : ");
        scanf(" %s", message);

	if( send(socket_sock , message , strlen(message) , 0) < 0)
	{
		printf("Send failed");
		return 1;
	}

                    //Receive a reply from the server
	if( recv(socket_sock, server_reply , 1000 , 0) < 0)
	{
		puts("recv failed");
	}
	printf("Server : ");
	puts(server_reply);
        printf("\n");

        }
        close(socket_sock);
	return 0;
}
