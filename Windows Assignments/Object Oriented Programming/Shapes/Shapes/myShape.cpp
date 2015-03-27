/*
	Purpose:	this source drives the use of the Shape, Circle and Square classes
*/
#include <stdlib.h>
#include <new.h>
#include <stdio.h>
#include <string.h>

#include "Square.h"


// local function prototypes
int		getInteger(void);
float	getFloat(void);
int		getString(char* myString);


int main(void)
{

	Circle *ptr1 = NULL;
	Square *ptr2 = NULL;

	char shapename[100] = {0};
	char shapecolour[100] = {0};
	float radius = 0.0;
	float sidelength = 0.0;
	int quit = 0;

	printf("Please type in the Shape's name:\n");
	fgets(shapename, sizeof(shapename), stdin);

	printf("Please type in the Shape's colour:\n");
	fgets(shapecolour, sizeof(shapecolour), stdin);

	ptr1 = new Circle();
	if( ptr1 == NULL )
	{
		printf("Not enough memory (from new)\n");
		return 1;
	}

	ptr2 = new Square();
	if( ptr2 == NULL )
	{
		printf("Not enough memory (from new)\n");
		return 1;
	}

	//get rid of the last control character that was at the end of the string ..
	if(shapename[strlen(shapename)-1] < 33)
	{
		shapename[strlen(shapename)-1] = 0;
	}


	if (strcmp(shapename, "Circle") == 0)
	{
		printf("Please type in the Circle's radius:\n");
		radius = getFloat();

		ptr1->SetName(shapename);
		ptr1->SetColour(shapecolour);
		ptr1->SetRadius(radius);

	}
	
	if (strcmp(shapename, "Square") == 0)
	{
		printf("Please type in the Square's side-length:\n");
		sidelength = getFloat();

		ptr2->SetName(shapename);
		ptr2->SetColour(shapecolour);
		ptr2->SetSideLength(sidelength);
	}

	ptr1->Show();
	ptr2->Show();

	delete ptr1;
	delete ptr2;

	return 0;
}


// some useful functions
int getInteger(void)
{
	char	record[121] = {0};	/* record stores the string */
	int 	number = 0;

	/* use fgets() to get a string from the keyboard */
	fgets(record, sizeof(record), stdin);

	/*  extract the number from the string; sscanf() returns
		a number corresponding with the number of items it
		found in the string */
	if( sscanf(record, "%d", &number) != 1 )
	{
		/* if the user did not enter a number recognizable by
		 * the system, set number to -1 */
		number = -1;
	}

	return number;
}

float getFloat(void)
{
	char	record[121] = {0};	/* record stores the string */
	float 	number = 0.00;

	/* use fgets() to get a string from the keyboard */
	fgets(record, sizeof(record), stdin);

	/*  extract the number from the string; sscanf() returns
		a number corresponding with the number of items it
		found in the string */
	if( sscanf(record, "%f", &number) != 1 )
	{
		/* if the user did not enter a number recognizable by
		 * the system, set number to -1.00 */
		number = -1.00;
	}

	return number;
}

int getString(char* myString)
{
	char	record[121] = {0};	/* record stores the string */
	int		retCode = 0;		/* success code */

	/* use fgets() to get a string from the keyboard */
	fgets(record, sizeof(record), stdin);

	/*  extract the number from the string; sscanf() returns
		a number corresponding with the number of items it
		found in the string */
	if( sscanf(record, "%s", myString) != 1 )
	{
		/* if the user did not enter a number recognizable by
		 * the system, set number to -1 */
		retCode = -1;
	}

	return retCode;
}

