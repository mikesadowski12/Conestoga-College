//CarRadio.cpp
// This header comment is quite inadequate and should be replaced.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CarRadio.h"


AmfmRadio::AmfmRadio(bool OnOff)
{
	for( int i = 0; i < 5; ++i )
	{
		button[i].AMButton = 530;
	}
	for( int j = 0; j < 5; ++j )
	{
		button[j].FMButton = 87.9;
	}
	current_station = 530;
	strcpy(frequency, "AM");
	volume = 0;
	on = false;
}

void CarRadio::PowerToggle()
{
	if( on == false )
	{
		on = true;
	}
	else
	{
		on = false;
	}
}

int CarRadio::SetVolume()
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

void CarRadio::ToggleFrequency()
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

int CarRadio::SetButton(int button_num)
{
	if( (button_num >= 0) && (button_num <= 4) )
	{
		if( strcmp("AM", frequency) == 0 )
		{
			button[button_num].AMButton = (int) current_station;
		}
		else
		{
			button[button_num].FMButton = (float) current_station;
		}
		return 1;

	}
	return 0;

}

int CarRadio::SelectCurrentStation(int button_num)
{
	if( (button_num >= 0) && (button_num <= 4) )
	{
		if( strcmp("AM", frequency) == 0 )
		{
			current_station = button[button_num].AMButton;
		}
		else
		{
			current_station = button[button_num].FMButton;
		}

		return 1;
	}
	return 0;


}

void CarRadio::ShowCurrentSettings()
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
		printf("%d) %6d ", i + 1, button[i].AMButton);
	}

	printf("\nFM Button Settings: ");
	for( int j = 0; j < 5; ++j )
	{
		printf("%d) %6.1f ", j + 1, button[j].FMButton);
	}
}

void CarRadio::ScanUp()
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
	printf("\nCurrent station: %f %s\n", current_station, frequency);
}


