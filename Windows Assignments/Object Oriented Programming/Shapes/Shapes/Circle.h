// This is a comment 
#include "Shape.h"

class Circle : public Shape
{
private:     
	 
	float radius;

public:     

	/*Prototypes*/
	Circle(float newRadius, char* newColour);
	Circle(void);
	
	//Destructor
	virtual ~Circle();

	//Accessors
	const float GetRadius(void);
	
	//Mutators
	void SetRadius(float newRadius);

	void Show(void);
	virtual float Perimeter(void) override;
	virtual float Area(void) override;

}; 
