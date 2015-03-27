//Mike Sadowski
//April 17th, 2013
//team.cpp
//this file contains all of the method bodies for the Team class.

#include "Team.h"

//Constructor + Destructor
///
/// \brief <b>Brief Description</b> - Constructor
///
/// Constructor for the Team class.
/// Initializes the 11 starters and 5 backup player's names as "NOTSET"
///	
/// \returns nothing
///
Team::Team(void)
{
	int x = 0;

	for(x = 0; x < 11; x++)
	{
		starters[x] = "NOTSET";
	}

	for(x = 0; x < 5; x++)
	{
		backups[x] = "NOTSET";
	}

	next = NULL;
}


///
/// \brief <b>Brief Description</b> - Destructor
///
/// Destructor for the Team class.
///	
/// \returns nothing
///
Team::~Team(void)
{

}


//Accessors
///
/// \brief <b>Brief Description</b> - Accessor 
///
/// This is the Accessor for the Team class's variable: starters[]
///	
/// \returns an array of strings (11 starting player's names)
///
const string* Team::GetStarters(void)
{
	return starters;
}


///
/// \brief <b>Brief Description</b> - Accessor 
///
/// This is the Accessor for the Team class's variable: backups[]
///	
/// \returns an array of strings (5 backups player's names)
///
const string* Team::GetBackups(void)
{
	return backups;
}


//Mutators
///
/// \brief <b>Brief Description</b> - Mutator 
///
/// This is the Mutator for the Team class's variable: starters
/// It also validates all incoming data.
///	
/// \returns bool array if the member at that index was set or not
///
bool *Team::SetStarters(const string newStarters[])
{
	int x = 0;
	bool NODESET[11] = {false};

	//if the length is greater than MAXLENGTH, exit right away since it's invalid
	for(x = 0; x < MAXSTARTERS; x++)
	{
		if(newStarters[x].length() > MAXLENGTH)
		{
			return false;
		}
	}

	//Check to see if characters in string are acceptable
	for(x = 0; x < MAXSTARTERS; x++)
	{
		if(CheckCharactersOfString(newStarters[x]))
		{
			starters[x] = newStarters[x];
			NODESET[x] = true;
		}
		else
		{
			NODESET[x] = false;
		}
	}

	return NODESET;
}


///
/// \brief <b>Brief Description</b> - Mutator 
///
/// This is the Mutator for the Team class's variable: backups[]
/// It also validates all incoming data.
///	
/// \returns bool array if the member at that index was set or not
///
bool* Team::SetBackups(const string newBackups[])
{
	int x = 0;
	bool NODESET[11] = {false};

	//if the length is greater than MAXLENGTH, exit right away since it's invalid
	for(x = 0; x < MAXBACKUPS; x++)
	{
		if(newBackups[x].length() > MAXLENGTH)
		{
			return false;
		}
	}

	//Check to see if characters in string are acceptable
	for(x = 0; x < MAXBACKUPS; x++)
	{
		if(CheckCharactersOfString(newBackups[x]))
		{
			backups[x] = newBackups[x];
			NODESET[x] = true;
		}
		else
		{
			NODESET[x] = false;
		}
	}

	return NODESET;
}


///
/// \brief <b>Brief Description</b> - Prints Team Information 
///
/// This function prints the teams information in a very neat way.
/// Format: ">>Team Name: "
///	        ">>Head Coach: "
///         ">>Assistant Coach: "
///         ">>Starting Players: "
///         ">>Backup Players: "
/// \returns NONE
///
void Team::PrintTeamInfo(void)
{
	int x = 0; 

	
	cout << ">>Team Name: " << GetTeamName() << endl;
	cout << ">>Head Coach: " << GetHeadCoach() << endl;
	cout << ">>Assistant Coach: " << GetAssistantCoach() << endl;
	cout << ">>Starting Players: " << endl;

	//Print starting players
	for(x = 0; x < MAXSTARTERS; x++)
	{
		//Skip printing the first comma so output doesn't look ugly..
		if(x == 0)
		{
			cout << "    ";
			cout << starters[x];
			x++;
		}

		//Every 5 players, print a new line, and keep printing players seperated by commas.
		if(x % 5 == 0 && x != 0)
		{
			cout << endl;
			cout << "    ";
			cout << starters[x];
		}
		else
		{
			cout << ", " << starters[x] ;
		}
	}

	cout << endl;

	//Print backup players
	cout << ">>Backup Players: " << endl;
	for(x = 0; x < MAXBACKUPS; x++)
	{
		if(x == 0)
		{
			cout << "    ";
		}
		if(x == 4)
		{
			cout << backups[x] << endl;
		}
		else
		{
			cout << backups[x] << ", ";
		}
	}

	//Print a seperator to seperate teams, and cleanup the output.
	cout << "-------------------------------------------------------------------------------" << endl;
}




