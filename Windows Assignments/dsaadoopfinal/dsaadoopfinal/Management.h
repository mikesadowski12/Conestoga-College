//Mike Sadowski
//April 17th, 2013
//Management.h
//this file contains the class definition for the Mangement class.
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

#define ARRAYSIZE 100
#define MAXSTARTERS 11 
#define MAXBACKUPS 5
#define MAXLENGTH 255
#define BUFFERSIZE 1000

#define TEAMNAMEATTRIBUTENUM 100
#define HEADCOACHATTRIBUTENUM 101
#define ASSISTANTCOACHATTRIBUTENUM 102
#define STARTERATRRIBUTENUM 103
#define BACKUPATRRIBUTENUM 104
#define ALLATTRIBUTES 105

/** 
* \class Management
*
* \brief <b>Brief Description</b> - Class representing the management/staff of a soccer team
*
* This class replicates the management and staff of a soccer team. It contains the name of the head coach, assistant coach, and what
* the name of the soccer team is. It also contains a function that is used to verify all names of players/coaches on the team, and checks
* if the string contains characters that are not supposed to be a part of the person's name.
*
* 
* - class constants:  
*   - TEAMNAMEATTRIBUTENUM indicates a change to the team name is wanted
*   - HEADCOACHATTRIBUTENUM indicates a change to the head coach name is wanted
*   - ASSISTANTCOACHATTRIBUTENUM indicates a change to the assitant coach name is wanted
*   - STARTERATRRIBUTENUM indicates a change to the starters is wanted 
*   - BACKUPATRRIBUTENUM indicates a change to the backups is wanted
*   - ALLATTRIBUTES indicates a change to the team name is wanted
*   - ARRAYSIZE is the max array size 
*   - MAXSTARTERS max amount of starters allowed (11)
*   - MAXBACKUPS max amount of backups allowed (5)
*   - MAXLENGTH max length of user input (255 characters)
*   - BUFFERSIZE max length of a buffer (1000 characters)
* 
* - class data members (attributes):
*   - string teamName; contains the name of the team
*   - string headCoach; contains the name of the head coach
*   - string assistantCoach; contains the name of the assistant coach
*
*
* \author <i>Mike Sadowski</i>
*/
class Management
{

private:
	string teamName;
	string headCoach;
	string assistantCoach;

public:

	//Constructor + Destructor
	Management(void);
	~Management(void);

	//Accessors
	const string GetTeamName(void);
	const string GetHeadCoach(void);
	const string GetAssistantCoach(void);

	//Mutators
	bool SetTeamName(string newTeamName);
	bool SetHeadCoach(string newHeadCoach);
	bool SetAssistantCoach(string newAssistantCoach);

	bool CheckCharactersOfString(string myString);//Checks all characters of a string to see if they are acceptable

};