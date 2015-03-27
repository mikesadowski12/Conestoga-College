//Mike Sadowski
//April 17th, 2013
//project.cpp
//This program allows a user to input soccer teams (team name, head coach, assistant coach, 11 starting players, 5 backup players)
//into a database to manage them. They can edit the teams, delete them, create them, display them, delete entire databases and load/save/display databases
//using a menu.

#include "Team.h"

using namespace std;

Team *PrintUI(Team *HeadOfLL, int *exitCode);
Team *CreateTeam(Team *HeadOfLL);
Team *EditTeam(Team *HeadOfLL);
Team *DeleteTeam(Team *HeadOfLL);
void DisplayTeam(Team *HeadOfLL);
void DisplayDatabase(Team *HeadOfLL);
void SaveDatabase(Team *HeadOfLL);
Team *LoadDatabase(Team *HeadOfLL);
void HelpMenu(void);
Team *AddNewNode(Team *newHead, Team teamObject);
Team *searchLinkedList(Team *HeadOfLL, string teamName);
Team EnterAttribute(int attributeNum, Team *teamObject);
void freeAll(Team *head);
Team *AddArbitraryItems(Team *HeadOfLL);


int main(void)
{
	Team *HeadOfLL = NULL;//pointer to head of the linked list
	int x = 0;
	char input = 0;
	int exitCode = 0;

	while(exitCode != 5)
	{
		HeadOfLL = PrintUI(HeadOfLL, &exitCode);
		input = getchar();
	}

	return 1;
}
///
/// \brief <b>Brief Description</b> - Prints User Interface 
///
/// Presents user with a menu to choose from to perform a function. 
/// 
/// \returns NONE
///
Team *PrintUI(Team *HeadOfLL, int *exitCode)
{
	int userInput;
	Team teamObject;//Stores information user enters
	Team *searchObject;

	cout << ">>>> SOCCER TEAM TRACKER v1.0 <<<<" << endl;//
	cout << ">>>    1.  Create Team         <<<" << endl;//
	cout << ">>>    2.  Edit Team           <<<" << endl;//
	cout << ">>>    3.  Delete Team         <<<" << endl;//
	cout << ">>>    4.  Display Team        <<<" << endl;//
	cout << ">>>    5.  Display Database    <<<" << endl;//
	cout << ">>>    6.  Save Database       <<<" << endl;//
	cout << ">>>    7.  Load Database       <<<" << endl;//
	cout << ">>>    8.  Delete Database     <<<" << endl;//
	cout << ">>>    9.  Exit (With Save)    <<<" << endl;//
	cout << ">>>    10. Exit (Without Save) <<<" << endl;//
	cout << ">>>    11. Help                <<<" << endl;//////
	cout << ">>>    12. Add Arbitrary Items <<<" << endl;
	//userInput = getchar();
	cin >> userInput;

	switch ( userInput )
      {
         case 1:
            HeadOfLL = CreateTeam(HeadOfLL);
            break;
         case 2:
            searchObject = EditTeam(HeadOfLL);
            break;
		case 3:
			HeadOfLL = DeleteTeam(HeadOfLL);
			break;
		case 4:
			DisplayTeam(HeadOfLL);
			break;
		case 5:
			system("CLS");
			cout << ">> Database Displayed:\n\n" << endl;
			DisplayDatabase(HeadOfLL);
			break;
		case 6:
			system("CLS");
			cout << ">> Database Saved!\n\n" << endl;
			SaveDatabase(HeadOfLL);
			break;
		case 7:
			system("CLS");
			cout << ">> Database Loaded!\n\n" << endl;
			HeadOfLL = LoadDatabase(HeadOfLL);
			break;
		case 8:
			system("CLS");
			cout << ">> Database Deleted!\n\n" << endl;
			freeAll(HeadOfLL);//Free entire linked list
			HeadOfLL = NULL;
			break;
		case 9:
			SaveDatabase(HeadOfLL);
			*exitCode = 5;
			break;
		case 10:
			freeAll(HeadOfLL);//Free entire linked list
			HeadOfLL = NULL;
			*exitCode = 5;
			break;
		case 11:
			system("CLS");
			HelpMenu();
			break;
		case 12:
			system("CLS");
			HeadOfLL = AddArbitraryItems(HeadOfLL);
			break;
         default:
			system("CLS");
			HeadOfLL = PrintUI(HeadOfLL, exitCode);
            break;
	}
	return HeadOfLL;
}

