//Mike Sadowski
//6292106
//Assignment #4
//April 23, 2013
//This program is for the arduino MEGA2560. It allows a user to simulate a gas pump. The joystick allows the user to 
//increment the digits of the gas pump. Middle button is on/off, up = , down = , left = , right = .

/*
 *
 * Fuel Price Display Driver - Arduino Mega2560 version
 *
 * This implements the fuel price driver for the Arduino
 * Mega2560 board with LCD shield.
 *
 */

#include <stdio.h> 
#include "LCD4884.h"
#include <avr/io.h>
#include <util/delay.h>

//PROTOTYPES
void driver_init(void);
unsigned char driver_get_keys(void);
void driver_display_output(int digits[], int decimals[]);
static int ReadSwitch(void);
static int joyStickReading(int result);
static int readADC(void);



//NAME: driver_init
//PARAMETERS: NONE
//DESCRIPTION: initializes the sign, clears it, and turns the back light ON
//RETURN: NONE
void driver_init(void)
{
  LCD_init();//initialize sign
  LCD_clear();//clear sign
  LCD_backlight_on();//turn backlight on

  //Initial Setup to read ADC values
  ADMUX |= (1<<REFS0);
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADCSRA |= (1<<ADEN);
}



//NAME: driver_get_keys
//PARAMETERS: NONE
//DESCRIPTION: Checks which button was pressed
//RETURN: Value of bits 0-4, as an unsigned char
unsigned char driver_get_keys(void)
{
	unsigned char curKeyPressed  = 0;
	int switchToggled = 0;
	static unsigned char prevKeyPress = -1;//made -1 so on first pass of the program, the key pressed are different.
	
	switchToggled = ReadSwitch();//read switches..store which switch was read into switchToggled

	if(switchToggled == prevKeyPress || switchToggled < 0 || switchToggled > 4)
	{
		return curKeyPressed; //if no new button was pressed, or a non readable input was in switchToggled, return right away
	}
	else
	{
		if(switchToggled == 0)//Up switch
		{
			prevKeyPress = currentReading;
			curKeyPressed = 4;
		}
		if(switchToggled == 1)//Right switch
		{
			prevKeyPress = switchToggled;
			curKeyPressed = 16;
		}
		if(switchToggled == 2)//Down switch
		{
			prevKeyPress = switchToggled;
			curKeyPressed = 2;
		}
		if(switchToggled == 3)//Left switch
		{
			prevKeyPress = switchToggled;
			curKeyPressed = 1;
		}
		if(switchToggled == 4)//Toggle power
		{
			prevKeyPress = switchToggled;
			curKeyPressed = 8;
		}
	}
	return curKeyPressed;
}



//NAME: driver_display_output
//DESCRIPTION: Output number to LCD screen
//PARAMETERS: Paramter 1 - digit index, Parameter 2 - decimal position
//RETURN: NONE
void driver_display_output(int digits[], int decimals[])
{
	char buffer[121]= {0};
	LCD_write_string(0,0,"       ",0);//blank

	if(digits[0] == 10)
	{
		sprintf(buffer,"       ");//blank 
		LCD_write_string(0, 0, buffer, 0);
	}
	else
	{
		sprintf(buffer,"%d %d %d.%d",digits[0], digits[1], digits[2], digits[3]);//create a buffer with the display
		LCD_write_string(0, 0, buffer, 0);//write buffer to the LCD screen
	}
}



//NAME: ReadSwitch
//DESCRIPTION: Read the buttons pressed
//PARAMETERS: NONE
//RETURN: Joystick reading as a static integer
static int ReadSwitch(void)
{
	int ADCvalue = 0 ;
	int validateADC = 0 ;
		
	ADCvalue = readADC();//get the ADC value 
	ADCvalue = joyStickReading(newADC); 

	_delay_ms(1);

	validateADC = readADC();//get the ADC value 
	validateADC = joyStickReading(validateADC);

	if( ADCvalue == validateADC )
	{
		return validateADC;
	}

	return 5;//return a non readable result..
}



//DID NOT CREATE THIS FUNCTION...
//SOURCE: James French
static int joyStickReading(int result)
{
	const int adckeys[5] = { 50, 200, 400, 600, 800 };
	int i = 0;
	for( i = 0; i < 5; i++ )
	{
		if( result < adckeys[i] )
		{
			return i;
		}
	}
	return -1; 
}



//DID NOT CREATE THIS FUNCTION...
//SOURCE: James French
static int readADC(void)
{
	ADCSRA |= (1<<ADSC);
	while( ADCSRA & (1<<ADSC) );
	int  result = ADCL;
	result += ADCH*256;

	return result;
}

