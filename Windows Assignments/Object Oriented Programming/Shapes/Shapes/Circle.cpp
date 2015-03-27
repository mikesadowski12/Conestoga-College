// This is a comment 
#include "Circle.h"

/*CONSTRUCTORS*/
Circle::Circle(float newRadius, char* newColour)
{
	if(newRadius >= 0.00)
	{
		radius = newRadius;
	}
	else
	{
		radius = radius;
	}

	Circle::SetColour(newColour);
}


Circle::Circle(void)
{
	radius = 0.00;
}


/*DESTRUCTOR*/
Circle::~Circle()
{
	printf("The circle is broken ...\n");
}



/*ACCESSORS*/
const float Circle::GetRadius(void)
{
	return radius;
}



/*MUTATORS*/
void Circle::SetRadius(float newRadius)
{
	if(newRadius >= 0.00)
	{
		radius = newRadius;
	}
	else
	{
		radius = radius;
	}

}


/*SHOW INFO*/
 void Circle::Show(void)
{
	printf("\nShape Information\n");
	printf("Name			: %s\n", GetName());
	printf("Colour			: %s\n", GetColour());
	printf("Radius			: %f cm\n", radius);
	printf("Circumference		: %f cm\n", Perimeter());
	printf("Area			: %f square cm\n", Area());
}


/*VIRTUAL FUNCTIONS*/
float Circle::Perimeter(void)
{
	float perimeter = 0.00;

	perimeter = (float)((PI * radius) * 2);

	return perimeter;
}

float Circle::Area(void)
{
	float area = 0.00;

	area = (float)(PI * (radius * radius));

	return area;
}