///
/// \brief <b>Brief Description</b> - Menu item #1 Create a team
///
/// Allows user to input a team name, head coach, assistant coach, 11 starting players and 5 backup players into the database.
/// 
/// \returns NONE
///
Team *CreateTeam(Team *HeadOfLL)
{
	Team teamObject;

	teamObject = EnterAttribute(ALLATTRIBUTES, &teamObject);

	HeadOfLL = AddNewNode(HeadOfLL, teamObject);//Add new team node to the linked list

	system("CLS");
	cout << ">> Team was successfully added to the database!" << endl;
	cout << endl;

	return HeadOfLL;
}

///
/// \brief <b>Brief Description</b> - Menu Item #2 Edit a team
///
/// Allows user to search for a team, and edit data within that team. 
/// 
/// \returns head of the linked list
///
Team *EditTeam(Team *HeadOfLL)
{
	Team *searchObject = NULL;
	char UserInput[MAXLENGTH] = {0};
	int userMenuInput = 0;

	fgets(UserInput, sizeof(UserInput), stdin);//clear keyboard buffer...
	system("CLS");
	cout << "Please enter the team name of the team you wish to edit: ";
	cin.getline(UserInput, MAXLENGTH);

	searchObject = searchLinkedList(HeadOfLL, (char*)UserInput);
	if(searchObject == NULL)
	{
		//if search was unable to find a match, loop until user enters a team in the database
		while(searchObject == NULL)
		{
			system("CLS");
			cout << ">> Team was not found! <<" << endl;
			cout << "Please re-enter the team name of the team you wish to edit: ";
			cin.getline(UserInput, MAXLENGTH);
			searchObject = searchLinkedList(HeadOfLL, UserInput);
		}
	}

	system("CLS");
	searchObject->PrintTeamInfo();
	cout << ">>> Enter which attribute you would like to change " << endl;
	cout << ">>> 1. Team Name         <<<" << endl;
	cout << ">>> 2. Head Coach        <<<" << endl;
	cout << ">>> 3. Assistant Coach   <<<" << endl;
	cout << ">>> 4. Starting Players  <<<" << endl;
	cout << ">>> 5. Backup Players    <<<" << endl;
	//fgets(userMenuInput, sizeof(UserInput), stdin);//clear keyboard buffer...
	cin >> userMenuInput;// = getchar();
	

	switch ( userMenuInput )
    {
         case 1:
			EnterAttribute(TEAMNAMEATTRIBUTENUM, searchObject);//change team name
			break;
         case 2:
			EnterAttribute(HEADCOACHATTRIBUTENUM, searchObject); //change head coach
			break;
		case 3:
			EnterAttribute(ASSISTANTCOACHATTRIBUTENUM, searchObject);//change assistant coach
			break;
		case 4:
			EnterAttribute(STARTERATRRIBUTENUM, searchObject);//change starting players
			break;
		case 5:
			EnterAttribute(BACKUPATRRIBUTENUM, searchObject);//change backup players
			break;
		default:
			system("CLS");
			cout << ">> Invalid Key! Returning to Main Menu! \n\n" <<endl;
            break;
	}
	return searchObject;
}
///
/// \brief <b>Brief Description</b> - Menu Item #3 Delete a team
///
/// Allows user to search for a team, and delete it from the database
/// 
/// \returns head of the linked list
///
Team *DeleteTeam(Team *HeadOfLL)
{
	Team *current = HeadOfLL;
	Team *previous;
	string UserInput;
	
	cout << "Please enter the name of the team you wish to delete: ";
	cin >> UserInput;

	//if there is no linked list to search yet, return null
	if (HeadOfLL == NULL)
	{
		return HeadOfLL;
	}

	do
	{
		//search the list for the name
		if(UserInput.compare(current->GetTeamName()) == 0)
		{
			previous->next = current->next;

			// finally, free the desired element
			free(current);
			return HeadOfLL;
		}
		//save the last node
		previous = current;
		current = current->next;

	}while (current != NULL);//keep going until match is found, or end of linked list
		
	//if nothing was found, return null
	return HeadOfLL;
}



