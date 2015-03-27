//AmfmRadio.cpp
//Mike Sadowski Feburary 26, 2013
//This file contains all of the method bodies for the AmfmRadio class.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "amfmRadio.h"

AmfmRadio::AmfmRadio(void)
{
	for( int i = 0; i < 5; ++i )
	{
		button[i].AMFreq = 530;
	}
	for( int j = 0; j < 5; ++j )
	{
		button[j].FMFreq = 87.9;
	}
	current_station = 530;
	strcpy(frequency, "AM");
	volume = 0;
	on = false;
}

int AmfmRadio::SetVolume()
{
char buf[20] = "";

	printf("\nEnter the volume level (0 - 100). ");
	fgets(buf, sizeof buf, stdin);
	volume = atoi(buf);

	if( volume < 0 ) //if user enters volume less than 0, volume = 0
	{
		volume = 0;
		return 0;
	}

	if( volume > 100 ) //if user enters volume greater than 100, volume = 100
	{
		volume = 100;
		return 2;
	}
	return 1;
}

int AmfmRadio::SetVolume(int newVolume)
{
	volume = newVolume;

	if( volume < 0 ) //if user enters volume less than 0, volume = 0
	{
		volume = 0;
		return 0;
	}

	if( volume > 100 ) //if user enters volume greater than 100, volume = 100
	{
		volume = 100;
		return 2;
	}
	return 1;

}

int AmfmRadio::SetButton(int button_num)
{
	if( (button_num >= 0) && (button_num <= 4) )
	{
		if( strcmp("AM", frequency) == 0 )
		{
			button[button_num].AMFreq = (int) current_station;
		}
		else
		{
			button[button_num].FMFreq = (float) current_station;
		}
		return 1;

	}
	return 0;
}

int AmfmRadio::SelectCurrentStation(int button_num)
{
	if( (button_num >= 0) && (button_num <= 4) )
	{
		if( strcmp("AM", frequency) == 0 )
		{
			current_station = button[button_num].AMFreq;
		}
		else
		{
			current_station = button[button_num].FMFreq;
		}

		return 1;
	}
	return 0;
}

void AmfmRadio::ShowCurrentSettings()
{

	if( on == true )
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", frequency);
	printf("Volume: %d\n", volume);
	printf("Current Station: %.1f %s\n", current_station, frequency);
	printf("AM Button Settings: ");
	for( int i = 0; i < 5; ++i )
	{
		printf("%d) %6d ", i + 1, button[i].AMFreq);
	}

	printf("\nFM Button Settings: ");
	for( int j = 0; j < 5; ++j )
	{
		printf("%d) %6.1f ", j + 1, button[j].FMFreq);
	}
}


/*-------------------------------------*/
/* ALL THE FUNCTIONS I CREATED/EDITED BELOW! */
/*-------------------------------------*/


	/**
	* \brief <b>Brief Description</b> - Constructor <b><i>class method</i></b> - called upon to construct an AmFmRadio
	* \details <b>Details</b>
	* <b>NAME:</b> AmfmRadio
	* <b>PARAMETERS:</b> bool OnOff - a bool to turn instantiate a radio that is on/off
	* <b>DESCRIPTION:</b> This method constructs a AmFmRadio, by taking in a parameter to indicate if the radio is on or off, and setting default values.
	* <b>RETURN:</b> NONE
	* 
	*
	*/
AmfmRadio::AmfmRadio(bool OnOff)
{
	for( int i = 0; i < 5; ++i )
	{
		button[i].AMFreq = 530;
	}
	for( int j = 0; j < 5; ++j )
	{
		button[j].FMFreq = 87.9;
	}
	current_station = 530;
	strcpy(frequency, "AM");
	volume = 0;
	on = OnOff;
}




	/**
	* \brief <b>Brief Description</b> - Constructor <b><i>class method</i></b> - called upon to construct an AmFmRadio
	* \details <b>Details</b>
	* <b>NAME:</b> AmfmRadio
	* <b>PARAMETERS:</b> bool OnOff - a bool to turn instantiate a radio that is on/off, Freqs buttons[5] - 5 Freq buttons
	* <b>DESCRIPTION:</b> This method constructs a AmFmRadio, by taking in a parameter to indicate if the radio is on or off, Freqs buttons to set the preset buttons.
	* <b>RETURN:</b> NONE
	*
	*/
