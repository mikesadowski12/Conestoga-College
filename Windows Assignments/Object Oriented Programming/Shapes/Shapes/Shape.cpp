// This is a comment 
#include "Shape.h"

/*CONSTRUCTORS*/
Shape::Shape(void)
{
	strcpy(name,"Unknown");
	strcpy(colour, "Undefined");
}

Shape::Shape(char* newName, char* newColour)
{
	if(strlen(newName) < 100)
	{
		if(strcmp(name, "Circle") == 0 || strcmp(name, "Square") == 0|| strcmp(name, "Unknown") == 0)
		{
			strcpy(name, newName);
		}
	}
	else
	{
		cout << "Please type in a valid name\n";
	}

	if(strlen(newColour) < 10)
	{
		if(strcmp(colour,"red") == 0 || strcmp(colour,"green") == 0 || strcmp(colour,"blue") == 0 || strcmp(colour,"yellow") ==0 || strcmp(colour,"purple") == 0 
		   || strcmp(colour, "pink") == 0 || strcmp(colour,"orange") == 0 || strcmp(colour,"undefined") == 0)
		{
			strcpy(colour,newColour);
		}
	}
	else
	{
		cout << "Please type in a valid colour\n";
	}
}


/*ACCESSORS*/
const char* Shape::GetName(void)     
{     
	return name;
}

const char* Shape::GetColour(void)     
{     
	return colour;
}


/*MUTATORS*/
void Shape::SetName(char* newName)	
{
	if(strlen(newName) < 100)
	{
		if(strcmp(name, "Circle") == 0 || strcmp(name, "Square") == 0|| strcmp(name, "Unknown") == 0)
		{
			strcpy(name, newName);
		}
	}
	else
	{
		cout << "Please type in a valid name\n";
	}
};

void Shape::SetColour(char* newColour)	
{
	if(strlen(newColour) < 10)
	{
		if(strcmp(colour,"red") == 0 || strcmp(colour,"green") == 0 || strcmp(colour,"blue") == 0 || strcmp(colour,"yellow") ==0 || strcmp(colour,"purple") == 0 
		   || strcmp(colour, "pink") == 0 || strcmp(colour,"orange") == 0 || strcmp(colour,"undefined") == 0)
		{
			strcpy(colour,newColour);
		}
	}
	else
	{
		cout << "Please type in a valid colour\n";
	}
};



/*DESTRUCTOR*/
Shape::~Shape()
{
	printf("%s destroyed\n", name);
}

