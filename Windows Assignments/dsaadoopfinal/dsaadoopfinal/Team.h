//Mike Sadowski
//April 17th, 2013
//team.h
//this file contains the class definition for the Team class.

/** 
* \class Team
*
* \brief <b>Brief Description</b> - Class representing the players of a soccer team
*
* This class replicates the players a soccer team. It contains the name of all 11 starting players, and the 5 backup players.
* It inherits from the Management class, which is used to hold the information about the coaches and the team's name, while this
* class only holds information about the players.
*
* 
* - class constants:  
*   - MAXSTARTERS max amount of starters allowed (11)
*   - MAXBACKUPS max amount of backups allowed (5)
*   - MAXLENGTH max length of user input (255 characters)
*   - BUFFERSIZE max length of a buffer (1000 characters)
* 
* - class data members (attributes):
*   - string starters[MAXSTARTERS]; an array of the 11 starting player's names
*   - string backups[MAXBACKUPS]; an array of the 5 backup player's names
*   - Team *next; a Team pointer that is used to create a linked list of many objects type Team
*
*
* \author <i>Mike Sadowski</i>
*/
#include "Management.h"

class Team: public Management
{

private:
	string starters[MAXSTARTERS];
	string backups[MAXBACKUPS];
	
public:

	Team *next;

	//Constructor + Destructor
	Team(void);
	~Team(void);

	//Accessors
	const string* GetStarters(void);
	const string* GetBackups(void);

	//Mutators
	bool* SetStarters(const string newStarters[]);
	bool* SetBackups(const string newBackups[]);

	void PrintTeamInfo(void);//Print team information

};