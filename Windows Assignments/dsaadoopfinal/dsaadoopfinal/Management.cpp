//Mike Sadowski
//April 17th, 2013
//Management.cpp
//this file contains all of the method bodies for the Management class.

#include "Management.h"

//Constructor + Destructor

///
/// \brief <b>Brief Description</b> - Constructor
///
/// Constructor for the Management class.
/// Initializes the teamName, headCoach, assistantCoach strings to equal "NOTSET"
///	
/// \returns nothing
///
Management::Management(void)
{
	teamName = "NOTSET";
	headCoach = "NOTSET";
	assistantCoach = "NOTSET";
}


///
/// \brief <b>Brief Description</b> - Destructor 
///
/// This is the destructor for the Management class
///	
/// \returns nothing
///
Management::~Management(void)
{

}

//Accessors
///
/// \brief <b>Brief Description</b> - Accessor 
///
/// This is the Accessor for the Management class's variable: teamName
///	
/// \returns teamName (string)
///
const string Management::GetTeamName(void)
{
	return teamName;
}


///
/// \brief <b>Brief Description</b> - Accessor 
///
/// This is the Accessor for the Management class's variable: headCoach
///	
/// \returns headCoach (string)
///
const string Management::GetHeadCoach(void)
{
	return headCoach;
}


///
/// \brief <b>Brief Description</b> - Accessor 
///
/// This is the Accessor for the Management class's variable: assistantCoach
///	
/// \returns assistantCoach (string)
///
const string Management::GetAssistantCoach(void)
{
	return assistantCoach;
}

//Mutators
///
/// \brief <b>Brief Description</b> - Mutator 
///
/// This is the Mutator for the Management class's variable: teamName
/// It also validates all incoming data.
///	
/// \returns True/False if member was set or not
///
bool Management::SetTeamName(string newTeamName)
{

	//if the length is greater than MAXLENGTH, return false  since it's invalid
	if(newTeamName.length() > MAXLENGTH)
	{
		return false;
	}

	//return true if string passes the test, false if it doesn't
	if(CheckCharactersOfString(newTeamName))
	{
		teamName = newTeamName;
		return true;
	}
	else
	{
		return false;
	}
}


///
/// \brief <b>Brief Description</b> - Mutator 
///
/// This is the Mutator for the Management class's variable: headCoach
/// It also validates all incoming data.
///	
/// \returns True/False if member was set or not
///
bool Management::SetHeadCoach(string newHeadCoach)
{
	//if the length is greater than MAXLENGTH, return false  since it's invalid
	if(newHeadCoach.length() > MAXLENGTH)
	{
		return false;
	}

	//return true if string passes the test, false if it doesn't
	if(CheckCharactersOfString(newHeadCoach))
	{
		headCoach = newHeadCoach;
		return true;
	}
	else
	{
		return false;
	}
}


///
/// \brief <b>Brief Description</b> - Mutator 
///
/// This is the Mutator for the Management class's variable: assistantCoach
///	It also validates all incoming data.
/// 
/// \returns True/False if member was set or not
///
bool Management::SetAssistantCoach(string newAssistantCoach)
{
	//if the length is greater than MAXLENGTH, return false  since it's invalid
	if(newAssistantCoach.length() > MAXLENGTH)
	{
		return false;
	}

	//return true if string passes the test, false if it doesn't
	if(CheckCharactersOfString(newAssistantCoach))
	{
		assistantCoach = newAssistantCoach;
		return true;
	}
	else
	{
		return false;
	}
}

///
/// \brief <b>Brief Description</b> - Validator Function 
///
/// This function iterates through an array of available characters, and determines if a string passed in
/// contains a character that is not allowed.
///	
/// \returns True/False if string passed the test
///
bool Management::CheckCharactersOfString(string myString)
{
	//An array of all allowed characters 
	int AllowedChars[ARRAYSIZE] = {32, 33, 38, 40, 41, 43, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 93, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
	int x = 0;
	int y = 0;

	//Loop through array and check each character against the array of allowed characters
	for (x = 0; x < myString.length(); x++)
	{
		for(y = 0; y < ARRAYSIZE; y++)
		{
			if(myString[x] == AllowedChars[y])
			{
				//if a match was found, break from the first for loop
				break;
			}
			else
			{
				//If cycled through all allowed characters and hasn't found a match, return false 
				if(y == ARRAYSIZE-1)
				{
					return false;
				}
			}
		}
	}
	return true; //if return false wasn't hit, the string passed the test.
}

