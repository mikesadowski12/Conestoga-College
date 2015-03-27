#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <iostream>
using namespace std;

#define EXITCODE 2
#define NOEXIT 1


#ifndef _CARRADIO_H
#define _CARRADIO_H

struct Freqs
{
	int AMFreq;
	float FMFreq;
};

/**
* \class AmfmRadio
*
* \brief <b>This class models an AM/FM radio</b> 
*
*  <b>NAME:</b> AmfmRadio </li>
*  <b>DESCRIPTION:</b> This class models an AM FM radio. It has a volume level, a current station, frequency and on/off features, just like a real radio.
*  It is used as a parent class, so that other radio such as the PioneerCarRadio can use it's data members, and represent different types of radios.
*
* \author <i>Mike Sadowski</i>
*/

class AmfmRadio 
{
private:
	Freqs button[5];
	double current_station; /** \This indicates the current station the radio is on */
	char frequency[3]; /**< This indicates the frequency of the radio */
	int volume; /**< /**< This indicates the volume of the radio */ 
	bool on; /**< Indicates whether radio is on or off */

public:
	//sets the each button to the lowest frequency, sets the current station, sets the
	//frequency to AM, sets the volume to 0 and sets on to false
	AmfmRadio(void);
	AmfmRadio(bool OnOff);
	AmfmRadio(bool OnOff, Freqs buttons[5]);

	~AmfmRadio();

	//Mutators
	void SetCurrentStation(double newCurrent_station); 

	//Accessors
	const Freqs* getButton(void);
	const double getCurrent_station(void);
	const char* getFrequency(void);
	const int getVolume(void);
	const bool getOn(void);

	//sets on to true
	void PowerToggle();

	//returns a true if the radio is currently powered on, and false if the radio is in
	//the off position
	bool IsRadioOn() {return on;}

	//toggles frequency between AM and FM and sets current station
	void ToggleFrequency();

	//sets button with current station by being passed a button number
	int SetButton(int button_num);

	//sets current station by being passed a button number
	int SelectCurrentStation(int button_num);

	//sets volume
	int SetVolume();
	int SetVolume(int newVolume);

	//shows volume, button settings, current station, AM or FM
	void ShowCurrentSettings();

	//changes frequency up in increments of .2 for FM, 10 for AM
	void ScanUp(bool display);
	void ScanDown(bool display);



};
#endif