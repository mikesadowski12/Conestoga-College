// Mike Sadowski
// March 16th, 2013
// This file contains all the method bodies used for the PioneerCarRadioClass


#include "pioneerCarRadio.h"

	/**
	* \brief <b>Brief Description</b> - Constructor - <b><i>class method</i></b> - Constructs a PioneerCarRadio
	* \details <b>Details</b>
	*
	* <b>NAME:</b> PioneerCarRadio
	* <b>DESCRIPTION:</b> Constructs a PioneerCarRadio, constructor for the PioneerCarRadio class
	* <b>PARAMETERS:</b> NONE
	* <b>RETURN:</b> NONE
	* 
	*
	*/
PioneerCarRadio::PioneerCarRadio(void)
{	
	
}
	/**
	* \brief <b>Brief Description</b> - Destructor - <b><i>class method</i></b> - Destroys a PioneerCarRadio
	* \details <b>Details</b>
	*
	* <b>NAME:</b> ~PioneerCarRadio
	* <b>DESCRIPTION:</b> Destroys a PioneerCarRadio, destructor for the PioneerCarRadio class
	* <b>PARAMETERS:</b> NONE
	* <b>RETURN:</b> Returns nothing, just prints the message "Pioneer Radio destroyed... "
	* 
	*
	*/
PioneerCarRadio::~PioneerCarRadio(void)
{
	printf("Pioneer Radio destroyed... ");
}

//NAME: processKeystrokes
//DESCRIPTION: Gets a character from the user, and processes the command to perform the desired action.
//PARAMETERS: NONE
//RETURN: returns code for a exit, NOEXIT to not exit, and EXITCODE to exit
	/**
	* \brief <b>Brief Description</b> - Processes User Input - <b><i>class method</i></b> - called to process input
	* \details <b>Details</b>
	*
	* <b>NAME:</b> processKeystrokes
	* <b>DESCRIPTION:</b> Function is used to process the characters pressed by the user, and performs the desired actions based on the keystroke
	* <b>PARAMETERS:</b> NONE
	* <b>RETURN:</b> An integer that indicates whether or not to exit the program (2 for yes, 1 for no)
	* 
	*
	*/
