// Mike Sadowski
// 6292106
// Assignment 3
// This program uses a 7 segment display the price of gas being pumped. To increment the value, press buttons 0-3
// to increment the corresponding digit, and the 4th switch turns the display on and off. When the digit hits 9,
// it will wrap around to blank, and then to 0, and continue counting normally afterwards.

#include <stdio.h>

#define digit_0_address 0xE017
#define digit_1_address 0xE015
#define digit_2_address 0xE013
#define digit_3_address 0xE011

#define bit_0 1
#define bit_1 2
#define bit_2 4
#define bit_3 8

//char checkbuttons(unsigned char buttons);
unsigned char processDigit(unsigned char ButtonPress, unsigned char OldButtonPress, unsigned char digitvalue, unsigned char bitValue);
//void processbutton4(void);
void displaydigit(unsigned char digitvalue, unsigned char *address);


int main(void)
{
	unsigned char newButton = 0;
	unsigned char buttonMemory = 0;
	unsigned char changedButton = 0;
	unsigned char displayOnOff = 0;
	unsigned char prevValue = 0;
	unsigned char digit0value = 0;
	unsigned char digit1value = 0;
	unsigned char digit2value = 0;
	unsigned char digit3value = 0;

	while(1)
	{
		//This loop only executes when button 4 is on, incrementing and processing digits
		while(displayOnOff != 0)
		{
			changedButton = newButton;//Remember last set of read buttons
			newButton = *((unsigned char*)0xE001);
			//newButton = checkbuttons(buttons);//Read buttons

			if(newButton != changedButton)//Only execute if new buttons have been pressed
			{
				//displayOnOff = processbutton4(); //Check if fourth button has been pressed or not, if so exit loop

				prevValue = digit0value; //Save the last value of digit0
				digit0value = processDigit(newButton, changedButton, digit0value, bit_0);//process whether to increment digit 0 or not
                displaydigit(digit0value, digit_0_address);//Display new digit

				prevValue = digit1value; //Save the last value of digit1
				digit1value = processDigit(newButton, changedButton, digit1value, bit_1); //process whether to increment digit 1 or not
                displaydigit(digit1value, digit_2_address);//Display new digit

				prevValue = digit2value; //Save the last value of digit2
				digit2value = processDigit(newButton, changedButton, digit2value, bit_2); //process whether to increment digit 2 or not
				displaydigit(digit2value, digit_2_address);//Display new digit

				prevValue = digit3value; //Save the last value of digit3
				digit3value = processDigit(newButton, changedButton, digit3value, bit_3); //process whether to increment digit 3 or not
                displaydigit(digit3value, digit_3_address);//Display new digit

			}//end if
		}//end while button4 (stop incrementing digits and turn off display)
	}//end while
	return 1;
}//end main



/*
//NAME: checkbuttons
//DESCRIPTION: Checks the buttons to see which ones are pressed
//PARAMETERS:
//RETURN:
char checkbuttons(unsigned char buttons)
{
	unsigned char buttonsOn = 0x00;

	//buttonsOn = buttons &&

}
*/

//NAME: processDigit
//DESCRIPTION: Checks to see if the 4th button is being held down or not
//PARAMETERS:
//RETURN:
unsigned char processDigit(unsigned char ButtonPress, unsigned char OldButtonPress, unsigned char digitvalue, unsigned char bitValue)
{
	unsigned char xor = 0;
	unsigned char bitCheck = 0;
	unsigned char newDigitValue = 0;

	if(ButtonPress != OldButtonPress)
	{
        xor = (ButtonPress ^ OldButtonPress);//XOR
        bitCheck = (xor & bitValue); //check to see if 3rd bit is on
        if(bitCheck == bitValue)
        {
            newDigitValue = digitvalue + 1;//increment digit by 1

            if(newDigitValue == 10)//check to see if you need to wrap around to 0
            {
                newDigitValue = 0;
            }
        }
    }
    return newDigitValue;//return new value of digit
}

//NAME: displaydigit
//DESCRIPTION: Increments and re displays digit
//PARAMETERS:
//RETURN:
void displaydigit(unsigned char digitvalue, unsigned char *address)
{
    unsigned char valueToDisplay = 0;
    unsigned char lookUpTable[] = {0x3f, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};

    valueToDisplay = lookUpTable[digitvalue];

    *address = valueToDisplay;
}
