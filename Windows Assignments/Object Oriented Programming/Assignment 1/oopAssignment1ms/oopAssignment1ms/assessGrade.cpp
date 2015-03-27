//Mike Sadowski
//Jan 29th, 2012
//assessGrade.cpp
//This file contains the logic of all 3 overloaded functions that process a string and 
//provide a final mark as a float. It also contains a function that is used to validate the input, check
//for errors, and print whether a student passed/failed, or if there were any errors.

#include "assessGrade.h"


/*  -- Method Header Comment
		Name	:	assessGrade

		Purpose :	 Called to translate a string into a float, that translate into a students
						mark/special case.

		Inputs	:	char *string 

		Outputs	:	NONE	

		Returns	:	95.0=A+,85.0=A,77.0=B+,72.0=B,67=C+,62=C,57=D,50=F,I=I,Q=Q,AU=AU,I/P=IP
					or ERRORLEVEL for an error.
*/	
float assessGrade(char *string)
{
	//Each if statement compares what was passed in as string, to the letter grade or 
	//special case that is allowed, and returns the appropriate mark or special case. If input was none 
	//of the allowed letter grades or special cases, an error level is returned to be processed
	//later.
	if (strcmp(string,"A+")==0)
	{
		return 95.0;
	}

	if (strcmp(string,"A")==0)
	{
		return 85.0;
	}

	if (strcmp(string,"B+")==0)
	{
		return 77.0;
	}

	if (strcmp(string,"B")==0)
	{
		return 72.0;
	}

	if (strcmp(string,"C+")==0)
	{
		return 67.0;
	}

	if (strcmp(string,"C")==0)
	{
		return 62.0;
	}

	if (strcmp(string,"D")==0)
	{
		return 57.0;
	}

	if (strcmp(string,"F")==0)
	{
		return 50.0;
	}

	if (strcmp(string,"I")==0)
	{
		return I;
	}

	if (strcmp(string,"Q")==0)
	{
		return Q;
	}

	if (strcmp(string,"AU")==0)
	{
		return AU;
	}

	if (strcmp(string,"DNA")== 0)
	{
		return DNA;
	}

	if (strcmp(string,"I/P")==0)
	{
		return IP;
	}

	return ERRORLEVEL;
}



/*  -- Method Header Comment
		Name	:	assessGrade

		Purpose :	 Called to return a double as a float that can be translated into a
						students mark

		Inputs	:	double 

		Outputs	:	NONE	

		Returns	:	dbleGrade(the Final Mark as a float)
*/
float assessGrade(double dbleGrade)
{
	//cast the double as a float, and returns it as a float.
	return (float)dbleGrade;
}



/*  -- Method Header Comment
		Name	:	assessGrade

		Purpose :	 Called to return a final average of 5 integers that can be translated
						into a students final mark.

		Inputs	:	integer array 

		Outputs	:	NONE	

		Returns	:	the average of all 5 integers as a float
*/
float assessGrade(int markArray[])
{
	int x = 0;
	float FinalMark = 0;

	//for loop that counts to 5, adds all 5 elements of the int array passed in
	for (x = 0; x < 5; x++)
	{
		//if a negative number was given, return an error level to be processed later
		if (markArray[x] < 0)
		{
			return ERRORLEVEL;
		}
		else
		{
			//adds each element of the array together
			FinalMark += markArray[x]; 
		}
	}
	//divides the sum of all 5 integers by x(which is 5 in this case) to provide an average
	FinalMark /= x;

	//return the final average of all 5 integers
	return FinalMark;
}



/*  -- Method Header Comment
		Name	:	printResult

		Purpose :	 Called to check the final mark, and decide whether the mark passed/failed
						or if there is an error with the input.

		Inputs	:	float number

		Outputs	:	outputs pass if the float number is > 54.5, a fail if it is less than 54.5,
					or an error message if invalid input was given.

		Returns	:	NONE
*/
void printResult(float FinalMark)
{
	if (FinalMark <= MAXMARK)
	{
		if (FinalMark >= PASSMARK)
		{
			cout << " >> Student achieved " << FinalMark << "% which is a PASS condition\n";
		}
		else
		{
			cout << " >> Student achieved " << FinalMark << "% which is a FAIL condition\n";
		}
	}

	if (FinalMark == I)
	{
		cout << " >> Student has special condition: I (Incomplete)\n";
	}

	if (FinalMark == Q)
	{
		cout << " >> Student has special condition: Q (Withdrawal after drop/refund date)\n";
	}

	if (FinalMark == AU)
	{
		cout << " >> Student has special condition: AU (Audit)\n";
	}

	if (FinalMark == DNA)
	{
		cout << " >> Student has special condition: DNA (Did Not Attend)\n";
	}


	if (FinalMark == IP)
	{
		cout << " >> Student has special condition: I/P (In Process)\n";
	}


	if (FinalMark == 200.0)
	{
		cout << " >> ERROR: Final Mark Invalid\n";
	}
}