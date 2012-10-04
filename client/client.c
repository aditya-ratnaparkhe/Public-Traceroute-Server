/*
 * Client.c
 * Contains the client code which connects to the server and
 * then has the ability to execute different commands.
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <memory.h>



#define PORT 1216
int terminateSenderThread = -1;


/*
 * Creates a thread for the client to
 * execute commands on the server.
 */
void  *sendThread(void *arg)
{
	int clientFD = *(int*)arg;
	char command[512];


	while (1) {
		memset(&command, 0, sizeof(command));
		fgets(command, sizeof(command),stdin);
		command[strlen(command)-1]='\0';

		ssize_t len = (ssize_t)sizeof(command);
		ssize_t res = send(clientFD,&command,len,0);
		if(res==-1){printf("\nError in sending");}


	}

	return NULL;
}






/*
 * Main thread used to receive data from the server.
 */
int main(int argc, const char * argv[])
{

	int port_no = PORT;
	char ip_addr[15];
	int use_localhost = 1;

	//The seperator is "=" as parameters are supplied in the form param=value
	const char *seperator = "=";
	int i;

	//Accept parameters and seperate them.
	for(i=1;i<argc;i++)
		//0 is command
	{
		const char *arg = argv[i];
		char *param = strtok((char *)arg, seperator);
		char *val = NULL;
		while ((val = strtok(NULL, seperator))!=NULL) {

			if(strcmp(param, "ip")==0)
				strcpy(ip_addr,val);
			else if((strcmp(param, "port"))==0)
			{
				port_no = atoi(val);
				use_localhost = 0;
			}
		}
	}

	//Create client stream socket of type TCP for IPV4
	int clientFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sockAddr;
	pthread_t rthread,sthread;
	void *rstatus = NULL;

	//If client socket is successfully created
	if (clientFD!=-1) {
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		//Convert port no to network byte order
		sockAddr.sin_port = htons(port_no);
		if(!use_localhost)
			inet_pton(AF_INET,ip_addr,&(sockAddr.sin_addr.s_addr));
		else if(use_localhost)
			sockAddr.sin_addr.s_addr = INADDR_ANY;
		printf("Socket created");
	}
	else
	{
		exit(1);
	}

	//connect to server
	int res = connect(clientFD, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if(res>=0)
	{
		printf("\nConnected to server");

		//Create thread to send commands to server
		pthread_create(&sthread, NULL, sendThread, &clientFD);
		char buff[1024];
		int len=0;
		ssize_t bytes = 0;
		int byte_count = -1;

		//Infinite loop to send commands and receive output
		while (1)
		{

			memset(buff, 0, sizeof(buff));

			//Check if data is received correctly
			if( (byte_count = recv (clientFD, buff, sizeof(buff), MSG_WAITALL)) == -1)
			{
				printf("Error receiving msg");
			}
			else
			{
				buff[byte_count]='\0';

				if((strcmp(buff, "terminate"))==0)
				{
					pthread_cancel(sthread);
					break;
				}
				else if (strcmp(buff, "\nConnection Time Out")==0)
				{
					printf("Connection time out\n");
					pthread_cancel(sthread);
					break;

				}
					printf("%s",buff);
				fflush(stdout);


			}
		}

		//Close connection from client side.
		close(clientFD);
		printf("\nShutting down\n");

		return 0;
	}
}