///
/// \brief <b>Brief Description</b> - Menu Item #4 Display a team
///
/// Allows user to search for a team, and display the data within that team. 
/// 
/// \returns NONE
///
void DisplayTeam(Team *HeadOfLL)
{
	Team *searchObject = NULL;
	string UserInput;

	if(HeadOfLL != NULL)//only if there is a data base
	{
		system("CLS");
		cout << "Please enter the team name of the team you wish to display: ";
		cin >> UserInput;

		searchObject = searchLinkedList(HeadOfLL, UserInput);
		if(searchObject == NULL)
		{
			while(searchObject == NULL)
			{
				system("CLS");
				cout << ">> Team was not found! <<" << endl;
				cout << "Please re-enter the team name of the team you wish to display: ";
				cin >> UserInput;
				searchObject = searchLinkedList(HeadOfLL, UserInput);
			}
		}
		system("CLS");
		searchObject->PrintTeamInfo();
	}
	else
	{
		cout << ">> No database exists! <<" << endl;
	}
}

///
/// \brief <b>Brief Description</b> - Menu Item #5 Display database
///
/// Displays every item in the database for the user. 
/// 
/// \returns NONE
///
void DisplayDatabase(Team *HeadOfLL)
{
	Team *current = HeadOfLL;

	system("CLS");
	if(HeadOfLL != NULL)//only if there is a data base
	{
		do
		{
			current->PrintTeamInfo();

			current = current->next;
		}while(current != NULL);
	}
	else
	{
		cout << ">> No database exists! \n\n" << endl;
	}


}

///
/// \brief <b>Brief Description</b> - Menu Item #6 save database
///
/// Save all items in database into a textfile 
/// 
/// \returns NONE
///
void SaveDatabase(Team *HeadOfLL)
{
	Team *current = HeadOfLL;
	string* buffer;
	char *bufferForStarters = 0;
	string *starterArray = 0;
	string *backupArray = 0;
	char *teamName = 0;
	char *headCoach = 0;
	char *assistantCoach = 0;
	int x = 0;
	//FILE * pFile= fopen ("soccerDBASE.txt","w+");
	ofstream myfile;
	myfile.open("soccerDBASE.txt");

	teamName = (char *)calloc(1, sizeof (char));
	headCoach = (char *)calloc(1, sizeof (char));
	assistantCoach = (char *)calloc(1, sizeof (char));
	buffer = (string *)calloc(1, sizeof (string));

	do
	{
		strcpy(teamName, (current->GetTeamName()).c_str());
		strcpy(headCoach, current->GetHeadCoach().c_str());
		strcpy(assistantCoach, current->GetAssistantCoach().c_str());
		starterArray = (string*) current->GetStarters();
		backupArray = (string*)current->GetBackups();
		
		//print teamName, headCoach, assistantCoach seperated by *'s to buffer
		buffer->append(teamName);
		buffer->append("*");
		buffer->append(headCoach);
		buffer->append("*");
		buffer->append(assistantCoach);

		//append each starter player afterwards to the string, each seperated by *'s again
		for (x = 0; x < MAXSTARTERS; x++)
		{
			buffer->append("*");
			buffer->append(starterArray[x]);
		}

		//append each backup player afterwards to the string, each seperated by *'s again
		for (x = 0; x < MAXBACKUPS; x++)
		{
			buffer->append("*");
			buffer->append(backupArray[x]);			
		}

		buffer->append("*");
		myfile << *buffer << "\n";
		//go to next node of the database (linked list) and clear buffer
		buffer->clear();
		current = current->next;
	}while(current != NULL);	

	//close the file
	myfile.close();
}

