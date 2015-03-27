//Mike Sadowski + Constantine Grigoriadis
//April 17th, 2013
//class.h
//This file contains the class definition for the GameInfo class, includes the libraries used, and some constants
//used throughout the program.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <algorithm>  // used for the standard template library
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>  //used for socket communication
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

#define MAXWORDS 21
#define MAXCHARS 41
#define MAXLENGTH 256

//Name: GameInfo
//Purpose: This class was created to hold all of the needed information about the game that is going to be played.
//			It holds the available characters, words, timelimit, score and the client socket number.
class GameInfo
{
private:

	string ListOfChars;
	string ListOfWords[MAXWORDS];
	int TimeLimit;
	int score;
	int ClientSocket;

public:

	GameInfo(void);
	~GameInfo(void);

	string getListOfChars(void);
	string *getListOfWords(void);
	int getTimeLimit(void);
	int getScore(void);
    int getClientSocket(void);
	bool setListOfChars(string newSetOfChars);
	bool setListOfWords(string *newSetOfWords);
	bool setTimeLimit(int newTimeLimit);
    bool setClientSocket(int socketToSet);
	void printGameInfo(void);
	void printGame(void);
	void printScore(void);
	void setScore(int newScore);
	GameInfo operator=( GameInfo b);

};

