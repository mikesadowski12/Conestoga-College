#include "class.h"



//PROTOTYPES
GameInfo OpenFileAndProcessContents(char *filename, GameInfo myGame);
GameInfo ParseTextFileContents(char *contents, GameInfo myGame);
void PrintHelp(void);
void PlayGame(GameInfo myGame);
bool IsNotEmpty( const std::string& str );


int main(int argc, char* argv[]) 
{
	char i = 0;
	GameInfo myGame;
	bool SetYesNo = false;
	
	//checks to see if theres 3 arguments on the command line (program name, input file, time limit)
	if (argc != 3)
	{
		PrintHelp();
		return 1;
	}

	//Set the game time limit, and check to see if it was inputted correctly, if not exit program.
	SetYesNo = myGame.setTimeLimit(atoi(argv[2]));
	if(SetYesNo != true)
	{
		PrintHelp();
		return 1;
	}

	//Open the file, parse out the contents, and save into the myGame object. 
	//This is now the entire set up of the game
	myGame = OpenFileAndProcessContents(argv[1], myGame);

	//Start playing the game that was instantiated
	PlayGame(myGame);

	i = getch();
	return 0;
	
}



void PlayGame(GameInfo myGame)
{
	int NumCorrectGuesses = 0;
	int CorrectOrNot = 4; //started at 4 so messages don't print on first time th
	int x = 0;
	int z = 0;
	string inputGuess;
	string wordHolder;
	string CorrectWords[MAXWORDS];
	string *AvailableWords = myGame.getListOfWords();
	int TotalWords = std::count_if(AvailableWords, &AvailableWords[MAXWORDS], IsNotEmpty); //Get total amount of available words
	int points = 0;
	int timer = 0;
	time_t start,end;//start time and end time
	int minutes = myGame.getTimeLimit();

	time (&start); //start timer

	while(timer < minutes * 60)//Convert minutes to seconds
	{
		if(TotalWords == NumCorrectGuesses)
		{
			break;
		}

		//clear cmd prompt window
		system("CLS");

		if(CorrectOrNot == 4)
		{
			printf("\n>> Start Guessing! <<\n\n");
		}

		//If CorrectOrNot is equal to 1, the word was in the list
		if(CorrectOrNot == 1)
		{
			printf("\n>> Word Correct! %d/%d words found! <<\n\n", NumCorrectGuesses, TotalWords);
		}

		//If CorrectOrNot is equal to 0, the word was not in the list
		if(CorrectOrNot == 0)
		{
			printf("\n>> Word Incorrect! %d/%d words found! <<\n\n", NumCorrectGuesses, TotalWords);
		}

		//If CorrectOrNot is equal to 2, the word was already entered
		if(CorrectOrNot == 2)
		{
			printf("\n>> Word Already Entered! %d/%d words found! <<\n\n", NumCorrectGuesses, TotalWords);
		}

		//Reset the CorrectOrNot count
		CorrectOrNot = 0;

		myGame.printGame();

		printf("\n>> Type in the word: ");
		cin >> inputGuess;

		for(x = 0; x < MAXWORDS; x++)
		{
			//Check if the word was already guessed..
			if(inputGuess.compare(CorrectWords[x]) == 0)
			{
				CorrectOrNot = 2;
				break;
			}

			//Check if the word is correct..
			if(inputGuess.compare(*(AvailableWords + x)) == 0)
			{
				CorrectWords[z] = inputGuess;
				NumCorrectGuesses++;
				CorrectOrNot = 1;
				z++;
				break;
			}
		}

		time (&end);
		timer = difftime (end,start);
	}

	//Tally up the points..
	for(x = 0; x < TotalWords; x++)
	{
		wordHolder = CorrectWords[x];
		points += wordHolder.length();
	}

	//clear cmd prompt window and print game results..
	system("CLS");
	printf("\n>> Game Is Finished! %d/%d words found! <<\n\n", NumCorrectGuesses, TotalWords);
	myGame.printGame();
	printf("\nYour Score: %d\n\n\n\n\n", points);
	printf("\n >> Press any key to quit << ");
}

//Not my function..
//Source: http://stackoverflow.com/questions/5739384/how-to-find-number-of-elements-in-an-array-of-strings-in-c
bool IsNotEmpty( const std::string& str )
{
    return !str.empty();
}

//NAME: OpenFileAndProcessContents
//DESCRIPTION: This function opens a specified file name from the command line, and parses out the string of characters,
//			   and the words that are found in the string of characters, and saves the data to the GameInfo object also passed in.
//PARAMETERS: 1 - The name of a file to open, 2 - a GameInfo object
//RETURN: A GameInfo object
GameInfo OpenFileAndProcessContents(char *filename, GameInfo myGame)
{
	FILE * InputFile;
	char* buffer = 0;
	int sizeoffile = 0;
	string newSetOfWords[MAXWORDS];
	string LinesOfFile[MAXWORDS];
	string newSetOfChars;
	char BuildWord[MAXLENGTH] = {0};
	int x = 0;
	int y = 0;
	int z = 0;
	int AmountOfWordsCopied = 0;
	
	//Open the input file name
	InputFile = fopen(filename, "rb");

	//Check if input file was opened, if it did read it into a buffer.
	if (InputFile == NULL)
	{
		printf(">> Error: Cannot open INPUT file");
		return myGame;
	}
	//Find out file size
	fseek(InputFile , 0 , SEEK_END);
	sizeoffile = ftell(InputFile);
	fseek(InputFile , 0 , SEEK_SET);

	//allocate memory to read file into it
	buffer = (char*) calloc((sizeoffile+1), sizeof(char));
	
	fread(buffer, sizeof(char) , sizeoffile, InputFile);
	if(strlen(buffer) > 0)
	{
		for(x = 0; x < sizeoffile; x++)
		{
			BuildWord[z++] = buffer[x];

			//If a carraige return is hit
			if(buffer[x] == 13)
			{
				BuildWord[z-1] = '\0'; //terminate the string each time, removing the carriage return
				LinesOfFile[y] = BuildWord;
				x++;
				y++;
				z = 0;
				AmountOfWordsCopied++;
			}

			//End of file is reached
			if(x == sizeoffile - 1)
			{
				BuildWord[z] = '\0'; //terminate the string each time, removing the carriage return
				LinesOfFile[y] = BuildWord;
				y++;
				z = 0;
				AmountOfWordsCopied++;
			}
		}
	}

	//First line of array is the characters, copy into a new variable
	newSetOfChars = LinesOfFile[0];

	//Copy the set of available words into a string array
	for(x = 0; x < AmountOfWordsCopied; x++)
	{
		newSetOfWords[x] = LinesOfFile[x+1];
	}

	//Setup the myGame object to contain all needed information
	myGame.setListOfChars(newSetOfChars);
	myGame.setListOfWords(newSetOfWords);

	//close file, and free memory
	fclose (InputFile);
	free (buffer);

	//Return the myGame object with all required information stored in it
	return myGame;
}



//NAME: PrintHelp
//DESCRIPTION: Prints the help/usage statements of the program
//PARAMETERS: NONE
//RETURN: NONE
void PrintHelp(void)
{
	cout << "Please specify 3 arguments: [programname.exe] [filename.txt] [timelimit]" << endl;
	cout << ">> [filename.txt] is arbitrary" << endl;
	cout << ">> [timelimit] must be a single integer that isgreater than 0, and in minutes" << endl;
}

