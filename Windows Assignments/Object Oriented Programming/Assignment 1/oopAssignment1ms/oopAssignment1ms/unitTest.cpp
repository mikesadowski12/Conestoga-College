//Mike Sadowski
//Jan 29th, 2012
//uniTest.cpp
//This file contains 21 different tests. Those include normal tests, exception tests, and
//boundary checks for all 3 overloaded functions to see if they work as intended. 
//All the tests are exactly the same, except the only differences are the test strings, 
//and the expected and actual result floats.

#include "assessGrade.h"

void main(void)
{

	// Tests for assessGrade(char *)
	// TEST #1
	char testString[80] = "A+";
	float expectedResult = 95.0;
	float actualResult = 0.0;

	//call the assessGrade function on the test string
	actualResult = assessGrade(testString);
	cout << "Test #1: Normal Test of assessGrade(char *)";
	cout << "Submitting '" << testString << "' input\n";
	cout << "Expected Result: " ;
	//call the print result function to print the expected results of the test
	printResult(expectedResult); 
	cout << "\n";
	cout << "Actual Result:   "; 
	//call the print result function to print the actual results of the test
	printResult(actualResult);  
	cout << "\n";
	
	//checks to see if the expected mark is equal to the actual mark and prints
	//if test passed or not accordingly.
	if(expectedResult == actualResult)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

//Every other test is commented out


	// TEST #2
	char testString1[80] = "DNA";
	float expectedResult1 = DNA;
	float actualResult1 = 0.0;

	actualResult1 = assessGrade(testString1);
	cout << "Test #2: Normal Test of assessGrade(char *)";
	cout << "Submitting '" << testString1 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult1); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult1);  
	cout << "\n";
	
	if(expectedResult1 == actualResult1)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	// TEST #3
	char testString2[80] = "C";
	float expectedResult2 = 62.0;
	float actualResult2 = 0.0;

	actualResult2 = assessGrade(testString2);
	cout << "Test #3: Normal Test of assessGrade(char *)";
	cout << "Submitting '" << testString2 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult2); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult2);  
	cout << "\n";
	
	if(expectedResult2 == actualResult2)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}
	// TEST #4
	char testString3[80] = "A-";
	float expectedResult3 = ERRORLEVEL;
	float actualResult3 = 0.0;

	actualResult3 = assessGrade(testString3);
	cout << "Test #4: Exception Test of assessGrade(char *)";
	cout << "Submitting '" << testString3 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult3); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult3);  
	cout << "\n";
	
	if(expectedResult3 == actualResult3)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}
	// TEST #5
	char testString4[80] = "Hello";
	float expectedResult4 = ERRORLEVEL;
	float actualResult4 = 0.0;

	actualResult4 = assessGrade(testString4);
	cout << "Test #5: Exception Test of assessGrade(char *)";
	cout << "Submitting '" << testString4 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult4); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult4);  
	cout << "\n";
	
	if(expectedResult4 == actualResult4)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}
	// TEST #6
	char testString5[80] = "+A";
	float expectedResult5 = 95.0;
	float actualResult5 = 0.0;

	actualResult5 = assessGrade(testString5);
	cout << "Test #6: Exception Test of assessGrade(char *)";
	cout << "Submitting '" << testString5 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult5); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult5);  
	cout << "\n";
	
	if(expectedResult5 == actualResult5)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Tests for assessGrade(double)
	//Test #7
	char testString6[80] = "42.37";
	float expectedResult6 = 42.37;
	float actualResult6 = 0.0;

	actualResult6 = assessGrade(testString6);
	cout << "Test #7: Normal Test of assessGrade(double)";
	cout << "Submitting '" << testString6 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult6); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult6);  
	cout << "\n";
	
	if(expectedResult6 == actualResult6)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #8
	char testString7[80] = "80.0";
	float expectedResult7 = 80.0;
	float actualResult7 = 0.0;

	actualResult7 = assessGrade(testString7);
	cout << "Test #8: Normal Test of assessGrade(double)";
	cout << "Submitting '" << testString7 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult7); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult7);  
	cout << "\n";
	
	if(expectedResult7 == actualResult7)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #9
	char testString8[80] = "67.7";
	float expectedResult8 = 67.7;
	float actualResult8 = 0.0;

	actualResult8 = assessGrade(testString8);
	cout << "Test #9: Normal Test of assessGrade(double)";
	cout << "Submitting '" << testString8 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult8); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult8);  
	cout << "\n";
	
	if(expectedResult8 == actualResult8)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #10
	char testString9[80] = "-23.5";
	float expectedResult9 = ERRORLEVEL;
	float actualResult9 = 0.0;

	actualResult9 = assessGrade(testString9);
	cout << "Test #10: Exception Test of assessGrade(double)";
	cout << "Submitting '" << testString9 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult9); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult9);  
	cout << "\n";
	
	if(expectedResult9 == actualResult9)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #11
	char testString10[80] = "234.1";
	float expectedResult10 = ERRORLEVEL;
	float actualResult10 = 0.0;

	actualResult10 = assessGrade(testString10);
	cout << "Test #11: Exception Test of assessGrade(double)";
	cout << "Submitting '" << testString10 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult10); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult10);  
	cout << "\n";
	
	if(expectedResult10 == actualResult10)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #12
	char testString11[80] = "-200.0";
	float expectedResult11 = ERRORLEVEL;
	float actualResult11 = 0.0;

	actualResult11 = assessGrade(testString11);
	cout << "Test #12: Exception Test of assessGrade(double)";
	cout << "Submitting '" << testString11 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult11); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult11);  
	cout << "\n";
	
	if(expectedResult11 == actualResult11)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #13
	char testString12[80] = "54.4";
	float expectedResult12 = 54.4;
	float actualResult12 = 0.0;

	actualResult12 = assessGrade(testString12);
	cout << "Test #13: Boundary Test of assessGrade(double)";
	cout << "Submitting '" << testString12 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult12); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult12);  
	cout << "\n";
	
	if(expectedResult12 == actualResult12)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #14
	char testString13[80] = "54.5";
	float expectedResult13 = 54.4;
	float actualResult13 = 0.0;

	actualResult13 = assessGrade(testString13);
	cout << "Test #14: Normal Test of assessGrade(double)";
	cout << "Submitting '" << testString13 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult13); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult13);  
	cout << "\n";
	
	if(expectedResult13 == actualResult13)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #15
	char testString15[80] = "100.0";
	float expectedResult15 = 100.0;
	float actualResult15 = 0.0;

	actualResult15 = assessGrade(testString15);
	cout << "Test #15: Boundary Test of assessGrade(double)";
	cout << "Submitting '" << testString << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult15); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult15);  
	cout << "\n";
	
	if(expectedResult15 == actualResult15)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #16
	char testString16[80] = "75 90 80 70 60";
	float expectedResult16 = 75.0;
	float actualResult16 = 0.0;

	actualResult16 = assessGrade(testString16);
	cout << "Test #16: Normal Test of assessGrade(int array)";
	cout << "Submitting '" << testString16 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult16); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult16);  
	cout << "\n";
	
	if(expectedResult16 == actualResult16)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #17
	char testString17[80] = "80 20";
	float expectedResult17 = 50.0;
	float actualResult17 = 0.0;

	actualResult17 = assessGrade(testString17);
	cout << "Test #17: Normal Test of assessGrade(int array)";
	cout << "Submitting '" << testString17 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult17); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult17);  
	cout << "\n";
	
	if(expectedResult17 == actualResult17)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #18
	char testString18[80] = "75 90 80";
	float expectedResult18 = ERRORLEVEL;
	float actualResult18 = 0.0;

	actualResult18 = assessGrade(testString18);
	cout << "Test #18: Normal Test of assessGrade(int array)";
	cout << "Submitting '" << testString18 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult18); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult18);  
	cout << "\n";
	
	if(expectedResult18 == actualResult18)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #19
	char testString19[80] = "75 90 -80 70 60";
	float expectedResult19 = ERRORLEVEL;
	float actualResult19 = 0.0;

	actualResult19 = assessGrade(testString19);
	cout << "Test #19: Exception Test of assessGrade(int array)";
	cout << "Submitting '" << testString19 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult19); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult19);  
	cout << "\n";
	
	if(expectedResult19 == actualResult19)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #20
	char testString20[80] = "75 90 -80 70";
	float expectedResult20 = ERRORLEVEL;
	float actualResult20 = 0.0;

	actualResult20 = assessGrade(testString20);
	cout << "Test #20: Exception Test of assessGrade(int array)";
	cout << "Submitting '" << testString20 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult20); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult20);  
	cout << "\n";
	
	if(expectedResult20 == actualResult20)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}

	//Test #21
	char testString21[80] = "-75 90";
	float expectedResult21 = ERRORLEVEL;
	float actualResult21 = 0.0;

	actualResult21 = assessGrade(testString21);
	cout << "Test #21: Normal Test of assessGrade(int array)";
	cout << "Submitting '" << testString21 << "' input\n";
	cout << "Expected Result: " ;
	printResult(expectedResult21); 
	cout << "\n";
	cout << "Actual Result:   ";  
	printResult(actualResult21);  
	cout << "\n";
	
	if(expectedResult21 == actualResult21)
	{
		cout << "** TEST PASSED **\n\n";
	}
	else
	{
		cout << "** TEST FAILED **\n\n";
	}
	
}