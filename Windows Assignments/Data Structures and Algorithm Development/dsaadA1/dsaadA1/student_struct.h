// Mike Sadowski
// 2-12-2013
// This file contains the needed include files, defines the constants used, and contains the Student Struct, and the Nickname Struct. Everything is used
// throughout dsadA1.c. 




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



//STRUCTURES
typedef struct Student
{
	char StudentName[100]; //holds name of the student, grabbed from nickname linked list
	char NickName[100]; //holds nickname of the student, grabbed from nickname linked list
	char DirectoryName[300]; //holds name of directory


	struct Student *next;
} Student;


typedef struct Nickname
{
	char RealName[100]; //holds name of the student
	char NickName[100]; //holds nickname of student

	struct Nickname *next;
} Nickname;





