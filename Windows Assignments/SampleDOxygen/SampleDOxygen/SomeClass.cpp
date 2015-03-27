#include "SomeClass.h"

	///
	/// \brief <b>Brief Description</b> - Humourously named method called upon to print out a SomeClass object's current set of attribute values
	/// \details <b>Details</b>
	///
	/// Here is where I can provide a better, more detailed description of what this method does...
	///	
	/// \returns nothing
	///
	void	SomeClass::SomeClassDump(void)
	{
		printf("SomeClass Name\t: %s\n", name);
		printf("SomeClass Breed\t: %s\n", breed);
		printf("SomeClass Sex\t\t: %s\n", GetGender());
		printf("SomeClass Size\t: %s\n", GetSize());
	}