//Mike Sadowski
//Jan 29th, 2012
//assign1.cpp
//This file contains the main loop for the program. It prompts a user to type in the string
//that is used as the students marks, and then checks what format the string was entered as,
//and calls the correct overloaded function to deal with the input. It also calls a function
//to print and check whether the student passed/failed or if there was an error with the input.

#include "assessGrade.h"

void main(void)
{
	//variables
	double dbleGrade = 0;
	char inputString[80] = {0};
	float FinalMark = 0;
	int marksArray[5];

	//Prompts user to input student's mark(s)
	cout << "Please type in the student's grades: ";
	cin.getline(inputString,80);

	//calls a function to see if the input string is a double
	dbleGrade = strtod(inputString,NULL);
	//if string returned 0.0, the string was not a double, and I check to see if
	//the strings length is less than or equal to 5 because the max double allowed
	//is 100.0, which is 5 characters, anything exceeding that is invalid.
	if (dbleGrade != 0.0 && strlen(inputString) <= 5)
	{
		//call the assessGrade function with a double as the parameter
		FinalMark = assessGrade(dbleGrade);
	}
	else
	{
		//checks to see if the string length is less than or equal to 3 
		//because the max length of the letter grades and special cases is 3, 
		//so the string cannot exceed that amount
		if(strlen(inputString) <= 3)
		{
			//call the assessGrade function with the input string as a parameter
			FinalMark = assessGrade(inputString);
		}
		else
		{
			//each line of code looks for a space, and whatever was before that space 
			//in the string is put into an array of integers
			marksArray[0] = atoi(strtok(inputString, " "));
			marksArray[1] = atoi(strtok(NULL, " "));
			marksArray[2] = atoi(strtok(NULL, " "));
			marksArray[3] = atoi(strtok(NULL, " "));
			//since only 5 integers are allowed, last call looks for null termination of 
			//the string
			marksArray[4] = atoi(strtok(NULL, "\0"));

			//call the assessGrade function with the array of integers as parameter
			FinalMark = assessGrade(marksArray);
		}
	}
	//call print result with the final mark as a parameter to check and print
	//if a student passed/failed, or if there was an error with the input.
	printResult(FinalMark);
}


