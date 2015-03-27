//Mike Sadowski
//April 11th, 2013
//ultimateRadio.cpp
//This file contains the driver for the entire Pioneer Class family. It reads a command line argument, and creates an object
//of the correct radio type based on the command line argument, and allows the user to use it's features (volume, scan up/down, etc)
//Once the user presses X, the radio object is destroyed, and the program waits for the user to press C A W or X. When C is pressed,
//the program instatiates another object of type PioneerCarRadio, when A is pressed, it instatiates an object of type PioneerAm, when W
//is pressed, it instantiates an object of type PioneerWorld, and when X is pressed, the program exits.

#include "PioneerWorld.h"

PioneerCarRadio *createRadio(char *radioType);
PioneerCarRadio *processUserKeyPress(void);


int main(int argc, char* argv[])
{
	int ifExit = 0;

	PioneerCarRadio *pRadio = NULL;
	try
	{
		pRadio = createRadio(argv[1]);//send first cmd line arg to function...
	}
	catch(char *e)
	{
		printf("%s", e);//print exception if caught..
	}

	while (1)//loop until x is pressed twice within the program
	{
		ifExit = pRadio->processKeystrokes();//process keystrokes (scan up, down, band etc..)
		if(ifExit == EXITCODE)//if the user pressed x, destroy object
		{
			free(pRadio); //= NULL;
			try
			{
				pRadio = processUserKeyPress();//wait for user to press c a w or x 
			}
			catch(char *e)
			{
				printf("%s", e);//print exception if caught..
			}

			if(pRadio == NULL)
			{
				return EXITCODE;//exit program if user press X a second time..
			}
		}
	}
	
	return EXITCODE;
}

//NAME: processUserKeyPress
//DESCRIPTION: waits for a user to press c a w or x, and creates the appropriate radio object, or exit the program
//PARAMETERS:
//RETURN:
PioneerCarRadio *processUserKeyPress(void)
{
	PioneerCarRadio *NULLRETURN = NULL;
	PioneerCarRadio *CARtemp = NULL;
	PioneerAM *AMtemp = NULL;
	PioneerWorld *WRLDtemp = NULL;

	while(1)
	{
		switch(getch())
		{
			case 99:// 'c'
				CARtemp = new PioneerCarRadio;
				if(CARtemp == NULL)
				{
					throw "ERROR: OUT OF MEMORY";
				}
				return CARtemp;
				break;
			case 97:// 'a'
				AMtemp = new PioneerAM;
				if(AMtemp == NULL)
				{
					throw "ERROR: OUT OF MEMORY";
				}
				return AMtemp;
				break;
			case 119:// 'w'
				WRLDtemp = new PioneerWorld;
				if(WRLDtemp == NULL)
				{
					throw "ERROR: OUT OF MEMORY";
				}
				return WRLDtemp;
				break;
			case 120:// 'x'
				return NULLRETURN;//code to exit program..
				break;
		}//end switch
	}//end while
}


//NAME: createRadio
//DESCRIPTION: This function takes in a string, and determines which radio to instantiate, then returns that object.
//PARAMETERS: a string (the cmd line arg)
//RETURN: either a pointer to a PioneerCarRadio, PioneerAM or PioneerWorld object, or an exception.
PioneerCarRadio *createRadio(char *radioType)  
{
	PioneerCarRadio *NULLRETURN = NULL;

	if(strcmp(radioType, "-car") == 0)
	{
		PioneerCarRadio *temp = NULL;

		temp = new PioneerCarRadio;
		if(temp == NULL)
		{
			throw "ERROR: OUT OF MEMORY";
		}

		return temp;
	}
	if(strcmp(radioType,"-am") == 0)
	{
		PioneerAM *temp = NULL;

		temp = new PioneerAM;
		if(temp == NULL)
		{
			throw "ERROR: OUT OF MEMORY";
		}

		return temp;
	}

	if(strcmp(radioType, "-world") == 0)
	{
		PioneerWorld *temp = NULL;

		temp = new PioneerWorld;
		if(temp == NULL)
		{
			throw "ERROR: OUT OF MEMORY";
		}

		return temp;
	}

	throw "Command line argument was not -car -am or -world!";
	return NULLRETURN;
}

