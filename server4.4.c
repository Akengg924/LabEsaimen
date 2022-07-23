#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //write

int main(int argc , char *argv[])
{
        int socket_sock , next_socket , c;
        struct sockaddr_in server , client;
        char  client_message[1000];
        char buffer[1000];
        char message[sizeof(buffer)];


        //Create socket
        socket_sock = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_sock <0)
        {
                printf("Create Socket Failed");
        }

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 8000 );

        //Bind
        if( bind(socket_sock,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("bind failed");
                return 1;
        }
        puts("bind done");

        //Listen
        listen(socket_sock , 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);

        while(1)
        {
               next_socket = accept(socket_sock, (struct sockaddr *)&client, (socklen_t*)&c); 
                puts("Connection accepted\n");

                while(1){
                //Message from Client
                if( recv(next_socket, client_message , 1000 , 0) < 0)
                    {
                      puts("recv failed");
                    }


                 printf("Client :");
                 puts(client_message);

                //Reply to the client
                printf("Server : ");
                scanf("%s", message);
                printf("\n");
                write(next_socket , message , strlen(message));
                }
        }

        if (next_socket<0)
        {
                perror("accept failed");
                return 1;
        }

        return 0;
}
