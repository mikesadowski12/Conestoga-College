// Mike Sadowski
// 2-12-2013
// This file contains the needed include files, defines the constants used, and contains the Nickname Struct. 



//INCLUDE
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <stddef.h>



//CONSTANTS
#define MAXLENGTH 100 //max length of the strings
#define MAXDIRLENGTH 300 //max length of a directory path
#define ERRORLEVEL 1
#define BUCKETS 127



typedef struct Nickname
{
	char RealName[MAXLENGTH]; //holds name of the student
	char NickName[MAXLENGTH]; //holds nickname of student

	struct Nickname *next;
} Nickname;