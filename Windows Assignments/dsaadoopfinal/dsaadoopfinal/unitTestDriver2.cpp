//Mike Sadowski
//April 17th, 2013
//unitTestDriver2.cpp
//This unit test is testing the effectiveness of the mutators of the Team class ONLY. 
//It will check to see that no bad data gets passed the functions, and into the database with normal tests, exception tests
//and boundary tests.

#include "Team.h"


int main(void)
{
	//TEST #1: two exception tests (sending functions an array of data that contains some bad data to set as backups/starters)
	Team teamObjectTest1;

	string BadBackupArray[MAXBACKUPS] = {"one", "<*>", "three", ">>>", "five"};
	string BadStarterArray[MAXSTARTERS] = {"Only", "^.^", "^mike^", "*Some", "Are", "()()()()", "(mikeS)", "HeLo0o0OO", "**", "*", "Set"};

	teamObjectTest1.SetStarters(BadStarterArray);
	teamObjectTest1.SetBackups(BadBackupArray);

	cout << "Result: TEST #1: two exception tests"; 
	cout << "\nExpectations: A few starters/backups should NOT be set!: \n" << endl;
	teamObjectTest1.PrintTeamInfo();

	//TEST #2: two normal tests (sending functions an array of good data to set as backups/starters)
	Team teamObjectTest2;

	string GoodStarterArray[MAXSTARTERS] = {"Player one", "Player two", "Player three", "Player four", "Player five", "Player six", "Player seven", "Playereight", "Player nine", "Player ten", "Player eleven"};
	string GoodBackupArray[MAXBACKUPS] = {"Messi", "Iniesta", "Ronaldo", "Ronaldinho", "Wesley Sneijder"};

	teamObjectTest2.SetStarters(GoodStarterArray);
	teamObjectTest2.SetBackups(GoodBackupArray);

	cout << "\n\n\nResult: TEST #2: two normal tests" << endl;
	cout << "\nExpectations:  Object should have set all starters and backups!: \n" << endl;
	teamObjectTest2.PrintTeamInfo();

	//TEST #3: two boundary tests (given arrays that test the boundaries of the functions to set members)
	Team teamObjectTest3;

	string GoodStarterArray2[MAXSTARTERS] = {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "2", "", "4", "5", "", "7", "", "9", "","11"};
	string BadBackupArray2[MAXSTARTERS] = {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "2", "", "4", "5", "", "7", "", "9", "","11"};

	cout << "\n\n\nResult: TEST #3: two boundary tests" << endl;
	cout << "\nExpectations: Only the first backup player is not bounds: \n" << endl;
	teamObjectTest3.PrintTeamInfo();
}