int PioneerCarRadio::processKeystrokes(void)
{
	int curVol = 0;
	int volume_OK = 0;
	bool on = true;
	bool off = false;
	char buf[20] = {0};
	int exitProgram = 0;
	int newVol = 0;

	curVol = PioneerCarRadio::getVolume(); //get the current volume level

	switch(getch()) 
	{
		case 111:// On/Off 'o'
			PioneerCarRadio::PowerToggle();
			break;

		case 43:// Volume Up '+'
			newVol = curVol + 1;
			volume_OK = PioneerCarRadio::SetVolume(newVol);
			if( volume_OK == 0 )
			{
				printf("\nPIONEER: Volume was set to 0.\n\n");
			}
			else if( volume_OK == 2 )
			{
				printf("\nPIONEER: Volume was set to 100.\n\n");
			}
			break;

		case 95:// Volume Down '_'
			newVol = curVol - 1;
			volume_OK = PioneerCarRadio::SetVolume(newVol);
			if( volume_OK == 0 )
			{
				printf("\nVolume was set to 0.");
			}
			else if( volume_OK == 2 )
			{
				printf("\nVolume was set to 100.");
			}
			break;
		case 61:// Scan Up '='
			on = PioneerCarRadio::IsRadioOn();
			if( on )
			{
				PioneerCarRadio::ScanUp(off);
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan button!\n");
			}
			break;

		case 45:// Scan Down '-'
			on = PioneerCarRadio::IsRadioOn();
			if( on )
			{
				PioneerCarRadio::ScanDown(off);
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan button!\n");
			
			}
			break;

		case 98:// Switch Band 'b'
			on = PioneerCarRadio::IsRadioOn();
			if( on )
			{
				PioneerCarRadio::ToggleFrequency();  
			}
			else
			{
				printf("\nThe radio must be turned on before the "
					"band can be toggled!");
			}
			break;

		// Choose Button 1-5 '1 2 3 4 5'
		case 49: 
			PioneerCarRadio::chooseButton(1);
			break;
		case 50:
			PioneerCarRadio::chooseButton(2);
			break;
		case 51:
			PioneerCarRadio::chooseButton(3);
			break;
		case 52:
			PioneerCarRadio::chooseButton(4);
			break;
		case 53:
			PioneerCarRadio::chooseButton(5);
			break;

		// Set Button 1-5 'Shift+1 Shift+2 Shift+3 Shift+4 Shift+5'
		case 33: 
			PioneerCarRadio::programButtons(1);
			break;
		case 64:
			PioneerCarRadio::programButtons(2);
			break;
		case 35:
			PioneerCarRadio::programButtons(3);
			break;
		case 36:
			PioneerCarRadio::programButtons(4);
			break;
		case 37:
			PioneerCarRadio::programButtons(5);
			break;
			

		case 120:// Exit 'x'
			exitProgram = EXITCODE;
			break;
	}

	//Always print the current seetings
	PioneerCarRadio::printPioneerCarRadio();

	//Return code to exit program or not
	if(exitProgram == EXITCODE)
	{
		return EXITCODE;
	}
	else
	{
		return NOEXIT;
	}
}


	/**
	* \brief <b>Brief Description</b> - Prints Radio Settings - <b><i>class method</i></b> - called upon to print the state of all data members
	* \details <b>Details</b>
	*
	* <b>NAME:</b> printPioneerCarRadio
	* <b>DESCRIPTION:</b> Function is used to print the state of all data members, in an organized way.
	* <b>PARAMETERS:</b> NONE
	* <b>RETURN:</b> NONE
	* 
	*/
void PioneerCarRadio::printPioneerCarRadio(void)
{
	printf("Pioneer XS440");
	PioneerCarRadio::ShowCurrentSettings();
}

	/**
	* \brief <b>Brief Description</b> - Allows user to change the station <b><i>class method</i></b> - called upon to change the current_station according to the saved button
	* \details <b>Details</b>
	*
	* 
	* <b>NAME:</b> chooseButton
	* <b>DESCRIPTION:</b> Called to change the current_station according to station that was saved to the button previously.
	* <b>PARAMETERS:</b> Button Number as an integer
	* <b>RETURN:</b> NONE
	*
	*/
void PioneerCarRadio::chooseButton(int newButton)
{
	int button_OK = 0;
	bool on = true;

	on = PioneerCarRadio::IsRadioOn();
	if( on )
	{
		button_OK = PioneerCarRadio::SelectCurrentStation(newButton);
		if( button_OK == 0 )
		{
			printf("\nYou entered an invalid button number!");
		}
	}
	else
	{
		printf("\nYou must turn the radio on before you set the buttons!\n");
	}
}
	/**
	* \brief <b>Brief Description</b> - Allows user to change a button's preset <b><i>class method</i></b> - called upon to change the current_station that is saved to the button
	* \details <b>Details</b>
	*
	* <b>NAME:</b> programButtons
	* <b>DESCRIPTION:</b> Called to change the current_station that is saved in that button, so that the station is saved and can be accessed again by pressing the button
	* <b>PARAMETERS:</b> Button Number as an integer
	* <b>RETURN:</b> NONE
	* 
	*
	*/
void PioneerCarRadio::programButtons(int newButton)
{
	int button_OK = 0;
	bool on = true;

	on = PioneerCarRadio::IsRadioOn();
	if( on )
	{
		button_OK = PioneerCarRadio::SetButton(newButton);
		if( button_OK == 0 )
		{
			printf("\nYou entered an invalid button number!");
		}
	}
	else
	{
		printf("\nYou must turn the radio on before you set the buttons!\n");
	}

}