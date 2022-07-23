//OLD CODE

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<signal.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char *message,serverMsg[signalTSTP],buff[signalTSTP],buffer[signalTSTP];
	void signalTSTP_handler(int tstp)

	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
		
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//Message with CLIENT
	while( (new_socket = accept(socket_desc, (struct sockaddr )&client, (socklen_t)&c)) )
	{
		puts("Connection accepted");
		printf("***Welcome to chat application***\n\n");

		
		for(;;){
		if((recv(new_socket,buff,1000,0))>0)
		{
			printf("** Waiting for CLIENT Message ***\n\n");
			recv(socket_desc,buff,1000,0);
			printf("CLIENT: %s\n",buff);
			
			printf("!!! Press CTRL + Z to exit!!! \n\n");
			printf("SERVER:");
			fgets(buffer,1000,stdin);
			send(new_socket,buffer,1000,0);
			
			if (signal(SIGNALTSTP, signalTSTP_handler) == SIG_ERR){
			perror("signal");
			exit(1);
  			}
			
		}
		}
	}
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	
}
void signalTSTP_handler(int tstp)
{
  printf("Ending Message with Client \n\n");
  printf("***Thank You for using this application****\n\n");
  exit(0);
}
