//Mike Sadowski
//April 11th, 2013
//amfmRadio.h
//This file contains the declaration of the AmfmRadio, declaring it's data members, and methods, as well as the Freqs struct. It also contains defined constants.

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include <iostream>
using namespace std;

#define EXITCODE 2
#define NOEXIT 1

#ifndef _CARRADIO_H
#define _CARRADIO_H

#define MAXFM 107.9
#define MINFM 87.9
#define MAXAM 1700
#define MINAM 530

#define MINWRLD 531
#define MAXWRLD 1602

#define MAXLEN 100


struct Freqs
{
	int AMFreq ;
	float FMFreq;
};

/* 
	NAME	:	AmfmRadio
	PURPOSE :	This class is meant to model a radio. It has all the features of a radio such as volume, band, frequency,
				etc, and has all the functions that go with a radio as well. (scan up/down, on/off, button presets, etc)
*/
class AmfmRadio 
{
private:
	Freqs button[5];
	char name[MAXLEN];
	double current_station;
	char frequency[3];
	int volume;
	int prevVolume;
	bool on;
	Freqs prevFreq;
	bool outPut;
public:
	//sets the each button to the lowest frequency, sets the current station, sets the
	//frequency to AM, sets the volume to 0 and sets on to false
	AmfmRadio (bool OnOff = false);
	AmfmRadio (bool OnOff, Freqs buttons[5]);

	virtual ~AmfmRadio(void);

	//sets on to true
	void PowerToggle(void);

	//returns a true if the radio is currently powered on, and false if the radio is in
	//the off position
	bool IsRadioOn() {return on;}

	//toggles frequency between AM and FM and sets current station
	virtual void ToggleFrequency(void);

	//sets button with current station by being passed a button number
	int SetButton(int button_num);

	//sets current station by being passed a button number
	int SelectCurrentStation(int button_num);

	//sets volume
	int SetVolume(void);
	int SetVolume(int newVolume);

	//shows volume, button settings, current station, AM or FM
	void ShowCurrentSettings();

	//changes frequency up in increments of .2 for FM, 10 for AM
	virtual void ScanUp(void);
	virtual void ScanDown(void);

	bool SetCurrentStation(double newStation);

	virtual void ToggleBand(void);

	//accessors
	const Freqs *GetButton(void);
	const double GetCurrent_station(void);
	const char *GetFrequency(void);
	const int GetVolume(void);
	const int GetPrevVolume(void);
	const bool GetOn(void);
	const Freqs GetPrevFreq(void);
	const bool GetoutPut(void);
	const char *GetName(void);

	//mutators
	bool SetFrequency(char *newFreq);
	bool SetName(char *newName);
	bool SetOn(bool OnOff);

};
#endif