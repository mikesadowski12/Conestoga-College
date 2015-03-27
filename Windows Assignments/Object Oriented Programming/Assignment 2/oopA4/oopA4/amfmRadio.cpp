//Mike Sadowski
//April 11th, 2013
//amfmRadio.cpp
// This file contains all the method bodies for the AmfmRadio class.

#include "amfmRadio.h"


//NAME: AmfmRadio
//DESCRIPTION: constructor 1 for AmfmRadio class
//PARAMETERS: a bool that sets the radio on/off
//RETURN: NONE
AmfmRadio::AmfmRadio(bool OnOff)
{
	for( int i = 0; i < 5; ++i )
	{
		button[i].AMFreq = MINAM;
	}
	for( int j = 0; j < 5; ++j )
	{
		button[j].FMFreq = MINFM;
	}
	current_station = MINAM;
	strcpy(frequency, "AM");
	volume = 0;
	prevVolume = 0;
	on = OnOff;
	outPut = false;
	prevFreq.AMFreq = MINAM;
	prevFreq.FMFreq = MINFM;
}



//NAME: AmfmRadio
//DESCRIPTION: constructor 2 for AmfmRadio class
//PARAMETERS: a bool that sets the radio on/off, and an array of 5 struct Freqs
//RETURN: NONE
AmfmRadio::AmfmRadio(bool OnOff, Freqs buttons[5])
{

	for( int i = 0; i < 5; ++i )
	{
		button[i].AMFreq = buttons[i].AMFreq;
	}
	for( int j = 0; j < 5; ++j )
	{
		button[j].FMFreq = buttons[j].FMFreq;
	}
	current_station = 530;
	strcpy(frequency, "AM");
	volume = 0;
	prevVolume = 0;
	on = OnOff;
	outPut = false;
}



//NAME: ~AmfmRadio
//DESCRIPTION: destructor for AmfmRadio class
//PARAMETERS: NONE
//RETURN: NONE
AmfmRadio::~AmfmRadio(void)
{
	if(outPut == true)
	{
		printf("Destroying AmfmRadio");
	}
}


//NAME: PowerToggle
//DESCRIPTION: turns a radio on/off, if turning it on it returns the volume to the previous, and off sets the volume to 0
//PARAMETERS: NONE
//RETURN: NONE
void AmfmRadio::PowerToggle(void)
{
	if( on == false )
	{
		volume = prevVolume;
		on = true;
	}
	else
	{
		prevVolume = volume;
		volume = 0; //turn the volume off
		on = false;
	}
}

int AmfmRadio::SetVolume(void)
{
	char buf[20] = "";
	int checkReturn = 1;

	printf("\nEnter the volume level (0 - 100). ");
	fgets(buf, sizeof buf, stdin);
	checkReturn = SetVolume(atoi(buf));//so that code isn't reused, use the other set volume to set the volume 

	return checkReturn;
}

//NAME: SetVolume
//DESCRIPTION: sets the volume to the parameter being passed in
//PARAMETERS: an integer that is to be the new volume
//RETURN: returns 0 if the volume was less than 0, and returns 2 if it was greater than 100
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


void AmfmRadio::ToggleFrequency(void)
{
	if( strcmp(frequency, "AM") == 0 )
	{
		strcpy(frequency, "FM");
		current_station = 87.9;
	}
	else
	{
		strcpy(frequency, "AM");
		current_station = 530;
	}
}

int AmfmRadio::SetButton(int button_num)
{
	if( (button_num > 0) && (button_num <= 5) )
	{
		if( strcmp("AM", frequency) == 0 )
		{
			button[button_num-1].AMFreq = (int) current_station;//button_num - 1 to get the corrent index..
		}
		else
		{
			button[button_num-1].FMFreq = (float) current_station;//button_num - 1 to get the corrent index..
		}
		return 1;

	}
	return 0;

}

int AmfmRadio::SelectCurrentStation(int button_num)
{
	if( (button_num > 0) && (button_num <= 5) )
	{
		if( strcmp("AM", frequency) == 0 )
		{
			SetCurrentStation(button[button_num-1].AMFreq);//button_num-1 to get the corrent index...
		}
		else
		{
			SetCurrentStation(button[button_num-1].FMFreq);//button_num-1 to get the corrent index...
		}

		return 1;
	}
	return 0;


}

void AmfmRadio::ShowCurrentSettings(void)
{

	if( on == true )
	{
		printf("\nRadio is on. \n");
		printf("Volume: %d\n", volume);
		printf("Current Station: %.1f %s\n", current_station, frequency);
		printf("AM Buttons: \n");
		for( int i = 0; i < 5; ++i )
		{
			printf("%d: %6d, ", i + 1, button[i].AMFreq);
		}
		if(strcmp(GetName(), "Pioneer XS440-AM") != 0 && strcmp(GetName(), "Pioneer XS440-WRLD") != 0)//if its not a world or am radio print fm.
		{
			printf("\nFM Buttons: \n");
			for( int j = 0; j < 5; ++j )
			{
				printf("%d: %6.1f, ", j + 1, button[j].FMFreq);
			}
		}
	}
	else
	{
		printf("\nRadio is off. \n");
	}


}