///
/// \brief <b>Brief Description</b> - Menu Item #7 Load database
///
/// Load items to the database from a textfile 
/// 
/// \returns head of the linked list
///
Team *LoadDatabase(Team *HeadOfLL)
{
	FILE *myFile = NULL;
	int fileSize = 0;
	ifstream myfile("soccerDBASE.txt");
//	char *lineBuffer;
	char lineBuffer[BUFFERSIZE] = {0};
	string starters[MAXSTARTERS];
	string backups[MAXBACKUPS];
	int x = 0;
	int y = 0;
	int z = 0;
	Team teamObject;
	char tokenStrings[19][MAXLENGTH];

	myFile = fopen ("soccerDBASE.txt", "r");
	
	while(fgets(lineBuffer, BUFFERSIZE, myFile) != NULL)
	{
		for(x = 0; x < 19; x++)
		{
			if(x == 0)
			{
				strcpy(tokenStrings[x], strtok (lineBuffer, "*"));
			}
			else
			{
				strcpy(tokenStrings[x], strtok (NULL, "*"));
			}
		}

		for (y = 0; y < MAXSTARTERS; y++)
		{
			starters[y] = tokenStrings[y+3];
		}

		for (z = 0; z < MAXBACKUPS; z++)
		{
			backups[z] = tokenStrings[z+14];
		}

		teamObject.SetTeamName(tokenStrings[0]);
		teamObject.SetHeadCoach(tokenStrings[1]);
		teamObject.SetAssistantCoach(tokenStrings[2]);
		teamObject.SetStarters(starters);
		teamObject.SetBackups(backups);

		HeadOfLL = AddNewNode(HeadOfLL, teamObject);//Add new team node to the linked list
	}
	fclose(myFile);
	return HeadOfLL;
	//	
}//end func



	

