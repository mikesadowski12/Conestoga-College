// This is a comment 
#include "Circle.h"

class Square : public Shape
{
private:     
	 
	float sideLength;

public:     

	/*Prototypes*/
	Square(float newSideLength, char* newColour);
	Square(void);
	
	//Destructor
	virtual ~Square();

	//Accessors
	const float GetSideLength(void);
	
	//Mutators
	void SetSideLength(float newSideLength);

	void Show(void);
	virtual float Perimeter(void) override;
	virtual float Area(void) override;
};
