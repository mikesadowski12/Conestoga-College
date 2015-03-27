//Mike Sadowski
//March 4th, 2013
//This program collects data from nicknames.txt, and inputs the nicknames and real names from the text file into a 
//sorted linked list, as well as a hash table, and then allows the user to search for a name. The program will then
//output how many cycles it took to find the name in the linked list, and how many cycles it took to find the name in 
//the hash table

#include "nicknameStruct.h"

#pragma warning( disable : 4996)

//PROTOTYPES
Nickname *ProcessNicknameFile(Nickname *head, Nickname HashTable[]);
Nickname *GetNicknameNode(char* searchName, Nickname *NicknameHead);
Nickname *AddNewNicknameNode(Nickname *newHead, char* nickname, char* realname);
unsigned long hash(unsigned char *str);
void addNodeToHashTable(Nickname *HashTable[], char *nickname, char *realname);



int main(void)
{
	//initialize linked lists as NULL
	Nickname *NicknameHead = NULL;
	Nickname *pSearchLL = NULL;
	Nickname *pSearchH = NULL;
	Nickname HashTable[BUCKETS] = {0};
	char searchName[MAXLENGTH] = {0};
	int hashNum = 0;
	


	NicknameHead = ProcessNicknameFile(NicknameHead, &HashTable);
	if(NicknameHead == NULL)
	{
		return ERRORLEVEL;
	}


	

	while(1)
	{
		printf("\nEnter name to search (First Last): \n");
		fgets(searchName, sizeof(searchName), stdin);

		//get rid of the last control character that was at the end of the string ..
		if(searchName[strlen(searchName)-1] < 33)
		{
			searchName[strlen(searchName)-1] = 0;
		}

		if(strcmp(searchName, "QUIT") == 0)
		{
			return 1;
		}

		//Search the linked list, which will also display the results (the number of times it strcmp was called)
		//and return a pointer to the persons "node"
		pSearchLL = GetNicknameNode(searchName, NicknameHead);

		hashNum = hash(searchName);

		//Search the hash table, which will also display the results (the number of times it strcmp was called)
		//and return a pointer to the persons "node"
		pSearchH = GetNicknameNode(searchName, &HashTable[hashNum]);
	}
	
}



// Function: ProcessNicknameFile
// Description: This function opens and reads the nicknames.txt file, and determines the person's nickname, and their real name from it. It then calls
//				AddNewNicknameNode/addNodeToHashTable to store the name and nickname into a sorted linked list and hash table
//				(sorted by the name) 
// Parameters: Parameter 1 - head pointer to the Nickname Linked List
// Return Value: returns pointer to the head of the Nickname linked list
Nickname *ProcessNicknameFile(Nickname *head, Nickname (*HashTable)[BUCKETS])
{
	FILE *NicknamesFile = NULL;
	char buffer[MAXLENGTH] = {0};
	int spacelocation = 0;
	int x = 0;
	int spacecounter = 0;
	char nickname[MAXLENGTH] = {0};
	char realname[MAXLENGTH] = {0};
	
	//Open nicknames.txt and checks to see if it opened
	NicknamesFile = fopen ("nicknames.txt", "r");
    if(NicknamesFile == NULL)
	{
        printf( "Error opening Nickname file\n");
		//if not, return the head of the linked list and do not copy anything into it
        return NULL;
    }

	while(fgets(buffer, MAXLENGTH, NicknamesFile) != NULL)
	{
		for(x = 0; x < MAXLENGTH; x++)
		{
			//copies the first word into the nickname string up until the first space is reached (the end of the nickname)
			if(buffer[x] != ' ')
			{
				nickname[x] = buffer[x];
				nickname[x+1] = '\0'; //terminate the string each time
			}
			else
			{
				//copy from x+1 to avoid the space that was left in the string
				strcpy(realname, (buffer+x+1));

				//Not sure if it was because I was writing this on a mac, but everytime I read in the nicknames.txt, I would get an extra character (ascii 10)
				//at the end of my strings, which caused me a lot of problems later on...
				//Delete any extra character from end of the line from the text file
				if(realname[strlen(realname)-1] < 33)
				{
					realname[strlen(realname)-1] = 0;
				}

				break;

			}
		}
		//send the head pointer, nickname, and the real name of the student to the linked list, and reset space counter
		head = AddNewNicknameNode(head, nickname, realname);
		addNodeToHashTable(HashTable, nickname, realname);
		spacecounter = 0;
	}

	//close nicknames.txt
	fclose(NicknamesFile);

	//always return the pointer to the head of the linked list
	return head;
}

void addNodeToHashTable(Nickname *HashTable, char *nickname, char *realname)
{
	int HashValue = 0;
	Nickname *pBucket = NULL;

	//get the hash value 
	HashValue = hash(realname);

	//set up a pointer where to store the node
	pBucket = &HashTable[HashValue];
	//store the node in the correct place in the hash table
	AddNewNicknameNode(pBucket, nickname, realname);

}

// Function: AddNewNicknameNode
// Description: This function stores the person's name and nickname into a sorted linked list (sorted by the student's name) (Copied from the slides and modified it)
// Parameters: Parameter 1 - head pointer to the Nickname Linked List, Parameter 2 - the student's nickname, Parameter 3 - the name of the student
// Return Value: returns pointer to the head of the Nickname linked list
Nickname *AddNewNicknameNode(Nickname *newHead, char* nickname, char* realname)
{
	Nickname *newBlock = NULL;
	Nickname *ptr = NULL;
	Nickname *prev = NULL;
	
	newBlock = (Nickname *)malloc(sizeof (Nickname));
	if( newBlock == NULL )
	{
		printf("Error: No memory\n");
		return NULL;
	}	

	strcpy(newBlock->NickName, nickname);
	strcpy(newBlock->RealName, realname);
	newBlock->next = NULL;

	if( newHead == NULL )
	{
		newHead = newBlock;
	} 

	else if( strcmp(newHead->RealName, newBlock->RealName) >= 0 ) 
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
		if (strcmp(ptr->RealName, newBlock->RealName) >= 0 )
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



// Function: *GetNicknameNode
// Description: This function gets the name of a person, and compares the  name to see if it is identical to one in the linked list, 
//               and returns a pointer to the node that was matched, and prints how many times it searched.
// Parameters: Parameter 1 - the name person, Parameter 2 - a pointer to the head of the Nickname Linked List
// Return Value: returns a pointer to the Nickname Linked List. Returns NULL if no match was made, or if there was no linked list to search
Nickname *GetNicknameNode(char* searchName, Nickname *NicknameHead)
{
	Nickname *current = NicknameHead;
	Nickname *next = NULL;
	int compareCount = 0;

	//if there is no linked list to search yet, return null
	if (current == NULL)
	{
		return NULL;
	}

	do
	{
		//search the list for the name
		if(strcmp(searchName, current->RealName) == 0)
		{
			printf("\n%s was found in the linked list in %d comparisons", searchName, compareCount);
			return current;
		}
		else
		{
			compareCount++;
		}

		//set pointer to next, to continue through the linked list
		current = current->next;

	}while (current != NULL);//keep going until match is found, or end of linked list
		
	//if nothing was found, return null and print message
	printf("\n%s was not found in the linked list in %d comparisons", searchName, compareCount);
	return NULL;
}

//NAME: hash
//DESCRIPTION: makes a hash value for a string (copied from slides)
//PARAMETERS: a string
//RETURN: the hash value
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c = 0;

	while((c = *str++) != '\0')
	{
		hash = ((hash << 5) + hash) + c;
	}
	
	hash = hash % BUCKETS;

	return hash;
}



 
 