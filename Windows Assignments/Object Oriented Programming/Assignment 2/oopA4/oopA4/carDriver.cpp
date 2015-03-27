// Mike Sadowski
// March 16th, 2013
// This file contains the driver for the PioneerCarRadioClass, which inherits from AmFmRadio class. It is a test harness.

/// \mainpage PioneerCarRadio Assignment #3   
///
///
/// \section intro System Introduction
/// This system creates a Pioneer Car Radio. It inherits from the AmFmRadio class and models a real life radio. 
/// This program tests whether or not all functions are working in the AmFmRadio class by inheriting those functions to the
/// PioneerCarRadio class. The PioneerCar radio class adds some more functionality, the user is able to use keyboard shortcuts
/// to change the "radios" settings.
///
/// <hr>
/// \section knownBugs Known Issues and Limitations
///
/// \bug [known bugs and limitations within the project]
/// - BUG   :  Program sometimes crashes, depending on the order of the input
/// 
/// <hr>
/// \section version Current version of the PioneerCarRadio Project :
/// <ul>
/// <li>\author   Mike Sadowski
/// <li>\version   1.00.00</li>
/// <li>\date      March 16th, 2013</li>
/// </ul>
///

#include "pioneerCarRadio.h"


int main()
{
	bool on = true;
	bool off = false;
	int ifExit = 0;
	
	PioneerCarRadio jazzy;

	while (ifExit != EXITCODE)
	{
		ifExit = jazzy.processKeystrokes();
	}
	return EXITCODE;
}