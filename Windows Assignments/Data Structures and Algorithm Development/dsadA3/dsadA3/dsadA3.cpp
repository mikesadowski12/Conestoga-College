// Mike Sadowski
// 4-4-2013
// This program reads nicknames and real names of students from a text file, and then scans for sub directories (which are the student submissions), and sorts their name and nickname
// into a container called NicknameHead. With the help of the first container, it makes a second container that stores the students name and nickname, and the directory that goes with the student 
// into a container called StudentHead, and prints both container afterwards. Both container are sorted by the student's real name. After it has made both of the lists, the program then scans each subdirectory for the student's
// files, copies all of the files into a _allFiles directory, and (using the StudentHead container) appends their nickname and a hyphen to the front of all the files, so that each file in the main
// directory can be distinguished based on the student's nickname. It ignores all directories starting with a "_", as well as all sub directories with student's names not on the list. If the nickname file
// cannot be opened, an error message is displayed and the program terminates.



#include "student_class.h"
#pragma


//FUNCTION PROTOTYPES
std::set<Nickname> ProcessNicknameFile(std::set<Nickname> &NicknameHead);
std::set<Student> getFiles(std::set<Student> &head, std::set<Nickname> &NicknameHead);
Student* GetNicknameNode(char* dirName, std::set<Nickname> &NicknameHead);
char* GetStudentNameFromDirectory(char* dirName);
Student *AddNewStudentNode(Student *newHead, char* dirName, char* StudentName, char* NickName);

void CopyFiles(std::set<Student> &head, char* DestinationDirName);
void PrintStudentContainer(std::set<Student> &StudHead);
void PrintNicknameContainer(std::set<Nickname> &NickHead);



int main(void)
{
	//initialize containers
	set<Nickname> NicknameHead;
	set<Student> StudentHead;
	
	NicknameHead = ProcessNicknameFile(NicknameHead);

	StudentHead = getFiles(StudentHead, NicknameHead);

	//Print both containers
	PrintNicknameContainer(NicknameHead);
	PrintStudentContainer(StudentHead);

	CopyFiles(StudentHead, "_allFiles");	
	return 1;
}




// Function: ProcessNicknameFile
// Description: This function opens and reads the nicknames.txt file, and determines the student's nickname, and their real name from it. It then calls
//				AddNewNicknameNode to store the student's name and nickname into a set STL container
// Parameters: Parameter 1 - 
// Return Value: returns pointer to the head of the Nickname linked list
std::set<Nickname> ProcessNicknameFile(std::set<Nickname> &NicknameHead)
{
	FILE *NicknamesFile = NULL;
	char buffer[MAXLENGTH] = {0};
	int spacelocation = 0;
	int x = 0;
	char nickname[MAXLENGTH] = {0};
	char realname[MAXLENGTH] = {0};
	
	//Open nicknames.txt and checks to see if it opened
	NicknamesFile = fopen ("nicknames.txt", "r");
    if(NicknamesFile == NULL)
	{
        printf( "Error opening Nickname file\n");
		//if not, return the head of the linked list and do not copy anything into it
        return NicknameHead;
    }

	//loop until end of the file
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
		//insert nickname and real name to container
		NicknameHead.insert(Nickname(realname, nickname));
	}

	//close nicknames.txt
	fclose(NicknamesFile);

	//always return the pointer to the head of the linked list
	return NicknameHead;
}




