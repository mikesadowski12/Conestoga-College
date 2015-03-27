// Mike Sadowski
// March 16th, 2013
// pioneerCarRadio.h
// This file contains the class defintion for the PioneerCarRadioClass

#include "amfmRadio.h"
#define EXITCODE 2
#define NOEXIT 1
/**
* \class PioneerCarRadio
*
* \brief <b>This class is an AmFmRadio, that represents a Pioneer Car Radio in real life</b> 
* <b>NAME:</b> PioneerCarRadio 
* <b>DESCRIPTION:</b> This class models a pioneer car radio. It inherits from the AmFmRadio class. 
* Allows a user to create a "Pioneer Car Radio", and they are able to use it just like an AmFmRadio.
* It reads different keystrokes on the keyboard to perform actions, like change the volume, frequency, etc.
* 
* \author <i>Mike Sadowski</i>
*/
class PioneerCarRadio : public AmfmRadio
{
private:

public:

	PioneerCarRadio(void);

	~PioneerCarRadio(void);

	//Processes the keystroke from the user, and performs the appropriate action
	int processKeystrokes(void);

	void printPioneerCarRadio(void);

	void chooseButton(int newButton);

	void programButtons(int newButton);

};
