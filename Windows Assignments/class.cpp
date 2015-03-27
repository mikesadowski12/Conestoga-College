//Mike Sadowski + Constantine Grigoriadis
//April 17th, 2013
//class.cpp
//This file contains the method bodies for the GameInfo class.
#include "class.h"

//Name: GameInfo
//Description: constructor
//PARAMETERS: NONE
//RETURN: NONE
GameInfo::GameInfo(void)
{
	int x = 0;
    ClientSocket = 0;
	//Initialize time limit to be 0 minutes
	TimeLimit = 0;

	//Fill the available characters with 40 x's

	ListOfChars = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	//Fill the allowed words array with NOTSET
	for(x = 0; x < MAXWORDS; x++)
	{
		ListOfWords[x] = "";
	}

}

    int GameInfo::getClientSocket(void)
    {
        int SendingSocket = 0 ;
        SendingSocket  =  ClientSocket;
        return SendingSocket;
    }

//Name: ~GameInfo
//Description: destructor
//PARAMETERS: NONE
//RETURN: NONE
GameInfo::~GameInfo(void)
{

}

//Name: getListOfChars
//Description: accessor for a data member
//PARAMETERS: NONE
//RETURN: string
string GameInfo::getListOfChars(void)
{
	return ListOfChars;
}


//Name: getListOfWords 
//Description: accessor for a data member
//PARAMETERS: NONE
//RETURN: string array
string *GameInfo::getListOfWords(void)
{
	return ListOfWords;
}

//Name: getTimeLimit
//Description: accessor for a data member
//PARAMETERS: NONE
//RETURN: NONE
int GameInfo::getTimeLimit(void)
{
	return TimeLimit;
}


//Name: setClientSocket 
//Description: mutator for the CLientSocket data member
//PARAMETERS: integer (new socket)
//RETURN: true or false if member was set
bool GameInfo::setClientSocket(int socketToSet)
{
    if (socketToSet < 65537)
    {
        ClientSocket = socketToSet ;
        return 0 ; // the data was set
    }
    else
    {
        return 1; // the client socket was not set
    }

}


//Name: setListOfChars
//Description: mutator for the ListOfChars data member
//PARAMETERS: a string of the characters
//RETURN: true or false if member was set
bool GameInfo::setListOfChars(string newSetOfChars)
{
	ListOfChars = newSetOfChars;

	return true;
}


//Name: setListOfWords 
//Description: mutator for the ListOfWords data member
//PARAMETERS: string array
//RETURN: true or false if member was set
bool GameInfo::setListOfWords(string *newSetOfWords)
{
	int x = 0;

	for(x = 0; x < MAXWORDS; x++)
	{
		ListOfWords[x] = newSetOfWords[x];

	}
	return true;
}

 
//Name: setTimeLimit 
//Description: mutator for the time limit data member
//PARAMETERS: new time limit as an int
//RETURN: true or false if member was set
bool GameInfo::setTimeLimit(int newTimeLimit)
{
	if(newTimeLimit > 0)
	{
		TimeLimit = newTimeLimit;
		return true;
	}
	return false;
}

//Name: printGameInfo 
//Description: prints out all the game specifications
//PARAMETERS: NONE
//RETURN: NONE
void GameInfo::printGameInfo(void)
{
	int x = 0;
	printf("[TIMELIMIT]: %d minutes\n", TimeLimit);
	printf("[AVAILABLE CHARACTERS]: %s\n", ListOfChars.c_str());

	for(x = 0; x < MAXWORDS; x++)
	{
		printf("[AVAILABLE WORD]: %s\n", ListOfWords[x].c_str());
	}
}

//Name: printGame
//Description: this function prints out the available characters in a grid to the client.
//PARAMETERS: NONE
//RETURN: NONE
void GameInfo::printGame(void)
{
	int x = 0;
	char printChars[MAXCHARS] = {0};
	string buffer;

	//print 5 letters, spaced out on one line
	for(x = 0; x < 40; x++)
	{
		if(x % 5 == 0 && x != 0)
		{
			//printf("\n  ");
			write (ClientSocket, buffer.c_str(), sizeof(buffer));
			buffer = '\0' ;
		}
		//printf("%c ", printChars[x]);
		buffer += printChars[x] ;
	}
	//print one extra new line
	printf("\n");
}


//Name: printScore
//Description: prints the score
//PARAMETERS: NONE
//RETURN: NONE
void GameInfo::printScore(void)
{

	printGame();
	printf("\nYour Score: %d\n\n\n\n\n", score);

}


//Name: getScore
//Description: returns the score data member
//PARAMETERS: NONE
//RETURN: integer (the score)
int GameInfo::getScore(void)
{
	return score;

}

//Name: setScore 
//Description: sets the score data member
//PARAMETERS: new score as an integer
//RETURN: NONE
void GameInfo::setScore(int newScore)
{
	if(newScore > 0)
	{
		score = newScore;
	}

}

//Name:
//Description:
//PARAMETERS: NONE
//RETURN: NONE
GameInfo GameInfo::operator=( GameInfo b)
{
    GameInfo temp;
    temp.setListOfChars(b.getListOfChars());
    temp.setListOfWords( b.getListOfWords() );
    temp.setTimeLimit(b.getTimeLimit());
    temp.setScore(0);
    return temp;
}