// Function: GetStudentNameFromDirectory
// Description: This function gets the name of a directory (format: FIRSTNAME LASTNAME MM-DD-YYYY OPT#(if provided)) and parses out the student's first and last name, and appends them together into
//				one string, to form the complete student name.
// Parameters: Parameter 1 - the name of a directory
// Return Value: returns the student's name
char* GetStudentNameFromDirectory(char* dirName)
{
	char dirNameCpy[MAXDIRLENGTH] = {0}; 
	char *Token = 0;
	char Tokens[10][MAXLENGTH] = {0,0};
	char StudentName[MAXLENGTH] = {0};
	int TokenCount = 0;
	int i = 0;

	//make a copy of directory name
	strcpy(dirNameCpy, dirName);

	//copy the string up until the first space into Tokens, and since it will always be the first name of the student,
	//go ahead and copy that into the StudentName string
	strcpy(Tokens[i], strtok(dirNameCpy, " "));
	strcat(StudentName, Tokens[i]);

	do
	{
		i++;
		//look for the next space in the dirNameCpy string
		Token = strtok(NULL, " ");

		//check if the space was found or not
		if(Token != NULL)
		{
			//copy the cut up string into Tokens[i]
			strcpy(Tokens[i], Token);

				//if the string is not a number then it is a part of the student's name, and copy into the StudentName string
				if(!isdigit(Token[0]))
				{
					strcat(StudentName, " ");
					strcat(StudentName, Token);
				}
		}
	}while(Token != NULL);

	TokenCount = i; //keep the count of how many times the string got cut up into pieces

	//returns the parsed student's name
	return StudentName;
}



// Function: *GetNicknameNode
// Description: This function gets the name of a directory, and uses the GetStudentNameFromDirectory function to get the exact student name out of the 
//				directory name, and compares the two name to see if they are identical, and returns a pointer to the node that was matched, so that later
//				all the needed information stored in the previous Nickname linked list can be easily trasnfered into a new list, that will contain the 
//				directory name of the student, and their nickname, etc.
// Parameters: Parameter 1 - the name of a directory, Parameter 2 - a pointer to the head of the Nickname Linked List
// Return Value: returns a pointer to the Nickname Linked List. Returns NULL if no match was made, or if there was no linked list to search
Student* GetNicknameNode(char *dirName, std::set<Nickname> &NicknameHead)
{
	//SEARCH FOR NICKNAME FROM DIRECTORY
	char realName[100] = {0};
	set<Nickname>::iterator p = NicknameHead.begin();
	Student *ReturnStudent = NULL;

	strcpy(realName, GetStudentNameFromDirectory(dirName));

	//while(p != NicknameHead.end())
	//{
		p = NicknameHead.find(realName);
		if (p != NicknameHead.end())
		{			
			ReturnStudent = new Student((char*)(&*p->getRealName()),
				(char*)(&*p->getNickName()), dirName);
			return ReturnStudent;
		}

		*p++;
	//}
	return ReturnStudent;
}



// Function: getFiles
// Description: This function scans the current directory, and determines the name of a sub directory (the students name and date and optional number), and uses the GetNicknameNode function to find
//				the node that matches the Student to the sub directory based on the name to extract their nickname. The students name, their directory name, and their nickname is then put into a 
//				Student conatiner.
// Parameters: Parameter 1 - head of a Student container, Parameter 2 - head of a Nickname container
// Return Value: returns head of student container
std::set<Student>  getFiles(std::set<Student> &head, std::set<Nickname> &NicknameHead)
{
	char dirName[MAXLENGTH] = {0};
	std::set<Nickname> NicknamePtr;
	Student *AddNewStudent;

	WIN32_FIND_DATA fileData = {0};
	HANDLE handle = FindFirstFile("*.*", &fileData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		printf("Error >> File not found");
		return head;
	}
	else
	{
		do
		{
			//Checks to see if the file found is a directory or not
			if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			{
				if (strcmp(fileData.cFileName, ".") != 0 && 
					strcmp(fileData.cFileName, "..") !=0 && 
					fileData.cFileName[0] != '_')
				{
					AddNewStudent = GetNicknameNode(fileData.cFileName, NicknameHead);
					head.insert(*AddNewStudent);
				}
			}
		//keep looping until no files are left
		}while (FindNextFile(handle, &fileData) != 0);

	FindClose(handle);
	return head;
	}
}



