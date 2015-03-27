// Mike Sadowski
// February 11 2013
// This program filters user input from either specified text file, standard input, to either a specified output file
// or standard out, in either a s-record format, or assembly file format.

// program A
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//CONSTANTS
#define ERRORLEVEL 0
#define NOERROR 1
#define HELP 2
#define MAXINPUTLENGTH 9999

//PROTOTYPES
int ProcessCommandLine(int argc, char *argv[]);
int ProcessHowToPrintContents(char *InputFIleName, char *OutputFileName, char *buffer, int sizeofinputfile);
void PrintAssemblyStyle(FILE * OutputFile, char *buffer);
void PrintContentsAssemblyStdout(char *buffer);
void PrintSrecFile(char *InputFileName, char *OutputFileName, char *buffer);
void MakeS0Line(FILE * OutputFile, char *MyName, int address);
void MakeS1Line(FILE *OutputFile, char *data, int address);
void MakeS5Line(FILE *OutputFile, int address);
void MakeS9Line(FILE *OutputFile, int address);


int main(int argc, char *argv[])
{

	int filesize = 0;	
	int i = 0;
	int CheckHelpExit = 0;

	//Read the command line
	CheckHelpExit = ProcessCommandLine(argc, argv);

	//Check if help menu was displayed, if so exit program.
	if(CheckHelpExit == HELP)
	{
		return HELP;
	}
}


//Name: ProcessCommandLine
//Description: This function scans the command line, and parses out the input file, output file, -h for help,
//				and -srec, and calls a function that then deals with this information.
//Parameters: Parameter 1 - argc, Parameter 2 - argv[](all command line arguments)
//Return: returns HELP, NOERROR, or ERRORLEVEL(all defined constants)
int ProcessCommandLine(int argc, char *argv[])
{
	int x = 1;
	int counter = 2;
	FILE * InputFile;
	FILE * OutputFile;
	char *buffer = 0;
	char Buffer[9999] = {0};
	char FileNameBuffer[100] = {0};
	char InputFileName[100] = {"NONE"};
	char OutputFileName[100] = {"NONE"};
	int sizeoffile = 0;
	int srecCount = 0;

	for(x = 1; x < argc; x++)
	{
		if (strcmp(argv[x], "-h") == 0) 		
		{
			//If argv[x] is a -h, print help menu and return from function.
			printf("Program Name: %s\n", argv[0]);
			printf(">> -i at the start of a filename specifies the INPUTFILENAME.\n");
			printf(">> -o at the start of a filename specifies the OUTPUTFILENAME.\n");
			printf(">> -srec tells the software to output in the S-Record format. Without specifying this option, output will be an Assembly File.\n");
			return HELP;
		}

		//CHECK INPUT FILE AND READ INTO A BUFFER
		if(strstr(argv[x], "-i") != NULL)
		{

			strcpy(FileNameBuffer, argv[x]);
			//I want to copy one character at a time starting from the 3rd character to skip the '-i', this will be my input filename
			for(counter = 2; counter <= strlen(FileNameBuffer); counter++)
			{
				
				InputFileName[counter-2] = FileNameBuffer[counter];
			}
			
			//Open the input file name
			InputFile = fopen(InputFileName, "rb");
			//Check if input file was opened, if it did read it into a buffer.
			if (InputFile != NULL)
			{
				//Find out file size
				fseek(InputFile , 0 , SEEK_END);
				sizeoffile = ftell(InputFile);
				fseek(InputFile , 0 , SEEK_SET);

				//allocate memory to read my file into
				buffer = (char*) calloc((sizeoffile+1), sizeof(char));
				//Reads in entire input file, into buffer
				fread(buffer, sizeof(char), sizeoffile, InputFile);
			}
			else
			{
				printf(">> Error: Cannot open INPUT file");
				return ERRORLEVEL;
			}
		}


		//Check if an output file was specified.
		if(strstr(argv[x], "-o") != NULL)
		{
			strcpy(FileNameBuffer, argv[x]);
			//I want to copy one character at a time starting from the 3rd character to skip the '-i', this will be my input filename
			for(counter = 2; counter <= strlen(FileNameBuffer); counter++)
			{
				OutputFileName[counter-2] = FileNameBuffer[counter];
			}
		}

		//Check if srec output was specified
		if (strcmp(argv[x], "-srec") == 0) 
		{
			srecCount = 1;
		}
	} //END FOR LOOP

	//Use std input and write contents to outputfile specified
	if(strcmp(OutputFileName, "NONE") != 0 && strcmp(InputFileName, "NONE") == 0)
	{
		fgets(Buffer, sizeof(Buffer), stdin);
		//call function to print as Assembly to output file
		ProcessHowToPrintContents(InputFileName, OutputFileName, Buffer, sizeof(buffer), srecCount);
		return NOERROR;
	}

	//Checks if no input and no output file are specified, then uses stdin and stdout to get and
	//present the results, and exits functions
	if(strcmp(OutputFileName, "NONE") == 0 && strcmp(InputFileName, "NONE") == 0)
	{
		fgets(Buffer, sizeof(Buffer), stdin);
		//call function to print as Assembly to STDOUT
		PrintContentsAssemblyStdout(Buffer);
		return NOERROR;
	}

	//Check if srec was on the cmd line, if so, call the appropriate function to display data
	if(srecCount == 1)
	{
		 if(strcmp(InputFileName, "NONE") == 0)
		 {
			fgets(Buffer, sizeof(Buffer), stdin);
			ProcessHowToPrintContents(InputFileName, OutputFileName, Buffer, srecCount);
		 }
		 else
		 {
			ProcessHowToPrintContents(InputFileName, OutputFileName, buffer, srecCount);
		 }
	}
	else
	{
		ProcessHowToPrintContents(InputFileName, OutputFileName, buffer, sizeoffile, srecCount);
	}

	//Check if input was incorrect, if so display usage statement and exit.
	if(strcmp(InputFileName, "NONE") == 0 && strcmp(OutputFileName, "NONE") && strcmp(buffer, "0") == 0)
	{
		printf("Program Name: %s\n", argv[0]);
		printf(">> -i at the start of a filename specifies the INPUTFILENAME.\n");
		printf(">> -o at the start of a filename specifies the OUTPUTFILENAME.\n");
		printf(">> -srec tells the software to output in the S-Record format. Without specifying this option, output will be an Assembly File.\n");			return HELP;
		return ERRORLEVEL;
	}

	free(buffer);
	fclose(InputFile);
}



