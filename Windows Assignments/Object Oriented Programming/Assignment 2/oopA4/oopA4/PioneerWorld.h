//Mike Sadowski
//April 11th, 2013
//PioneerAM.h
//This file contains the class definition for the PioneerWorld class, and contains it's method bodies as well. It also
//contains some constants used throughout the class as well.

#include "PioneerAM.h"

#define MAXWRLD 1602
#define MINWRLD 531

/* 
	NAME	:	PioneerWorld
	PURPOSE :	Inherits from PioneerAM, PioneerWorld behaves like PioneerAM except that the AM band range is 531 kHz to 1602 kHz
				and the interval between frequencies is 9 kHz, not 10 kHz
*/
class PioneerWorld: public PioneerAM
{
public:
	PioneerWorld(void);
	virtual ~PioneerWorld(void);

	virtual void ScanUp(void) override;
	virtual void ScanDown(void) override;
};

//NAME: PioneerWorld
//DESCRIPTION: Constructor for the PioneerWorld class
//PARAMETERS: NONE
//RETURN: NONE
PioneerWorld::PioneerWorld(void)
{
	Freqs *worldButton = NULL;
	
	SetCurrentStation(MINWRLD);
	for( int i = 1; i <= 5; ++i )
	{
		SetButton(i);//since worlds min freq is 531..change the initial button values to 531 not 530
	}
	
	SetName("Pioneer XS440-WRLD");
}

//NAME: ~PioneerWorld
//DESCRIPTION: Destructor for the PioneerWorld class
//PARAMETERS: NONE
//RETURN: NONE
PioneerWorld::~PioneerWorld(void)
{
	printf("Destroying Pioneer XS440-WRLD Radio");
}

//NAME: ScanUp
//DESCRIPTION: Scans up through the current_station by intervals of 9
//PARAMETERS: NONE
//RETURN: NONE
void PioneerWorld::ScanUp(void)
{
	if( strcmp("AM", GetFrequency()) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( GetCurrent_station() == MAXWRLD )
		{
			SetCurrentStation(MINWRLD);
		}
		else
		{
			SetCurrentStation((GetCurrent_station()+9));
		}
	}
}


//NAME: ScanDown
//DESCRIPTION: Scans down through the current_station by intervals of 9
//PARAMETERS: NONE
//RETURN: NONE
void PioneerWorld::ScanDown(void)
{
	if(strcmp("AM", GetFrequency()) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( GetCurrent_station() == MINWRLD )
		{
			SetCurrentStation(MAXWRLD);
		}
		else
		{
			//In am mode, go down by increments of 10
			SetCurrentStation((GetCurrent_station()-9));
		}
	}
}