// Function: CopyFiles
// Description: This function cycles through all of the subdirectories in the current directories, finds the files in it, then it uses a pointer to a linked list to search the linked list,
//			    and appends the name of the file with the appropriate student's nickname, and copies the appended files to the appropriate destination directory (in this case it will be _allFiles)
// Parameters: Parameter 1 - a pointer to the head of the Student Linked List, Parameter 2 - the name of the destination directory (in this case it will be _allFiles)
// Return Value: None
void CopyFiles(std::set<Student> &head, char* DestinationDirName) 
{
	WIN32_FIND_DATA fileData = {0};
	HANDLE handle = 0;
	char SourceDirPath[MAXDIRLENGTH] = {0};
	char SourceFilePath[MAXDIRLENGTH] = {0};
	char SourceDirPathCpy[MAXDIRLENGTH] = {0};
	char DirName[MAXLENGTH] = {0};
	char FileName[MAXLENGTH] = {0};
	char FinalDestDir[MAXDIRLENGTH] = {0};
	char FinalFilePath[MAXDIRLENGTH] = {0};
	int CopiedFile = 0;
	set<Student>::iterator p = head.begin();

	//make destination directory name 
	//No need to error check, it will create the directory if it's not there, and not create it if it is there
	CreateDirectory(DestinationDirName, 0);

	//LOOP THROUGH THE CONTAINER AND THROUGH THE SUB DIRECTORY TO FIND FILES, APPEND THEM AS NEEDED, AND COPY THEM OUT TO DestinationDirName
	do
	{
		//get folder name from current node
		strcpy(DirName, (char*)(&*p->getDirectoryName()));
		//strcat(DirName, "\\");

		//make source directory name
		strcpy(SourceDirPath, DirName);

		strcat(SourceDirPath,"\\*.*");
		//get first file name
		handle = FindFirstFile(SourceDirPath, &fileData);

		//Checks to see if FindFirstFile returned a handle or not (meaning it found a file or not)
		if (handle == INVALID_HANDLE_VALUE)
		{
			printf("Error >> File not found");
		}
		else
		{
		//loop through the rest of files in the sub directory
			do
			{
				//checks to see if there is a folder or a file in the sub directory
				if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
					//if it is a folder in the sub directory, don't do anything to it..
				}
				else
				{
					//Re-initialize paths for every loop 
					strcpy(SourceDirPathCpy ,SourceDirPath);
					strcpy(FinalDestDir, DestinationDirName);
					strcat(FinalDestDir, "\\");

					//copy the file name into a blank string
					strcpy(FileName, fileData.cFileName);
					//Take out the *.* at the end of the source File Path, and append the file name that was found.
					SourceDirPathCpy[strlen(SourceDirPathCpy)-3] = 0;
					//Make the source file path
					strcat(SourceDirPathCpy, FileName);

					//add nickname to filename
					strcat(FinalDestDir, &*p->getNickName());
					strcat(FinalDestDir, "-");
					//make destination file path
					strcat(FinalDestDir, FileName);

					//Copy the file with the new name to the final destination directory
					CopyFile(SourceDirPathCpy, FinalDestDir, 0);
				}
				
			}while (FindNextFile(handle, &fileData) != 0);
			*p++;
		}

	//keep looping until end of the list
	}while(p != head.end());
	FindClose(handle);
}



// Function: PrintStudentContainer
// Description: This function prints the Student Container
// Parameters: Parameter 1 - head of a Student Container
// Return Value: None
void PrintStudentContainer(std::set<Student> &StudHead)
{
	set<Student>::iterator p = StudHead.begin();
	cout << "\n\nPRINTING THE STUDENT CONTAINER!\n" << endl;
	while(p != StudHead.end()) 
	{
		cout << ((char*)(&*p->getStudentName()));
		cout << " ";
		cout << ((char*)&*p->getNickName()) ;
		cout << " ";
		cout << ((char*)(&*p->getDirectoryName()));
		cout << endl;
		*p++;
	}
}



// Function: PrintNicknameLinkedList
// Description: This function prints the Nickname Container
// Parameters: Parameter 1 - head of a Nickname Container
// Return Value: None
void PrintNicknameContainer(std::set<Nickname> &NickHead)
{
	set<Nickname>::iterator p = NickHead.begin();

	cout << "\n\nPRINTING THE NICKNAME CONTAINER!\n" << endl;
	while(p != NickHead.end()) 
	{
		cout << (char*)(&*p->getRealName());
		cout << " ";
		cout << ((char*)&*p->getNickName()) ;
		cout << " ";
		cout << endl;
		*p++;
	}
}

