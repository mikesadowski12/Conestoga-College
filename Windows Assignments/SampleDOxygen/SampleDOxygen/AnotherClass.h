#include <string.h>
#include <stdio.h>

/* NOTE : This class is exactly the same (in terms of content) as the AnotherClass.h definition ... the difference is that 
          this class definition uses JAVADOC-style DOxygen style commenting */
/** 
* \class AnotherClass
*
* \brief <b>Brief Description</b> - One sentence summarizing the purpose of this class - what is it modeling ? what does it represent in reality?
*
* This comment block is <i>required</i> for all class declarations.  This is the place where the <b>class header comment</b> appears. 
* Remember that the <b>class header comment</b> is used to tell the reader (of your code and comments) exactly what you are trying
* to model in the class.  What does it represent in reality ?  How could some programmer use this class ?  What benefits does it have ?
*
* Within the class definition, you should also comment :
* - class constants and class data members (attributes) and their purpose
*   - NOTE: If you set up your DOxygen project properly, you can have DOxygen extract this constant and data memeber information from your code for 
*           <b><i>private</i></b>, <b><i>protected</i></b> and <b><i>public</i></b> levels of visibility
*   - In the DOxygen <i>Expert</i> tab, ensure that you have the EXTRACT_PRIVATE, EXTRACT_STATIC, EXTRACT_LOCAL_CLASSES and EXTRACT_LOCAL_METHODS checked
* - any and all <b>methods</b> in the proper <i>Method Header Commenting</i> style (see AnotherClass() below)
*   - again this applies to methods for all levels of visibility ...
*
* When it comes to commenting the body of your code, or commenting anything within
* any of your source modules that you want DOxygen to ignore - simply use
* standard C++ comments
*
*
* \author <i>insert your name here</i>
*/

class AnotherClass
{
	// ======================================
	//              PRIVATE
	// ======================================
private:
	// --------------  CONSTANTS --------------
	// notice in the following DOxygen commenting - where the comment appears after the element that the
	// comment is for - we start the comment with a "/**<" - this means "Hey DOxygen, attach the following comment 
	// to the previous element!"
	const int	dm3;		/**< this description should indicate the purpose of this <b>CONST</b> data member */

	// -------------- DATA MEMBERS ------------
	char	dm1[100];		/**< this description should indicate what the purpose / usage of this char[] datamember is ... */

	int		dm2;			/**< again the description of this int data member should tell the reader what its purpose is */

	// ---------------- METHODS ---------------
	/**
	* \brief <b>Brief Description</b> - Validation <b><i>class method</i></b> - called upon to ensure that <b>dm1's</b> contents are valid and within range
	* \details <b>Details</b>
	*
	* Here is where I can provide a better, more detailed description of what this method does...
	* 
	* \return a <b>bool</b> indicator whether the value tested is valid or not
	*
	*/
	static bool	ValidateDM1(char input[])
	{
		bool	retCode = false;
		if(strlen(input) > 0)		// Pretend Test #1 - the C-Style string needs to not be blank
		{
			if(input[0] == 'A')		// Pretend Test #2 - according to the requirements, the first letter of the C-Style string needs to be "A"
			{
				retCode = true;
			}
		}
		return retCode
	}

	/**
	* \brief <b>Brief Description</b> - Validation <b><i>class method</i></b> - called upon to ensure that <b>dm2's</b> contents are valid and within range
	* \details <b>Details</b>
	*
	* Here is where I can provide a better, more detailed description of what this method does...
	* 
	* \return a <b>bool</b> indicator whether the value tested is valid or not
	*/
	static bool	ValidateDM2(int someVal)
	{
		bool	retCode = false;

		// according to the requirements for this class, DM2 can be in the range of numbers
		// between 10 and 20 (inclusive) or 99 ...
		if(((someVal >= 10) && (someVal <= 20)) || (someVal == 99)) retCode = true;

		return retCode;
	}

	/**
	* \brief <b>Brief Description</b> - Validation <b><i>class method</i></b> - called upon to ensure that <b>dm3's</b> contents are valid and within range
	* \details <b>Details</b>
	*
	* Here is where I can provide a better, more detailed description of what this method does...
	* 
	* \return a valid value for the DM3 data member ...
	*/
	static int	ValidateDM3(int proposedDM3)
	{
		int		valueToSet = 0;

		// according to the requirements for this class, DM3 must be negative or zero ...
		//   ... if we get an invalid value - then set it to a value of 0
		if(proposedDM3 <= 0) valueToSet = proposedDM3;

		return proposedDM3;
	}

	// ======================================
	//              PROTECTED
	// ======================================
protected:
	// --------------  CONSTANTS --------------
	// -------------- DATA MEMBERS ------------
	// ---------------- METHODS ---------------

	// ======================================
	//              PUBLIC
	// ======================================
public:
	// --------------  CONSTANTS --------------
	static const int	SOME_CLASS_STATUS_OK	= 1;	/**< These <i>const class data members</i> are used to enumerate some status codes from AnotherClass */
	static const int	SOME_CLASS_STATUS_ERR	= 2;
	static const int	SOME_CLASS_STATUS_NOP	= 3;
	static const int	SOME_CLASS_STATUS_UNK	= 4;

	// -------------- DATA MEMBERS ------------
	// ---------------- METHODS ---------------
	/**
	* \brief <b>Brief Description</b> - To instantiate a new AnotherClass object - given a set of attribute values
	* \details <b>Details</b>
	*
	* Here is where I can provide a better, more detailed description of what this method does... how it works ...
	* about its algortihm ... basically what this method "brings to the party" in terms of the overall purpose of this class ...
	*
	* \param newDM1 - <b>char *</b> - description of what this parameter means ...
	* \param newDM2 - <b>int</b> - description of what this parameter means ...
	* \param newDM3 - <b>int</b> - description of what this parameter means ...
	* 
	* \return As this is a <i>constructor</i> for the AnotherClass class, nothing is returned
	*
	* <i>If you feel in your class' design that this method is related to another method - and you'd like to direct the
	*     reader of your comments to look at that other method - then you can insert a "see also" tag as below</i>
	*
	* \see ~AnotherClass(), ValidateDM1(), ValidateDM2() and ValidateDM3()
	*/
	AnotherClass(char* newDM1, int newDM2, int newDM3) : dm3(ValidateDM3(newDM3))
	{
		// set the values for the object's data members - but first we'll call the 
		// class methods we've set up to do validation ...
		if(ValidateDM1(newDM1) == true)
		{
			strcpy(dm1,newDM1);
		}
		else
		{
			memset(dm1,0,100);		// NULL out the DM1 data member  by default
		}

		if(ValidateDM2(newDM2) == true)
		{
			dm2 = newDM2;
		}
		else
		{
			dm2 = 99;				// set the data member to 99 by default
		}
	}


	/* NOTE : that in the sample comment below, I used the DOxygen @param directive - only to
			  show you that it still works in the JAVADOC-style commenting - you really wouldn't document the 
			  VOID parameter */

	/**
	* \brief <b>Brief Description</b> - Called upon to <i>destroy</i> a AnotherClass object - once it loses <b>scope</b>
	* \details <b>Details</b>
	*
	* Here is where I can provide a better, more detailed description of what this method does...
	*
	* @param NOTTA - <b>void</b> - it's a destructor - are you kidding me ?!?
	*
	* \return As this is a <i>destructor</i> for the AnotherClass class, nothing is returned
	*
	* \see AnotherClass()
	*/
	~AnotherClass()
	{
		printf("Dead AnotherClass ...\n");
	}
};