//NAME: ScanUp
//DESCRIPTION: scans the current_station data member up, if outPut is true, the function will produce output
//PARAMETERS: NONE
//RETURN: NONE
void AmfmRadio::ScanUp(void)
{
	if( strcmp("AM", frequency) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( current_station >= MAXAM )
		{
			SetCurrentStation(MINAM);
		}
		else
		{
			SetCurrentStation((current_station+10));
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if( current_station >= MAXFM )
		{
			SetCurrentStation(MINFM);
		}
		else
		{
			SetCurrentStation((current_station+.2));
		}
	}

	if(outPut == true)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}



//NAME: SetCurrentStation
//DESCRIPTION: mutator for the current_station data member
//PARAMETERS: the new current_station as a double
//RETURN: true or false whether the data member was set
bool AmfmRadio::SetCurrentStation(double newStation)
{
	if(strcmp("AM", frequency) == 0 )
	{
		if(newStation >= MINAM && newStation <= MAXAM)
		{
			current_station = newStation;
			return true;
		}
	}
	else
	{
		if(newStation >= MINFM && newStation <= MAXFM)
		{
			current_station = newStation;
			return true;
		}
	}
	//if none of the return trues were hit, the data member was not set
	return false;
}



//NAME: ScanDown
//DESCRIPTION: scans the current_station data member down, if outPut is true, the function will produce output
//PARAMETERS: NONE
//RETURN: NONE
void AmfmRadio::ScanDown(void)
{
	if(strcmp("AM", frequency) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( current_station <= MINAM )
		{
			current_station = MAXAM;
		}
		else
		{
			//In am mode, go down by increments of 10
			SetCurrentStation((current_station-10));
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		if( current_station <= MINFM )
		{
			current_station = MAXFM;
		}
		else
		{
			//Note: car radios jump .2 for the FM. That's how it's modeled here.
			SetCurrentStation((current_station-.2));
		}
	}

	if(outPut == true)//if output is on, print the output
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}



//NAME: ToggleBand
//DESCRIPTION: toggles between AM and FM, restoring the last frequency used on that band
//PARAMETERS: NONE
//RETURN: NONE
void AmfmRadio::ToggleBand(void)
{
	if(strcmp("AM", frequency) == 0 )
	{
		prevFreq.FMFreq = current_station;//save the last frequency
		current_station = prevFreq.FMFreq;//set the old frequency for the band to be the current on
		strcpy(frequency, "FM");//change the radio band
	}
	else
	{
		prevFreq.AMFreq = current_station;//save the last frequency
		current_station = prevFreq.AMFreq;//set the old frequency for the band to be the current on
		strcpy(frequency, "AM");//change the radio band
	}
}


//NAME: GetButton
//DESCRIPTION: accessor for the button data member
//PARAMETERS: NONE
//RETURN: pointer to a freqs button array
const Freqs *AmfmRadio::GetButton(void)
{
	return button;
}

//NAME: GetCurrent_station
//DESCRIPTION: accessor for the current_station data member
//PARAMETERS: NONE
//RETURN: current_station
const double AmfmRadio::GetCurrent_station(void)
{
	return current_station;
}

//NAME: GetFrequency
//DESCRIPTION: accessor for the frequency data member
//PARAMETERS: NONE
//RETURN: a string containing the band
const char *AmfmRadio::GetFrequency(void)
{
	return frequency;
}

//NAME: GetVolume
//DESCRIPTION: accessor for the volume data member
//PARAMETERS: NONE
//RETURN: volume as an integer
const int AmfmRadio::GetVolume(void)
{
	return volume;
}

//NAME: GetPrevVolume
//DESCRIPTION: accessor for the prevVolume data member
//PARAMETERS: NONE
//RETURN: volume as an integer
const int AmfmRadio::GetPrevVolume(void)
{
	return prevVolume;
}

//NAME: GetOn
//DESCRIPTION: accessor for the on data member
//PARAMETERS: NONE
//RETURN: true/false 
const bool AmfmRadio::GetOn(void)
{
	return on;
}

//NAME: GetPrevFreq
//DESCRIPTION: accessor for the prevFreq data member
//PARAMETERS: NONE
//RETURN: a Freqs variable  
const Freqs AmfmRadio::GetPrevFreq(void)
{
	return prevFreq;
}

//NAME: GetoutPut
//DESCRIPTION: accessor for the button data member
//PARAMETERS: NONE
//RETURN: true/false 
const bool AmfmRadio::GetoutPut(void)
{
	return outPut;
}

//NAME: SetFrequency
//DESCRIPTION: mutator for the frequency data member
//PARAMETERS: new frequency as a char pointer
//RETURN: true/false if member was set or not
bool AmfmRadio::SetFrequency(char *newFreq)
{
	if(strcmp(newFreq, "AM") == 0 || strcmp(newFreq, "FM") == 0)
	{
		strcpy(frequency, newFreq);
		return true;
	}
	return false;
}

//NAME: SetName
//DESCRIPTION: mutator for the name data member
//PARAMETERS: new name as a char pointer
//RETURN: true/false if member was set or not
bool AmfmRadio::SetName(char *newName)
{
	if(strcmp(newName, "Pioneer XS440-WRLD") == 0 || strcmp(newName, "Pioneer XS440-AM") == 0 || strcmp(newName, "Pioneer XS440") == 0)
	{
		strcpy(name, newName);
		return true;
	}
	return false;
}


//NAME: GetName
//DESCRIPTION: accessor for the name data member
//PARAMETERS: NONE
//RETURN: name as a char*
const char *AmfmRadio::GetName(void)
{
	return name;
}



bool AmfmRadio::SetOn(bool OnOff)
{
	on = OnOff;

	return true;
}