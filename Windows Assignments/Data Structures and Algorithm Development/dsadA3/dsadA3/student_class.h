// Mike Sadowski
// 2-12-2013
// This file contains the needed include files, defines the constants used, and contains the Student class, and the Nickname class. 


//INCLUDE
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <stddef.h>
#include <tchar.h>
#include <iostream>
#include <set>
using namespace std;


//CONSTANTS
#define MAXLENGTH 100 //max length of the strings
#define MAXDIRLENGTH 300 //max length of a directory path
#define ERRORLEVEL 1

class Student
{

private:
	
	char StudentName[MAXLENGTH]; //holds name of the student, grabbed from nickname linked list
	char NickName[MAXLENGTH]; //holds nickname of the student, grabbed from nickname linked list
	char DirectoryName[MAXLENGTH]; //holds name of directory

 public:
	 //friend bool operator< ( const Student, Student);
	 //const char* getDirectoryName(void);
	 //const char* getNickName(void);
	// const char* getStudentName(void);

	Student()                            
	{ 
		strcpy(StudentName, "");
		strcpy(NickName, "");  
		strcpy(DirectoryName, ""); 
	}

	Student(char* n, char* c, char* d) 
	{ 
		strcpy(StudentName, n);
		strcpy(NickName, c);  
		strcpy(DirectoryName, d); 
	}

	const char* getStudentName(void)              const { return StudentName; }
	const char* getNickName(void)				const { 	return NickName; }
	const char* getDirectoryName(void)          const     { return DirectoryName; }
};



class Nickname
 {
private:

	char RealName[MAXLENGTH]; //holds name of the student
	char NickName[MAXLENGTH]; //holds nickname of student

 public:

	Nickname()                             { strcpy(RealName, ""); strcpy(NickName,""); }
	Nickname(char* n)                 { strcpy(RealName,n); strcpy(NickName,""); }
	Nickname(char* n, char* c)		   { strcpy(RealName,n); strcpy(NickName,c); }
	const char* getRealName(void) 		const { return RealName; }
	const char* getNickName(void)		const{ return NickName; }
 };


bool operator<(Nickname p1, Nickname p2)
{
	if(strcmp(p1.getRealName(), p2.getRealName()) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator<(Student S1, Student S2)
{
	//return S1.getStudentName() < S2.getStudentName();
	return (strcmp(S1.getStudentName(), S2.getStudentName()) < 0);

}
