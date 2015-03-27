//Mike Sadowski
//April 11th, 2013
//PioneerAM.h
//This file contains the class definition for the PioneerAM class, and contains it's method bodies as well.
#include "pioneerCarRadio.h"


/* 
	NAME	:	PioneerAM
	PURPOSE :	Inherits from PioneerCarRadio, behaves like PioneerCarRadio except that it operates in the AM band only 
*/

class PioneerAM: public PioneerCarRadio
{
public:
	PioneerAM(void);
	virtual ~PioneerAM(void);

	virtual void ToggleFrequency(void)override;
	virtual void ToggleBand(void) override;
};
//NAME: PioneerAM
//DESCRIPTION: Constructor for the PioneerAM class
//PARAMETERS: NONE
//RETURN: NONE
PioneerAM::PioneerAM(void)
{
	SetName("Pioneer XS440-AM");
}

//NAME:~PioneerAM
//DESCRIPTION: Detructor for the PioneerAM class
//PARAMETERS: NONE
//RETURN: NONE
PioneerAM::~PioneerAM(void)
{
	printf("Destroying Pioneer XS440-AM Radio");
}

//NAME: ToggleFrequency
//DESCRIPTION: sets frequency to AM
//PARAMETERS: NONE
//RETURN: NONE
void PioneerAM::ToggleFrequency(void)
{
	SetFrequency("AM");
}


//NAME: ToggleBand
//DESCRIPTION: sets frequency to AM
//PARAMETERS: NONE
//RETURN: NONE
void PioneerAM::ToggleBand(void)
{
	SetFrequency("AM");
}