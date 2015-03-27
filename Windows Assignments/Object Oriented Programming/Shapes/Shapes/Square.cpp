// This is a comment 
#include "Square.h"

/*CONSTRUCTORS*/
Square::Square(float newSideLength, char* newColour)
{
	if(newSideLength >= 0.00)
	{
		sideLength = newSideLength;
	}
	else
	{
		sideLength = sideLength;
	}

	Square::SetColour(newColour);
}


Square::Square(void)
{
	sideLength = 0.00;
}


/*DESTRUCTOR*/
Square::~Square()
{
	printf("The square is squished ...\n");
}



/*ACCESSORS*/
const float Square::GetSideLength(void)
{
	return sideLength;
}



/*MUTATORS*/
void Square::SetSideLength(float newSideLength)
{
	if(newSideLength >= 0.00)
	{
		sideLength = newSideLength;
	}
	else
	{
		sideLength = sideLength;
	}
}


/*SHOW INFO*/
 void Square::Show(void)
{
	printf("\nShape Information\n");
	printf("Name			: %s\n", GetName());
	printf("Colour			: %s\n", GetColour());
	printf("Side-Length		: %f cm\n", sideLength);
	printf("Perimeter		: %f cm\n", Perimeter());
	printf("Area			: %f square cm\n", Area());
}


/*VIRTUAL FUNCTIONS*/
float Square::Perimeter(void)
{
	float perimeter = 0.00;

	perimeter = 4 * sideLength;

	return perimeter;
}

float Square::Area(void)
{
	float area = 0.00;

	area = (sideLength)*(sideLength);

	return area;
}