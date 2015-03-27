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
#define bit_4 16

unsigned char processDigit(unsigned char ButtonPress, unsigned char OldButtonPress, unsigned char digitvalue, unsigned char bitValue);
char processbutton4(unsigned char ButtonPress, unsigned char bitValue);
void displaydigit(unsigned char digitvalue, unsigned char *address, unsigned char OnOff, unsigned char dot);


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
	   changedButton = newButton;//Remember last set of read buttons
	   newButton = *((unsigned char*)0xE001);//read the buttons
       displayOnOff = processbutton4(newButton, bit_4);//check to see if display is on
	   //This only executes when button 4 is on, incrementing and processing digits
	   if(displayOnOff == 1)
	   {
            digit0value = processDigit(newButton, changedButton, digit0value, bit_0);//process whether to increment digit 0 or not
			digit1value = processDigit(newButton, changedButton, digit1value, bit_1); //process whether to increment digit 1 or not
			digit2value = processDigit(newButton, changedButton, digit2value, bit_2); //process whether to increment digit 2 or not
			digit3value = processDigit(newButton, changedButton, digit3value, bit_3); //process whether to increment digit 3 or not
	   }//end if

        displaydigit(digit0value, digit_0_address, displayOnOff, 0);//Display new digit
		displaydigit(digit1value, digit_1_address, displayOnOff, 1);//Display new digit, and the period
		displaydigit(digit2value, digit_2_address, displayOnOff, 0);//Display new digit
		displaydigit(digit3value, digit_3_address, displayOnOff, 0);//Display new digit
	}//end while
	return 1;
}//end main

//NAME: processDigit
//DESCRIPTION: Checks to see if the 4th button is being held down or not
//PARAMETERS: the buttons pressed, old set of buttons pressed, digit's value, the bit value of the bit to check for
//RETURN: the digits new value
unsigned char processDigit(unsigned char ButtonPress, unsigned char OldButtonPress, unsigned char digitvalue, unsigned char bitValue)
{
	unsigned char xor = 0;
	unsigned char bitCheck = 0;
	unsigned char newDigitValue = digitvalue;

	if(ButtonPress != OldButtonPress)
	{
        xor = (ButtonPress ^ OldButtonPress);//XOR

        bitCheck = (xor & bitValue); //check to see if 3rd bit is on
        if((xor & bitValue) && (ButtonPress & bitValue))
        {
            newDigitValue = digitvalue + 1;//increment digit by 1

            if(newDigitValue == 11)//check to see if you need to wrap around to 0
            {
                newDigitValue = 0;
            }
        }
    }
    else
    {
       newDigitValue = digitvalue;
    }

    return newDigitValue;//return new value of digit
}

//NAME: displaydigit
//DESCRIPTION: Increments and re displays digit
//PARAMETERS: digit's value, the address to send a value to (to the 7seg_), if the display is on or off, and if to display the dot
//RETURN:
void displaydigit(unsigned char digitvalue, unsigned char *address, unsigned char OnOff, unsigned char dot)
{
    unsigned char valueToDisplay = 0;
    unsigned char lookUpTable[] = {0x3f, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};



    if(OnOff == 1)
    {
        valueToDisplay = lookUpTable[digitvalue];
        if(dot == 1)
        {

        }
    }
    else
    {
        valueToDisplay = lookUpTable[10];//go to 11th position in LUT for blank digits
    }

    if(OnOff == 1)
    {
        if(dot == 1)
        {
            valueToDisplay |= 128;
        }
    }
    *address = valueToDisplay;
}


//NAME: processbutton4
//DESCRIPTION: Turns display on and off
//PARAMETERS: the buttons pressed, and the bit value of the bit to check for
//RETURN: a 1 or 0 if to turn the display on or off
char processbutton4(unsigned char ButtonPress, unsigned char bitValue)
{
    unsigned char bitTest = 0;

    bitTest = ButtonPress & bitValue;

    if(bitTest == bit_4)//check to see if 4th switch is pressed or not
    {
        return 1;
    }

    return 0;
}