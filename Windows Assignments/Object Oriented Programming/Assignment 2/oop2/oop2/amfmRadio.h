//CarRadio.h

#ifndef _CARRADIO_H
#define _CARRADIO_H

struct Freqs
{
	int AMFreq;
	float FMFreq;
};

class AmfmRadio 
{
private:
	Button button[5];
	double current_station;
	char frequency[3];
	int volume;
	bool on;
public:
	//sets the each button to the lowest frequency, sets the current station, sets the
	//frequency to AM, sets the volume to 0 and sets on to false
	AmfmRadio(bool OnOff);
	AmfmRadio(bool OnOff, Freqs buttons[5]);

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

	//shows volume, button settings, current station, AM or FM
	void ShowCurrentSettings();

	//changes frequency up in increments of .2 for FM, 10 for AM
	void ScanUp();



};
#endif