//Name: ProcessHowToPrintContents
//Description: This function decides how the inputted data should be printed, whether to the standard output,
//				or in s-record format, assembly format, and to what type of file if specified.
//Parameters: Parameter 1 - a input filename, Parameter 2 - a output file name, Parameter 3 - input data in string, 
//				Parameter 4 - the size of the input file, Paramter 5 - a count if srec was detected on the cmd line
//Return: returns NOERROR, or ERRORLEVEL(all defined constants)
int ProcessHowToPrintContents(char *InputFileName, char *OutputFileName, char *buffer, int sizeofinputfile, int srec)
{
	FILE * OutputFile;

	if(strcmp(OutputFileName, "NONE") != 0 && strcmp(InputFileName, "NONE") != 0 && srec == 0)
	{
		OutputFile = fopen(OutputFileName, "w+");
		//Check if output file was opened/created
		if (OutputFile == NULL)
		{	
			printf(">> Error: Cannot open OUTPUT file");
			return ERRORLEVEL;
		}
		//Call function to print in assembly style
		PrintAssemblyStyle(OutputFile, buffer, sizeofinputfile);
		return NOERROR;
	}
	//If no input file was specified, print what was grabbed from the stdin and print to specified
	//output file
	if(strcmp(InputFileName, "NONE") == 0 && srec == 0)
	{
		OutputFile = fopen(OutputFileName, "w+");
		if (OutputFile == NULL)
		{	
			printf(">> Error: Cannot open OUTPUT file");
			return ERRORLEVEL;
		}
		PrintAssemblyStyle(OutputFile, buffer, sizeof(buffer));
		return NOERROR;
	}
	//If no output file was specified, appent the original input file name with .asm, and
	//use that as the output file name
	else
	{
		if(srec == 0)
		{
			strcat(InputFileName, ".asm");
			//open a output file with the original input file name, appended with .asm
			OutputFile = fopen(InputFileName, "w+");

			//Check if output file was opened/created
			if (OutputFile == NULL)
			{	
				printf(">> Error: Cannot open OUTPUT file");
				return ERRORLEVEL;
			}
			//Call function to print in assembly style
			PrintAssemblyStyle(OutputFile, buffer, sizeofinputfile);	
		}
		else
		{
			if(strcmp(OutputFileName, "NONE") == 0)
			{
				strcat(InputFileName, ".srec");
				strcpy(OutputFileName, InputFileName);

				//Call function to print in srec style
				PrintSrecFile(InputFileName, OutputFileName, buffer);
				return NOERROR;

			}
			else
			{
				PrintSrecFile(InputFileName, OutputFileName, buffer);
				return NOERROR;
			}
	}
		fclose(OutputFile);
}//end function
}



