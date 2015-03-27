//server.c
//Mike Sadowski
//March 11th, 2013
//This program establishes a server. Clients may connect to it, and send messages to it. This server will then
//save the conversation into a chat log, and send the chat log to each client.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 5000

char buffer[BUFSIZ];
void printChatLog(char* buffer);
void writeChatLog(char *buffer);


void SigCatcher (int n)
{
	wait3 (NULL, WNOHANG, NULL);    
	signal (SIGCHLD, SigCatcher);
}

int main (void)
{
	char *messageBuffer = 0;
	int server_socket, client_socket1, client_socket2, client_socket;
	int client_len;
	struct sockaddr_in client_addr, server_addr;
	int len, i;
	FILE *p;
	messageBuffer = (char*)malloc(1000);

	//create a signal catcher for the child process
	signal (SIGCHLD, SigCatcher);

	//obtain the server socket.
	if ((server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		printf ("ERROR: Can't obtain server socket\n");
		return 1;
	}

	memset (&server_addr, 0, sizeof (server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	server_addr.sin_port = htons (PORT);

	//bind the server socket
	if (bind (server_socket, (struct sockaddr *)&server_addr, 
	sizeof (server_addr)) < 0) {
		printf ("ERROR: Can't bind server socket\n");
		close (server_socket);
		return 2;
	}	

	//start listening on the socket
	if (listen (server_socket, 5) < 0) {
		printf ("ERROR: Can't listen on server socket\n");
		close (server_socket);
		return 3;
	}	

	//Endless loop to accept messages from client, and write to the chat log.
	while (1)
	{

		client_len = sizeof (client_addr);
		if ((client_socket1 = accept (server_socket, 
		(struct sockaddr *)&client_addr, &client_len)) < 0)
		{
			printf ("ERROR: Can't accept packet from client\n");
			close (server_socket);
			return 4;
		}	

		client_socket2 = client_socket1;

		if (fork() == 0) 
		{
			//read the message that was just sent in.
			read (client_socket2, buffer, BUFSIZ);
			
			//write the message to the chatlog
			writeChatLog(buffer);

			//print message on the server terminal
			printf("%s\n",buffer);
			
			//print the entire chat log into a buffer, and send it to the client.
			printChatLog(messageBuffer);
			printf("Chat: %s", messageBuffer);
			write (client_socket2, messageBuffer, len);
	
			close (client_socket2);
			return 0;
		} 	

		else 
		{
			close (client_socket1);
		}	
	}		
	return 0;
}	


//NAME: printChatLog
//DESCRIPTION: this function prints the contents of a text file to the screen, so that clients are able
//             to view their entire conversation.
//PARAMETERS: NONE
//RETURNS: NONE					
void printChatLog(char* buffer)
{
	FILE * pFile;
	int x = 0;
	//char buffer[1000] = {0};

	pFile = fopen("chatlog.txt", "r+");

	fread(buffer, sizeof(char), 1000, pFile);
		
	//close file
	fclose(pFile);

}

//NAME: writeChatLog
//DESCRIPTION: this function writes to a text file to save the entire conversation to a text file
//PARAMETERS: Parameter 1 - a string
//RETURNS: NONE
void writeChatLog(char *buffer)
{
	FILE * pFile;
	
	pFile = fopen("chatlog.txt", "a+");	

	fprintf(pFile, "%s\n", buffer);
	fclose (pFile);
}


