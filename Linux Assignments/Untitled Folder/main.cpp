//Mike Sadowski + Constantine Grigoriadis
//April 17th, 2013
//main.cpp
//This file contains the main function of the program. It acts as a server, and it opens up a text file, and reads its content, and instantiates a
//GameInfo object to hold all of the data from the text for for the game, and waits for clients to connect. Once connected,
//the clients are given copies of the game info to play. Once finished, a high scores table is presented to each player, and
//their score is presented to them as well.
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#define _REENTRANT
#include "class.h"
//Global Server Resources

GameInfo myGame;
int ClientsConnected = 0 ; // the threads can affect this variable when it is spawned
int ClientsFinished = 0 ;  //the threads access this right before they close

//PROTOTYPES
GameInfo OpenFileAndProcessContents(char *filename, GameInfo myGame);
GameInfo ParseTextFileContents(char *contents, GameInfo myGame);
void PrintHelp(void);
GameInfo PlayGame(GameInfo myGame);
bool IsNotEmpty( const std::string& str );
void* SocketHandler(void*);

int main(int argc, char** argv)
{

    bool SetYesNo = false;
    int host_port= 2013;
    struct sockaddr_in my_addr;
    int SERVERSOCKET;
	int * p_int ;
    socklen_t addr_size = 0;
	int* CLIENTSOCKET;
	sockaddr_in sadr;
	pthread_t 	ClientThreads[MAXCLIENTS];


	//checks to see if theres 3 arguments on the command line (program name, input file, time limit)
	if (argc != 3)
	{
		PrintHelp();
		return 1;
	}

	//Set the game time limit, and check to see if it was inputted correctly, if not exit program.
	SetYesNo = myGame.setTimeLimit(atoi(argv[2]));
	if(SetYesNo != true)
	{
		PrintHelp();
		return 1;
	}

	//Open the file, parse out the contents, and save into the myGame object.
	//This is now the entire set up of the game
	myGame = OpenFileAndProcessContents(argv[1], myGame);

	SERVERSOCKET = socket(AF_INET, SOCK_STREAM, 0);
	if(SERVERSOCKET == -1)
	{
		printf("Error initializing socket exiting program...\n");
		return  3;
	}

	p_int = (int*)malloc(sizeof(int)); // used to set the server option then freed
	*p_int = 1;

	if( (setsockopt(SERVERSOCKET, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
    (setsockopt(SERVERSOCKET, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) )
    {
		printf("Error setting options closing program...\n" );
		free(p_int);
		return  3;
	}
	free(p_int); // p_int is not used anywhere else in the program

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY ;

	if( bind( SERVERSOCKET, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 )
	{
		printf("Error binding to socket...\n");
		return  3;
	}
	if(listen( SERVERSOCKET, 10) == -1 )
	{
		printf("Error listening Closing Program...\n");
		return  3;
	}

	//Now lets do the server stuff

	addr_size = sizeof(sockaddr_in);

	while(true)
	{
		printf("waiting for a connection...\n");
		CLIENTSOCKET = (int*)malloc(sizeof(int)); //allocating memory
		if((*CLIENTSOCKET = accept( SERVERSOCKET, (sockaddr*)&sadr, &addr_size))!= -1)
		{
			printf("---------------------\nReceived connection from %s\n",inet_ntoa(sadr.sin_addr));
			printf("sending the game display to the user\n");
			pthread_create(&ClientThreads[ClientsConnected],0,&SocketHandler, (void*)CLIENTSOCKET );
			pthread_detach(ClientThreads[ClientsConnected]); //pthread detach does not cause termination of the thread
		}
		else
		{
			printf("Error accepting packets from connection...\n" );
		}
	}



}
//FUNCTION : SocketHandler -- THREAD FUNCTION
//PARAMETERS : the socket value to be handled
//RETURNS: 0 on success
//DESCRIPTION: this is a thread function that plays the game on a socket
//
//
void* SocketHandler(void* socketVal)
{
    GameInfo thisGame ;
    int* CLIENTSOCKET = (int*)socketVal; // set the client socket for the game
	char buffer[BUFFERSIZE];
    char userName[BUFFERSIZE];
    thisGame = myGame ; //set the threads game to a copy of the global variable for the game
    thisGame.setClientSocket(*CLIENTSOCKET) ;
    int NumCorrectGuesses = 0;
	int CorrectOrNot = 4; //started at 4 so messages don't print on first time th
	int x = 0;
	int z = 0;
	int timeLimit = thisGame.getTimeLimit();
	string inputGuess;
	string wordHolder;
	int points = 0;
	string CorrectWords[MAXWORDS];
	string *AvailableWords = thisGame.getListOfWords();
	int TotalWords = std::count_if(AvailableWords, &AvailableWords[MAXWORDS], IsNotEmpty); //Get total amount of available words
    ClientsConnected++;
    time_t	startTime, stopTime, elapsedTime ;
    startTime = time(NULL); // start the timer
	thisGame.printGame();
	//do a timing loop that grabs user input for the game and validates
	memset(&buffer[0], 0, sizeof(buffer));

	read (*CLIENTSOCKET, buffer, BUFFERSIZE); // read in their name
	strcpy(userName, buffer);
	while(NumCorrectGuesses < MAXWORDS && (elapsedTime < timeLimit))//change max words to time to seconds
	{
		stopTime = time(NULL);
		elapsedTime = stopTime-startTime;

        if (elapsedTime < timeLimit)
        {


            if(TotalWords == NumCorrectGuesses)
            {
                break; // end game condition
            }

            //clear cmd prompt window


            if(CorrectOrNot == 4)
            {
                memset(&buffer[0], 0, sizeof(buffer));
                sprintf(buffer,"\n>> Start Guessing! <<\n\n");
                write (*CLIENTSOCKET, buffer, BUFFERSIZE);
            }

            //If CorrectOrNot is equal to 1, the word was in the list
            if(CorrectOrNot == 1)
            {
                memset(&buffer[0], 0, sizeof(buffer));
                sprintf(buffer,"\n>> Word Correct! %d/%d words found! <<\n\n"
                , NumCorrectGuesses, TotalWords);
                write (*CLIENTSOCKET, buffer, BUFFERSIZE);
            }

            //If CorrectOrNot is equal to 0, the word was not in the list
            if(CorrectOrNot == 0)
            {
                memset(&buffer[0], 0, sizeof(buffer));
                sprintf(buffer,"\n>> Word Incorrect! %d/%d words found! <<\n\n", NumCorrectGuesses, TotalWords);
                write (*CLIENTSOCKET, buffer, BUFFERSIZE);
            }

            //If CorrectOrNot is equal to 2, the word was already entered
            if(CorrectOrNot == 2)
            {
                memset(&buffer[0], 0, sizeof(buffer));
                sprintf(buffer,"\n>> Word Already Entered! %d/%d words found! <<\n\n", NumCorrectGuesses, TotalWords);
                write (*CLIENTSOCKET, buffer, BUFFERSIZE);
            }
        }
        else
        {
            break; //time is up
        }
		//Reset the CorrectOrNot count
		CorrectOrNot = 0;


        memset(&buffer[0], 0, sizeof(buffer));
        stopTime = time(NULL);
		elapsedTime = stopTime-startTime;

		if (elapsedTime > timeLimit)
		{

            thisGame.printGame();
            write (*CLIENTSOCKET,">> Type in the word: ", BUFFERSIZE);

            memset(&buffer[0], 0, sizeof(buffer));
            read (*CLIENTSOCKET, buffer, BUFFERSIZE);
            printf( "%s  submitted: %s \n ", userName , buffer);

            for(x = 0; x < MAXWORDS; x++)
            {
			//Check if the word was already guessed..
                if(inputGuess.compare(CorrectWords[x]) == 0)
                {
                    CorrectOrNot = 2;
                    break;
                }

			//Check if the word is correct..
                if(inputGuess.compare(*(AvailableWords + x)) == 0)
                {
                    CorrectWords[z] = inputGuess;
                    NumCorrectGuesses++;
                    CorrectOrNot = 1;
                    z++;
                    break;
                }
            }
		}
		else
		{
		    break;
		}

	} // main game loop is done


	//Tally up the points..
	for(x = 0; x < TotalWords; x++)
	{
		wordHolder = CorrectWords[x];
		points += wordHolder.length();
	}

    memset(&buffer[0], 0, sizeof(buffer));
	//clear cmd prompt window and print game results..
	sprintf(buffer,"\n>> Game Is Finished! %s found %d/%d words found! <<\n\n", userName ,NumCorrectGuesses, TotalWords);
	write (*CLIENTSOCKET, buffer, BUFFERSIZE);

	thisGame.setScore(points);
	thisGame.printScore();
	write (*CLIENTSOCKET, "Quit", BUFFERSIZE);
	free(CLIENTSOCKET);
    ClientsConnected--;
    return 0;
}


//Not my function..
//Source: http://stackoverflow.com/questions/5739384/how-to-find-number-of-elements-in-an-array-of-strings-in-c
bool IsNotEmpty( const std::string& str )
{
    return !str.empty();
}

//NAME: OpenFileAndProcessContents
//DESCRIPTION: This function opens a specified file name from the command line, and parses out the string of characters,
//			   and the words that are found in the string of characters, and saves the data to the GameInfo object also passed in.
//PARAMETERS: 1 - The name of a file to open, 2 - a GameInfo object
//RETURN: A GameInfo object
GameInfo OpenFileAndProcessContents(char *filename, GameInfo myGame)
{
	FILE * InputFile;
	char* buffer = 0;
	int sizeoffile = 0;
	string newSetOfWords[MAXWORDS];
	string LinesOfFile[MAXWORDS];
	string newSetOfChars;
	char BuildWord[MAXLENGTH] = {0};
	int x = 0;
	int y = 0;
	int z = 0;
	int AmountOfWordsCopied = 0;

	//Open the input file name
	InputFile = fopen(filename, "rb");

	//Check if input file was opened, if it did read it into a buffer.
	if (InputFile == NULL)
	{
		printf(">> Error: Cannot open INPUT file");
		return myGame;
	}
	//Find out file size
	fseek(InputFile , 0 , SEEK_END);
	sizeoffile = ftell(InputFile);
	fseek(InputFile , 0 , SEEK_SET);

	//allocate memory to read file into it
	buffer = (char*) calloc((sizeoffile+1), sizeof(char));

	fread(buffer, sizeof(char) , sizeoffile, InputFile);
	if(strlen(buffer) > 0)
	{
		for(x = 0; x < sizeoffile; x++)
		{
			BuildWord[z++] = buffer[x];

			//If a carraige return is hit
			if(buffer[x] == 13)
			{
				BuildWord[z-1] = '\0'; //terminate the string each time, removing the carriage return
				LinesOfFile[y] = BuildWord;
				x++;
				y++;
				z = 0;
				AmountOfWordsCopied++;
			}

			//End of file is reached
			if(x == sizeoffile - 1)
			{
				BuildWord[z] = '\0'; //terminate the string each time, removing the carriage return
				LinesOfFile[y] = BuildWord;
				y++;
				z = 0;
				AmountOfWordsCopied++;
			}
		}
	}

	//First line of array is the characters, copy into a new variable
	newSetOfChars = LinesOfFile[0];

	//Copy the set of available words into a string array
	for(x = 0; x < AmountOfWordsCopied; x++)
	{
		newSetOfWords[x] = LinesOfFile[x+1];
	}

	//Setup the myGame object to contain all needed information
	myGame.setListOfChars(newSetOfChars);
	myGame.setListOfWords(newSetOfWords);

	//close file, and free memory
	fclose (InputFile);
	free (buffer);

	//Return the myGame object with all required information stored in it
	return myGame;
}



//NAME: PrintHelp - server output
//DESCRIPTION: Prints the help/usage statements of the program
//PARAMETERS: NONE
//RETURN: NONE
void PrintHelp(void)
{
	system("clear");
	cout << "Please specify 3 arguments: [programname.exe] [filename.txt] [timelimit]" << endl;
	cout << ">> [filename.txt] is arbitrary" << endl;
	cout << ">> [timelimit] must be a single integer that is greater than 0, and in minutes" << endl;
}