AmfmRadio::AmfmRadio(bool OnOff, Freqs buttons[5])
{
	for( int i = 0; i < 5; ++i )
	{
		button[i].AMFreq = 530;
	}
	for( int j = 0; j < 5; ++j )
	{
		button[j].FMFreq = 87.9;
	}
	current_station = 530;
	strcpy(frequency, "AM");
	volume = 0;
	on = OnOff;
}




	/**
	* \brief <b>Brief Description</b> - Destructor <b><i>class method</i></b> - called upon to destroy an AmFmRadio
	* \details <b>Details</b>
	* <b>NAME:</b> ~AmfmRadio
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> destructor for AmfmRadio class
	* <b>RETURN:</b> NONE
	* 
	*
	*/
AmfmRadio::~AmfmRadio()
{
	printf("Destroying AmfmRadio");
}




	/**
	* \brief <b>Brief Description</b> - Turns on Radio <b><i>class method</i></b> - called upon to set the radio datamember "on"
	* \details <b>Details</b>
	* <b>NAME:</b> PowerToggle
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> toggles radio power on/off saving the previous frequency and station so that when turned back on,
	*              radio resumes the last frequency, station and volumeit was on. If it is turned on for the first time, 
	*              the volume is set to 0.
	* <b>RETURN:</b> NONE
	*
	*/
void AmfmRadio::PowerToggle()
{
	Freqs previous;
	char prevFreq[3] = {0};
	int prevVolume = 0;

	if( on == false )
	{
		on = true;

		//will also set volume to 0 if prevVolume has not been set before,
		//meaning the radio have been turned on for the first time.
		volume = prevVolume;

		strcpy(frequency,prevFreq);

		if( strcmp(frequency, "AM") == 0 )
		{
			current_station = previous.AMFreq;
		}
		else
		{
			current_station = previous.FMFreq;
		}

	}
	else
	{
		on = false;

		prevVolume = volume;
		volume = 0;

		if( strcmp(frequency, "AM") == 0 )
		{
			previous.AMFreq = current_station;
			strcpy(prevFreq, "AM");
		}
		else
		{
			previous.FMFreq = current_station;
			strcpy(prevFreq, "FM");
		}
	}
}




	/**
	* \brief <b>Brief Description</b> - Scans the frequence up <b><i>class method</i></b> - called upon to change the current_station data member
	* \details <b>Details</b>
	* <b>NAME:</b> ScanUp
	* <b>PARAMETERS:</b> bool display - indicator whether to turn output on or off
	* <b>DESCRIPTION:</b> functions scans up through the stations on the "radio"
	* <b>RETURN:</b> NONE
	*
	*/
void AmfmRadio::ScanUp(bool display)
{
	if( strcmp("AM", frequency) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( current_station == 1700 )
		{
			current_station = 530;
		}
		else
		{
			current_station = current_station + 10;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if( current_station >= 107.9 )
		{
			current_station = 87.9;
		}
		else
		{
			current_station = current_station + .2;
		}
	}

	//optional display
	if(display != false)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}




	/**
	* \brief <b>Brief Description</b> - Scans the frequence down <b><i>class method</i></b> - called upon to change the current_station data member
	* \details <b>Details</b>
	* <b>NAME:</b> ScanDown
	* <b>PARAMETERS:</b> bool display - indicator whether to turn output on or off
	* <b>DESCRIPTION:</b> functions scans down through the stations on the "radio"
	* <b>RETURN:</b> NONE
	*
	*/
void AmfmRadio::ScanDown(bool display)
{
	if( strcmp("AM", frequency) == 0 )
	{
		//if current_station is 530, the current_station becomes 1700
		if( current_station == 530)
		{
			current_station = 1700;
		}
		else
		{
			current_station = current_station - 10;
		}
	}
	else
	{
		//if the current_station is 87.9, the current_station becomes 107.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if( current_station >= 87.9 )
		{
			current_station = 107.9;
		}
		else
		{
			current_station = current_station - .2;
		}
	}

	//optional display
	if(display != false)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}

}




	/**
	* \brief <b>Brief Description</b> - Scans the frequency up <b><i>class method</i></b> - called upon to change the frequency data member
	* \details <b>Details</b>
	* <b>NAME:</b> ToggleFrequency
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> toggles between the 2 frequencies of AM and FM, saving the last current station on each frequencies.
	* <b>RETURN:</b> NONE
	* 
	*
	*/
