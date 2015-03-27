//driver.cpp
//Mike Sadowski Feburary 26, 2013
//This file contains the driver for the AmfmRadio class. It instantiates an AmfmRadio object, and allows the user to
//manipulate it as they would a regular radio with the ability to turn it on/off, set the volume, toggle AM/FM, set
//favourite buttons, show the current settings, scan up/down through the stations, and quit.

#include <stdio.h>
#include <stdlib.h>
#include "amfmRadio.h"

#include <iostream>
using namespace std;

enum menuItems
{
	kMenuNothing = 0,	// special constant for initialization only
	kMenuTogglePower = 1, kMenuSetVolume, kMenuToggleAMFM, kMenuSetButton, kMenuSelectButton,
	kMenuShowCurrentSettings, kMenuScanUp, kMenuScanDown, kMenuQuit
};


int main()
{
	bool on = true;
	bool off = false;
	int volume_OK = 0, button_OK = 0, button_num = 0;
	menuItems choice = kMenuNothing;
	char buf[20] = {0};
	cout << "a";
	AmfmRadio jazzy(on);

	do
	{
		printf("\n\nMAIN MENU\n");
		printf("=========\n\n");
		printf("1.  Toggle Power\n");
		printf("2.  Set Volume\n");
		printf("3.  Toggle AM / FM\n");
		printf("4.  Set a Button \n"); 
		printf("5.  Select a Button \n"); 
		printf("6.  Show Current Settings\n"); 
		printf("7.  Scan Up \n"); 
		printf("8.  Scan Down \n"); 
		printf("9.  Quit the Program\n");
		printf("\nMake a selection from the menu\n");
		fgets(buf, sizeof buf, stdin);
		choice = (menuItems) atoi(buf);
		
		switch( choice )
		{
		case kMenuTogglePower:
			jazzy.PowerToggle();
			break;
		case kMenuSetVolume: 
			volume_OK = jazzy.SetVolume();
			if( volume_OK == 0 )
			{
				printf("\nVolume was set to 0.");
			}
			else if( volume_OK == 2 )
			{
				printf("\nVolume was set to 100.");
			}
			break;
			
		case kMenuToggleAMFM:
			on = jazzy.IsRadioOn();
			if( on )
			{
				jazzy.ToggleFrequency();
			    
			}
			else
			{
				printf("\nThe radio must be turned on before the "
					"band can be toggled!");
			}
			break;
		case kMenuSetButton:
			on = jazzy.IsRadioOn();
			if( on )
			{
				printf("\nWhich button do you want to set?");
			    fgets(buf, sizeof buf, stdin);
			    button_num = atoi(buf) - 1;
			    button_OK = jazzy.SetButton(button_num);
			    if( button_OK == 0 )
				{
					printf("\nYou entered an invalid button number!");
				}
			}
			else
			{
				printf("\nYou must turn the radio on before you set the buttons!\n");
			}
			break;
		case kMenuSelectButton:
			on = jazzy.IsRadioOn();
			if( on )
			{
				printf("\nEnter the number of the button: ");
			    fgets(buf, 20, stdin);
			    button_num = atoi(buf) - 1;
			    button_OK = jazzy.SelectCurrentStation(button_num);
				if( button_OK == 0 )
				{
					printf("\nYou entered an invalid button number!");
				}
			}
			else
			{
				printf("\nYou must turn the radio on before you set the buttons!\n");
			}
			break;
		case kMenuShowCurrentSettings:
			jazzy.ShowCurrentSettings();
			break;
		case kMenuScanUp:
			on = jazzy.IsRadioOn();
			if( on )
			{
				jazzy.ScanUp(on);
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan button!\n");
			
			}
		case kMenuScanDown:
			on = jazzy.IsRadioOn();
			if( on )
			{
				jazzy.ScanDown(on);
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan button!\n");
			
			}
			break;
		case kMenuQuit:
		    break;
		default:
			printf("You have entered an invalid selection. Please make \n"
				   "another selection.\n");
			break;

		}

		if( (choice != kMenuShowCurrentSettings) && (choice != kMenuQuit) )
			jazzy.ShowCurrentSettings();

	}while( choice != kMenuQuit );

	printf("\nGoodbye!\n");
	return 0;


}