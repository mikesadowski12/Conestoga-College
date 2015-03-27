#include "class.h"

/*
 * client.c
 *
 * This is a sample internet client application that will talk
 * to the server s.c via port 5000
 */



#define PORT 5000
#define BUFFERSIZE 100


int main (int argc, char *argv[])
{
	int client_socket, len;
	struct sockaddr_in server_addr;
	struct hostent *host;
	char buffer[BUFSIZ];
	int quitFlag = 0 ;

	/*
	 * check for sanity
	 */

	if (argc != 2) {
		printf ("usage: c server_name\n");
		return 1;
	}	/* endif */

	/*
	 * determine host info for server name supplied
	 */


	if ((host = gethostbyname (argv[1])) == NULL) {
		printf ("grrr, can't get host info!\n");
		return 2;
	}	/* endif */

	/*
	 * get a socket for communications
	 */

	if ((client_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		printf ("grrr, can't get a client socket!\n");
		return 3;
	}	/* endif */

	/*
	 * initialize struct to get a socket to host
	 */

	memset (&server_addr, 0, sizeof (server_addr));
	server_addr.sin_family = AF_INET;
	memcpy (&server_addr.sin_addr, host->h_addr, host->h_length);
	server_addr.sin_port = htons (PORT);

	/*
	 * attempt a connection to server
	 */

	if (connect (client_socket, (struct sockaddr *)&server_addr,
	sizeof (server_addr)) < 0)
	{
		printf ("grrr, can't connet to server!\n");
		close (client_socket);
		return 4;
	}	/* endif */
	//at this point if the program is still running
	/*
	 * now that we have a connection, get a commandline from
	 * the user, and fire it off to the server
	 */
	printf("Welcome to the server chat program you are connected\n");
	printf( "type in messege to be sent to Server \n");
	fflush (stdout);

        read (client_socket, buffer, BUFFERSIZE);

		//the main chat loop
			do{


				memset (buffer, 0, sizeof (buffer));
				read (client_socket, buffer, BUFFERSIZE); // reads the information coming in from the socket
				printf("Server: %s\n",buffer);
				memset (buffer, 0, sizeof (buffer));
				printf("\n Client: ");
				fgets (buffer, BUFFERSIZE, stdin);
				if(strcmp(buffer , "QUIT") == 0)
				{

				quitFlag = 1 ;
				}
						//the max input size is 100 for messages
				write (client_socket, buffer, len);


			}while (quitFlag == 0);





	/*
	 * cleanup
	 */

	close (client_socket);
	printf ("Client is finished\n");

	return 0;
}	/* end main */