void AmfmRadio::ToggleFrequency()
{
	Freqs previous;

	if( strcmp(frequency, "AM") == 0 )
	{
		previous.AMFreq = current_station;
		strcpy(frequency, "FM");
		current_station = previous.FMFreq;
	}
	else
	{
		previous.FMFreq = current_station;
		strcpy(frequency, "AM");
		current_station = previous.FMFreq;
	}
}


	/**
	* \brief <b>Brief Description</b> - Mutator <b><i>class method</i></b> - called upon to change the current_station data member
	* \details <b>Details</b>
	* <b>NAME:</b> SetCurrentStation
	* <b>PARAMETERS:</b> double newCurrent_station - the value of the new station that the radio will change to
	* <b>DESCRIPTION:</b> mutator for the current_station attribute in the AmfmRadio class.
	* <b>RETURN:</b> NONE
	*
	*/
void AmfmRadio::SetCurrentStation(double newCurrent_station)
{
	current_station = newCurrent_station;
}


	/**
	* \brief <b>Brief Description</b> - Accessor <b><i>class method</i></b> - called upon to access the button data member
	* \details <b>Details</b>
	* <b>NAME:</b> getButton
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> accessor for the button attribute in the AmfmRadio class
	* <b>RETURN:</b> returns the buttons
	*
	*/
const Freqs* AmfmRadio::getButton(void)
{
	return button;
}



	/**
	* \brief <b>Brief Description</b> - Accessor <b><i>class method</i></b> - called upon to access the current_station data member
	* \details <b>Details</b>
	* <b>NAME:</b> getCurrent_station
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> accessor for the current_station attribute in the AmfmRadio class
	* <b>RETURN:</b> Returns the current station 
	*
	*/
const double AmfmRadio::getCurrent_station(void)
{
	return current_station;
}


	/**
	* \brief <b>Brief Description</b> - Accessor <b><i>class method</i></b> - called upon to access the frequency data member
	* \details <b>Details</b>
	* <b>NAME:</b> getFrequency
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> accessor for the frequency attribute in the AmfmRadio class
	* <b>RETURN:</b> returns the frequency
	*
	*/
const char* AmfmRadio::getFrequency(void)
{
	return frequency;
}



	/**
	* \brief <b>Brief Description</b> - Accessor <b><i>class method</i></b> - called upon to access the volume data member
	* \details <b>Details</b>
	* <b>NAME:</b> getVolume
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> accessor for the volume attribute in the AmfmRadio class
	* <b>RETURN:</b> returns the volume
	* 
	*
	*/
const int AmfmRadio::getVolume(void)
{
	return volume;
}


	/**
	* \brief <b>Brief Description</b> - Accessor <b><i>class method</i></b> - called upon to access the on data member
	* \details <b>Details</b>
	* <b>NAME:</b> getOn
	* <b>PARAMETERS:</b> NONE
	* <b>DESCRIPTION:</b> accessor for the on attribute in the AmfmRadio class
	* <b>RETURN:</b> returns if the radio is on or off by true/false state.
	*
	*/
const bool AmfmRadio::getOn(void)
{
	return on;
}