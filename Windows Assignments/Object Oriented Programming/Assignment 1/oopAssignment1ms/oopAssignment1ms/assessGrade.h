//Mike Sadowski
//Jan 29th, 2012
//assessGrade.h
//This file contains all needed include statements, as well as constants used throughout the program,
//and all function prototypes.

#include <iostream>
using namespace std;

//CONSTANTS
#define I 101.0
#define Q 102.0
#define AU 103.0
#define DNA 104.0
#define IP 105.0
#define PASSMARK 54.50
#define MAXMARK 100.00
#define ERRORLEVEL 200.0
#define NOERROR 300.0

//PROTOTYPES
float assessGrade(char *string);
float assessGrade(double FinalMark);
float assessGrade(int markArray[]);
void printResult(float FinalMark);