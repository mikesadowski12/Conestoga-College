//client.c
//Mike Sadowski
//March 11th, 2013
//This program connects to a server, and then allows a user to send messages to the server, with a username.

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

#define PORT 5000
#define BUFFSIZE 256

void usageStatement(void);

char buffer[BUFFSIZE];
char userName[BUFFSIZE];
char message[BUFFSIZE];

int main (int argc, char *argv[])
{
	int client_socket, len;
	struct sockaddr_in server_addr;
	struct hostent *host;

	if (argc != 2) 
	{
		usageStatement();
		return 1;
	}	

	//get host info
	if ((host = gethostbyname (argv[1])) == NULL) {
		printf ("ERROR: Can't obtain host info\n");
		return 2;
	}	

	//get a socket
	if ((client_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		printf ("ERROR: Can't get a client socket\n");
		return 3;
	}	

	//initialize struct to get socket to host
	memset (&server_addr, 0, sizeof (server_addr));
	server_addr.sin_family = AF_INET;
	memcpy (&server_addr.sin_addr, host->h_addr, host->h_length);
	server_addr.sin_port = htons (PORT);

	//connect to the server
	if (connect (client_socket, (struct sockaddr *)&server_addr,
	sizeof (server_addr)) < 0) 
	{
		printf ("ERROR: Can't connect to server\n");
		close (client_socket);
		return 4;
	}	

	usageStatement();
	//get username
	printf (" >> Enter username: ");
	fflush (stdout);
	fgets (userName, sizeof (userName), stdin);
	if (userName[strlen (userName) - 1] == '\n')
		userName[strlen (userName) - 1] = '\0';

	if(strcmp(userName, "CANCEL") == 0)
	{
		printf("\n**MESSAGE CANCELLED**\n");
		close (client_socket);
		return 1;
	}
	//get message body
	printf (" >> Enter text: ");
	fflush (stdout);
	fgets (buffer, sizeof (buffer), stdin);
	if (buffer[strlen (buffer) - 1] == '\n')
		buffer[strlen (buffer) - 1] = '\0';

	if(strcmp(buffer, "CANCEL") == 0)
	{
		printf("\n**MESSAGE CANCELLED**\n");
		close (client_socket);
		return 1;
	}

	//append the message to the username, and send it to the server
	strcat(userName, ": ");
	strcat(userName, buffer);
	strcpy(message, userName);

	write (client_socket, message, strlen (message));

	len = read (client_socket, message, sizeof (message));
	printf ("\n**Message Delivered**\n");

	//print the chat
	printf("CHAT: \n %s", message);

	close (client_socket);
	
	return 0;
}	


//NAME: usageStatement
//DESCRIPTION: prints usage statement
//PARAMETERS: NONE
//RETURN: NONE
void usageStatement(void)
{
	printf("\n\n-c <IP ADDRESS>"); 
	printf("\n-To send a message, please type in your username, and the message afterwards");
	printf("\n-Type CANCEL to quit anytime before the message is sent\n\n");
}


