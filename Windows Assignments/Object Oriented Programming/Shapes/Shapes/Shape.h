// This is a comment 
#include <stdio.h>
#include <string>
#include <iostream>

#define PI 3.1415926

using namespace std;

class Shape 
{
private:     
	 
	char name[100];
	char colour[10];

public:     

	/*Prototypes */
	Shape(void);
	Shape(char* newName, char* newColour);

	//Destructor
	virtual ~Shape();

	virtual float Perimeter(void) = 0;
	virtual float Area(void) = 0;

	//Accessors
	const char* GetName(void);
	const char* GetColour(void);	

	//Mutators
	void SetName(char* newName);    
	void SetColour(char* newColour); 
}; 