//Name: PrintAssemblyStyle
//Description: This function prints the inputted data in assembly format to a output file.
//Parameters: Parameter 1 - a pointer to a output file, Parameter 2 input data in string, 
//Return: NONE
void PrintAssemblyStyle(FILE * OutputFile, char *buffer)
{
	int x = 0;

		//Print to the output file in the assembly file format


		//iterates through buffer, prints each character to output file
	for (x = 0; x < strlen(buffer); x++)
	{
		//if x is a multiple of 16, and does not equal 0, print a new line
		if (x % 16  == 0)
		{
			//prints a new line to output file without the last comma
			fprintf(OutputFile, "\n   dc.b	");
			fprintf(OutputFile, "$%02X", buffer[x]);
		}
		else
		{
			//Prints to the outputfile 1 byte at a time, as an integer in hex
			fprintf(OutputFile, ", $%02X", buffer[x]);
		}
	}
}



//Name: PrintContentsAssemblyStdout
//Description: This function prints the inputted data in assembly format to standard output.
//Parameters: Parameter 1 - a pointer to a output file, Parameter 2 input data in string, 
//Return: NONE
void PrintContentsAssemblyStdout(char *buffer)
{
	int x = 0;

	//Print to the output file in the assembly file format

	//iterates through buffer, prints each character to output file
	for (x = 0; x <= strlen(buffer); x++)
	{
		//if x is a multiple of 16, and does not equal 0, print a new line
		if (x % 16  == 0)
		{
			//prints a new line to output file without the last comma
			printf("\n   dc.b	");
			printf("$%02X", buffer[x]);

		}
		else
		{
			//Prints to the outputfile 1 byte at a time, as an integer in hex
			printf(", $%02X", buffer[x]);
		}
	}
}


//Name: PrintSrecFile
//Description: This function prints the inputted data in srec format to a output file.
//Parameters: Parameter 1 - an input file name, Parameter 2 - output file name, Parameter 3 - input data in a string
//Return: NONE
void PrintSrecFile(char *InputFileName, char *OutputFileName, char *buffer)
{
	int x = 0;
	int y = 0;
	int BufferCount = 0;
	char LineBuffer[200] = {0};
	char MyName[7] = {"MIKE"};
	int Address = 0;
	int counter = 0;


	FILE *OutputFile; 

	if(strcmp(OutputFileName, "NONE") != 0)
	{
		OutputFile = fopen(OutputFileName, "w+");

		//Check if output file was opened/created
		if (OutputFile == NULL)
		{	
			printf(">> Error: Cannot open OUTPUT file");
			return ERRORLEVEL;
		}
			BufferCount = strlen(buffer);
			MakeS0Line(OutputFile, MyName, Address);
	
			for(x = 0; x < strlen(buffer); x++)
			{	
				if (buffer[x] >= 32)
				{
					LineBuffer[y] = buffer[x];
					y++;
					LineBuffer[y] = 0;
				}

				if(y == 16 || x == strlen(buffer)-1)
				{
					MakeS1Line(OutputFile, LineBuffer, Address);
					Address += 16;
					counter++;
					y = 0;
				}
			}

			Address = 0;

			MakeS5Line(OutputFile, counter);
			MakeS9Line(OutputFile, Address);

		fclose(OutputFile);
	}
}



//Name: MakeS0Line
//Description: This function prints the inputted data in assembly format to a output file.
//Parameters: Parameter 1 - pointer to an output file, Parameter 2 - persons name, 
//				Parameter 3 - address to start at as an int
//Return: NONE
void MakeS0Line(FILE *OutputFile, char *MyName, int address)
{
	int Count = {3};
	int x = 0;
	char DataString[200] = {0};
	char AddressString[5] = {0};
	char AddressLB[20] = {0};
	char AddressHB[20] = {0};
	int AddressLBi = 0;
	int AddressHBi = 0;
	int CheckSum = 0;

	sprintf(AddressString, "%04X", address);

	strncpy(AddressLB, AddressString, 2);
	AddressLBi = atoi(AddressLB);
	strncpy(AddressHB, AddressString+2, 2);
	AddressHBi = atoi(AddressHB);

	
	Count += strlen(MyName);
	CheckSum = (AddressLBi + AddressHBi) + Count; 

	for(x = 0; x < strlen(MyName); x++)
	{	
		if(x == 0)
		{
			fprintf(OutputFile, "S0%02X%04X%02X",Count, address, MyName[x]);
			CheckSum += MyName[x];
		}
		else
		{
			fprintf(OutputFile, "%02X", MyName[x]);
			CheckSum += MyName[x];
		}
	}
	
	//Ones complement, and LSB
	CheckSum = 0xFFFF - CheckSum;
	CheckSum &= 0xFF;

	fprintf(OutputFile, "%02X", CheckSum);


}