///
/// \brief <b>Brief Description</b> - Menu Item #11 Help menu
///
/// Prints usage statement about the program. Everything not in the help menu is because it's self explanatory in the program
/// 
/// \returns NONE
///
void HelpMenu(void)
{
	int AllowedChars[ARRAYSIZE] = {32, 33, 38, 40, 41, 43, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 93, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
	int x = 0;

	system("CLS");
	cout << ">>> Help Menu <<<" << endl;
	cout << ">>> - text file to load database must be called: soccerDBASE.txt" << endl;
	cout << ">>> - Allowed characters:" << endl;
	for (x = 0; x < ARRAYSIZE; x++)
	{
		if(x %10 == 0 && x != 0 )
		{
			cout << endl;
		}

		printf("%c ", AllowedChars[x]);
	}
}


///
/// \brief <b>Brief Description</b> - Adds a node to the database 
///
/// This function stores a team object into a sorted linked list (sorted by the team name) (Copied from the slides and modified it)
/// 
/// \returns head of the linked list
///
// Function: AddNewNode
// Description: This function stores a team object into a sorted linked list (sorted by the team name) (Copied from the slides and modified it)
// Parameters: Parameter 1 - head pointer to the Team Linked List, Parameter 2 - a team object
// Return Value: returns pointer to the head of the Team linked list
Team *AddNewNode(Team *newHead, Team teamObject)
{
	Team *newBlock = NULL;
	Team *ptr = NULL;
	Team *prev = NULL;
	string test2;
	
	newBlock = (Team *)calloc(1, sizeof (Team));
	if( newBlock == NULL )
	{
		printf("Error: No memory\n");
		return NULL;
	}	

	//Set newBlock pointer to have all same attributes as the object passed in
	newBlock->SetTeamName(teamObject.GetTeamName());
	newBlock->SetHeadCoach(teamObject.GetHeadCoach());
	newBlock->SetAssistantCoach(teamObject.GetAssistantCoach());
	newBlock->SetStarters(teamObject.GetStarters());
	newBlock->SetBackups(teamObject.GetBackups());


	newBlock->next = NULL;

	if( newHead == NULL )
	{
		newHead = newBlock;
	} 

	else if( newHead->GetTeamName().compare(newBlock->GetTeamName()) >= 0 ) 
	{
		newBlock->next = newHead;
		newHead = newBlock;
	}

	else
	{
		prev = newHead;		
		ptr = newHead->next;	
	
		
	while( ptr != NULL )
	{
		if (ptr->GetTeamName().compare(newBlock->GetTeamName()) >= 0 )
		{
			break;
		}

		prev = ptr;
		ptr = ptr->next;

	}	

	newBlock->next = ptr;
	prev->next = newBlock;

	}	
	return newHead;
}	


///
/// \brief <b>Brief Description</b> - searches for a node in the database 
///
/// This function gets the name of a team, and compares the  name to see if it is identical to one in the linked list, 
///  and returns a pointer to the node that was matched.
/// 
/// \returns head of the linked list
///
// Function: searchLinkedList
// Description: This function gets the name of a team, and compares the  name to see if it is identical to one in the linked list, 
//               and returns a pointer to the node that was matched.
// Parameters: Parameter 1 - the name of a team, Parameter 2 - a pointer to the head of the Team Linked List
// Return Value: returns a pointer to the Team Linked List. Returns NULL if no match was made, or if there was no linked list to search
Team *searchLinkedList(Team *HeadOfLL, string teamName)
{
	Team *current = HeadOfLL;
	Team *next = NULL;

	//if there is no linked list to search yet, return null
	if (current == NULL)
	{
		return NULL;
	}

	do
	{
		//search the list for the name
		if(teamName.compare(current->GetTeamName()) == 0)
		{
			return current;
		}

		current = current->next;

	}while (current != NULL);//keep going until match is found, or end of linked list
		
	//if nothing was found, return null
	return NULL;
}

///
/// \brief <b>Brief Description</b> - Function allows user to enter data into the database. 
///
/// Function uses an attribute number to detect which attribute is being set (edit team), or if all are going to be set for create, and allows user to input their data and store it in the database
/// 
/// \returns head of the linked list
///
Team EnterAttribute(int attributeNum, Team *teamObject)
{
	char UserInput[MAXLENGTH];
	bool validation = false;
	int x = 0;
	string Starters[MAXSTARTERS];
	string Backups[MAXBACKUPS];
	Team returnObject;
	
	fgets(UserInput, MAXLENGTH, stdin);//clear the keyboard buffer from cin....
	if(attributeNum == TEAMNAMEATTRIBUTENUM || attributeNum == ALLATTRIBUTES )
	{
		//Set team name
		system("CLS");
		cout << "Please enter the team name: ";
		cin.getline(UserInput, MAXLENGTH);
		validation = teamObject->SetTeamName(UserInput);//change the variable to what the user entered
		//if variable was not set the first time, user entered incorrect characters. loop until correct team name is typed in,
		//or exit if user chooses to do so.
		if(validation == false)
		{
			while(validation != true)
			{
				system("CLS");
				cout << "(See help for allowed characters)" << endl;
				cout << "Please re-enter the team name: ";
				cin.getline(UserInput, MAXLENGTH);
				validation = teamObject->SetTeamName(UserInput);//try to change the team name
			}
		}
	}

	if(attributeNum == HEADCOACHATTRIBUTENUM ||attributeNum == ALLATTRIBUTES)
	{
		//Set head coach
		system("CLS");
		cout << "Please enter the head coach's name: ";
		cin.getline(UserInput, MAXLENGTH);
//		fgets(UserInput, sizeof(UserInput), stdin);
		validation = teamObject->SetHeadCoach(UserInput);//change the variable to what the user entered
		//if variable was not set the first time, user entered incorrect characters. loop until correct team name is typed in,
		//or exit if user chooses to do so.
		if(validation == false)
		{
			while(validation != true)
			{
				system("CLS");
				cout << "(See help for allowed characters)" << endl;
				cout << "Please re-enter the head coach's name: ";
				cin.getline(UserInput, MAXLENGTH);
				validation = teamObject->SetHeadCoach(UserInput);//change the variable to what the user entered
			}
		}
	}
	
	if(attributeNum == ASSISTANTCOACHATTRIBUTENUM ||attributeNum == ALLATTRIBUTES)
	{
		//Set assistant coach
		system("CLS");
		cout << "Please enter the assistant coach's name: ";
		cin.getline(UserInput, MAXLENGTH);
		validation = teamObject->SetAssistantCoach(UserInput);//change the variable to what the user entered
		//if variable was not set the first time, user entered incorrect characters. loop until correct team name is typed in,
		//or exit if user chooses to do so.
		if(validation == false)
		{
			while(validation != true)
			{
				system("CLS");
				cout << "(See help for allowed characters)" << endl;
				cout << "Please re-enter the assistant coach's name: ";
				cin.getline(UserInput, MAXLENGTH);
				validation = teamObject->SetAssistantCoach(UserInput);//change the variable to what the user entered
			}
		}
	}
	
	if(attributeNum == STARTERATRRIBUTENUM ||attributeNum == ALLATTRIBUTES)
	{
		//Set starting players
		for(x = 0; x < MAXSTARTERS; x++)
		{
			system("CLS");
			cout << "Please enter the starting player's name (Player " << x+1 << "): ";
			cin.getline(UserInput, MAXLENGTH);
			validation = teamObject->CheckCharactersOfString(UserInput);//Check each string entered one by one to ensure it's valid
			if(validation == false)//if it's not, loop until the user decides to exit or types in an acceptable string
			{
				while(validation != true)
				{
					system("CLS");
					cout << "(See help for allowed characters)" << endl;
					cout << "Please re-enter the starting player's name (Player " << x+1 << "): ";
					cin.getline(UserInput, MAXLENGTH);
					validation = teamObject->CheckCharactersOfString(UserInput);
				}
			}
			else
			{
				Starters[x] = UserInput;
			}			
		}
		teamObject->SetStarters(Starters);//finally, send the array to the mutator to set the starters.
	}
	
	if(attributeNum == BACKUPATRRIBUTENUM ||attributeNum == ALLATTRIBUTES)
	{
		//Set backup players
		for(x = 0; x < MAXBACKUPS; x++)
		{
			system("CLS");
			cout << "Please enter the backup player's name (Player " << x+1 << "): ";
			cin.getline(UserInput, MAXLENGTH);
			validation = teamObject->CheckCharactersOfString(UserInput);//Check each string entered one by one to ensure it's valid	
			if(validation == false)//if it's not, loop until the user decides to exit or types in an acceptable string
			{
				while(validation != true)
				{
					system("CLS");
					cout << "(See help for allowed characters)" << endl;
					cout << "Please re-enter the backup player's name (Player " << x+1 << "): ";
					cin.getline(UserInput, MAXLENGTH);
					validation = teamObject->CheckCharactersOfString(UserInput);
				}
			}
			else
			{
				Backups[x] = UserInput;
			}			
		}
		teamObject->SetBackups(Backups);//finally, send the array to the mutator to set the starters.
	}

	returnObject.SetTeamName(teamObject->GetTeamName());
	returnObject.SetHeadCoach(teamObject->GetHeadCoach());
	returnObject.SetAssistantCoach(teamObject->GetAssistantCoach());
	returnObject.SetStarters(teamObject->GetStarters());
	returnObject.SetBackups(teamObject->GetBackups());

	return returnObject;
}


/*
 * Function: freeAll()
 * Description: This function removes all items from the linked list. (not my function, copied from Carlo's examples and slighty modified)
 * Parameters: personInfo *head: start of linked list
 * Returns: nothing
*/
void freeAll(Team *head)
{
	Team *curr = NULL, *next = NULL;

	curr = head;  

	// traverse the list, being careful to not access freed blocks
	while( curr != NULL )
	{
		// keep a pointer to the next block so we can go there after it's freed
		next = curr->next; 
		free(curr);
		curr = next;
	}
}
///
/// \brief <b>Brief Description</b> - Menu item #12 add arbitrary amount of item to database
///
/// This adds an arbitrary amount of item to database.
/// 
/// \returns head of the linked list
///
Team *AddArbitraryItems(Team *HeadOfLL)
{
	int UserInput = 0;
	int x = 0;
	Team teamObject;
	string teamName = "TEAM NAME";
	string headCoach = "HEAD COACH";
	string assistantCoach = "ASSISTANT COACH";
	string starters[MAXSTARTERS] = {"STARTER 1", "STARTER 2", "STARTER 3", "STARTER 4", "STARTER 5", "STARTER 6", "STARTER 7", "STARTER 8", "STARTER 9", "STARTER 10", "STARTER 11"};
	string backups[MAXSTARTERS] = {"BACKUP 1", "BACKUP 2", "BACKUP 3", "BACKUP 4", "BACKUP 5"};

	cout << "Please enter how many items you wish to add: ";
	cin >> UserInput;

	while(x <= UserInput)
	{
		teamObject.SetTeamName(teamName);
		teamObject.SetHeadCoach(headCoach);
		teamObject.SetAssistantCoach(assistantCoach);
		teamObject.SetStarters(starters);
		teamObject.SetBackups(backups);
		HeadOfLL = AddNewNode(HeadOfLL, teamObject);//Add new team node to the linked list

		x++;
	}

	return HeadOfLL;
}