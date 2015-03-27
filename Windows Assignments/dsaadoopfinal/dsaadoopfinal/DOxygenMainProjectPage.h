/// \mainpage SOCCER TEAM TRACKER v1.0   
/// \image html Arsenal-Team.jpg
///
///
/// \section intro System Introduction
/// - This system keeps track of soccer teams, and their current players. 
/// - There are players marked as Starters and Backups to indicate what type of player they are. 
/// - User is able to add a team, give it a name, and then add players to that team. 
/// - On the main menu of the program the user will be able to add a team, delete a team, display a team, or edit a team 
///   (add/remove players). The option to print a team that the user can search for is available. 
/// - An option to add x amount of teams is also available, and the user is able to edit the teams they add later. 
/// - They are also able save all the teams in the database to a single text file as well. 
/// - Once saved, the user will be able to load their entire database back a second time they use the program. 
/// - They will also be able to delete the entire current database while in the program, as well as print it.
/// 
/// <hr>
/// \section notes Special Release Notes
/// - Version 1.0:
///		 - Save database, Load database, Delete database, Delete team, view team, add arbitrary amout of teams, 
///			 create team, edit team, exit with/without saving, help menu are now AVAILABLE
///
/// <hr>
/// \section sampleTextFile Configuration File
///
/// soccerDBASE.txt:
/// - TEAM NAME*HEAD COACH*ASSISTANT COACH*STARTER 1*STARTER 2*STARTER 3*STARTER 4*STARTER 5*STARTER 6*STARTER 7*STARTER 8*STARTER 9*STARTER 10*STARTER 11*BACKUP 1*BACKUP 2*BACKUP 3*BACKUP 4*BACKUP 5*
///
/// <hr>
/// \section requirements Project Requirements
///
/// - add item 
/// - delete item 
/// - delete entire database 
/// - find and display item in a formatted and readable fashion 
/// - display entire database in a formatted and readable fashion 
/// - load database from file 
/// - save database to file 
/// - add an arbitrary number of random items to the database 
/// - exit with saving database changes 
/// - exit without saving database changes
/// - two non trivial classes
/// - three unit testing modules
/// <hr> 
/// \section futureIdeas Future Release Features and Ideas
/// - The plan was to move all of the functions that have to do with the UI menu out of project.cpp, and into the classes,
///   but I ran out of time to do it. This would have made the classes much less trivial. Also not having these functions in
///   the classes made it not possible to unit test them (without just copying them into the unit test file), 
///   except for the ones that I have unit tested already in the classes (which is why 1 unit test module is missing, no functions to test!).
///
/// \todo Move functions into classes 
/// \todo Create test module #3
///
/// <hr>
/// \section bugs BUGS
/// - Selecting Edit Team, and entering a letter causes program to hang.
/// - when printing the help menu, after it's printed the menu is re printed, except the title is tabbed over 
/// 
/// <hr>
/// \section version Current version of the Soccer Tracker Project:
/// <ul>
/// <li>\authors   <b><i>Mike Sadowski</i></b></li>
/// <li>\version   1.00.00</li>
/// <li>\date      April 17th, 2013</li>
/// <li>\copyright Soccer Tracker Project Team</li>
/// </ul>
///