//Name: MakeS1Line
//Description: This function prints the inputted data in srec format to a output file.
//Parameters: Parameter 1 - pointer to an output file, Parameter 2 - data to print, 
//				Parameter 3 - address to start at as an int
//Return: NONE
void MakeS1Line(FILE *OutputFile, char *data, int address)
{
	int Count = {3};
	int x = 0;
	char DataString[200] = {0};
	char AddressString[5] = {0};
	char AddressLB[20] = {0};
	char AddressHB[20] = {0};
	int AddressLBi = 0;
	int AddressHBi = 0;
	int CheckSum = 0;

	sprintf(AddressString, "%04d", address);

	strncpy(AddressLB, AddressString, 2);
	AddressLBi = atoi(AddressLB);

	strncpy(AddressHB, AddressString + 2, 2);
	AddressHBi = atoi(AddressHB);


	
	Count += strlen(data);
	CheckSum = (AddressLBi + AddressHBi) + Count; 

	for(x = 0; x < strlen(data); x++)
	{	
		if(x == 0)
		{
			fprintf(OutputFile, "\nS1%02X%04X%02X",Count, address, data[x]);
			CheckSum += data[x];
		}
		else
		{
			fprintf(OutputFile, "%02X", data[x]);
			CheckSum += data[x];
		}
	}
	
	//Ones complement, and LSB
	CheckSum = 0xFFFF - CheckSum;
	CheckSum &= 0xFF;

	fprintf(OutputFile, "%02X", CheckSum);
}



//Name: MakeS5Line
//Description: This function prints the inputted data in srec format to a output file.
//Parameters: Parameter 1 - pointer to an output file, Parameter 2 - count of how many s1 data fields were made
//Return: NONE
void MakeS5Line(FILE *OutputFile, int address)
{
	int Count = {3};
	int x = 0;
	char DataString[200] = {0};
	char AddressString[5] = {0};
	char AddressLB[20] = {0};
	char AddressHB[20] = {0};
	int AddressLBi = 0;
	int AddressHBi = 0;
	int CheckSum = 0;

	sprintf(AddressString, "%04d", address);

	strncpy(AddressLB, AddressString, 2);
	AddressLBi = atoi(AddressLB);

	strncpy(AddressHB, AddressString + 2, 2);
	AddressHBi = atoi(AddressHB);
	
	CheckSum = (AddressLBi + AddressHBi) + Count; 


	fprintf(OutputFile, "\nS5%02X%04X", Count, address);

	
	//Ones complement, and LSB
	CheckSum = 0xFFFF - CheckSum;
	CheckSum &= 0xFF;

	fprintf(OutputFile, "%02X", CheckSum);
}



//Name: MakeS9Line
//Description: This function prints the inputted data in srec format to a output file.
//Parameters: Parameter 1 - pointer to an output file, Parameter 2 - original starting address
//Return: NONE
void MakeS9Line(FILE *OutputFile, int address)
{
	int Count = {3};
	int x = 0;
	char DataString[200] = {0};
	char AddressString[5] = {0};
	char AddressLB[20] = {0};
	char AddressHB[20] = {0};
	int AddressLBi = 0;
	int AddressHBi = 0;
	int CheckSum = 0;

	sprintf(AddressString, "%04d", address);

	strncpy(AddressLB, AddressString, 2);
	AddressLBi = atoi(AddressLB);

	strncpy(AddressHB, AddressString + 2, 2);
	AddressHBi = atoi(AddressHB);
	
	CheckSum = (AddressLBi + AddressHBi) + Count; 


	fprintf(OutputFile, "\nS9%02X%04X", Count, address);

	
	//Ones complement, and LSB
	CheckSum = 0xFFFF - CheckSum;
	CheckSum &= 0xFF;

	fprintf(OutputFile, "%02X", CheckSum);
}