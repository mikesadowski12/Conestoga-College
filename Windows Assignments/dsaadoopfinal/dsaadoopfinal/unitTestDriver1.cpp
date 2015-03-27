//Mike Sadowski
//April 17th, 2013
//unitTestDriver1.cpp
//This unit test is testing the effectiveness of CheckCharactersOfString, and mutators of the Management class ONLY. 
//It will check to see that no bad data gets passed the functions, and into the database with normal tests, exception tests
//and boundary tests.

#include "Team.h"


int main(void)
{
	//TEST #1: three exception tests (sending functions 1 string of good data, 2 bad data)
	Team teamObjectTest1;

	teamObjectTest1.SetHeadCoach("I should be set");//good string
	teamObjectTest1.SetAssistantCoach("**I should not be set**");//bad string
	teamObjectTest1.SetTeamName("I should Also not >< be Set!**&&^^$$#");//bad string

	cout << "Result: TEST #1: three exception tests"; 
	cout << "\nExpectations: Only head coach should be set: \n" << endl;
	teamObjectTest1.PrintTeamInfo();

	//TEST #2: three normal tests (sending functions good data to set)
	Team teamObjectTest2;

	teamObjectTest2.SetHeadCoach("Im a headcoach");//good string
	teamObjectTest2.SetAssistantCoach("Im the assistant");//good string
	teamObjectTest2.SetTeamName("The team name");//good string

	cout << "\n\n\nResult: TEST #2: three normal tests" << endl;
	cout << "\nExpectations:  Objects should have set the coaches/team name!: \n" << endl;
	teamObjectTest2.PrintTeamInfo();

	//TEST #3: three boundary tests (given strings that test the boundaries of the functions to set as coaches/teamname)
	Team teamObjectTest3;

	//string of 255 x's
	string maxChars = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	//string of 257 x's
	string overMaxChars = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	string emptyString = "";

	teamObjectTest3.SetTeamName(maxChars);//send string AT the boundary
	teamObjectTest3.SetHeadCoach(overMaxChars);//send string over the boundary
	teamObjectTest3.SetAssistantCoach(emptyString);//send empty string

	cout << "\n\n\nResult: TEST #3: three boundary tests" << endl;
	cout << "\nExpectations: Only the teamname/assistant coach are in bounds: \n" << endl;
	teamObjectTest3.PrintTeamInfo();
}
