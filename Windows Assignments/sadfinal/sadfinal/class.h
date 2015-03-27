#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <time.h>

using namespace std;

#define MAXWORDS 21
#define MAXCHARS 41
#define MAXLENGTH 256

class GameInfo
{
private:

	string ListOfChars;
	string ListOfWords[MAXWORDS];
	int TimeLimit;

public:

	GameInfo(void);
	~GameInfo(void);

	string getListOfChars(void);
	string *getListOfWords(void);
	int getTimeLimit(void);

	bool setListOfChars(string newSetOfChars);
	bool setListOfWords(string *newSetOfWords);
	bool setTimeLimit(int newTimeLimit);

	void printGameInfo(void);
	void printGame(void);
};