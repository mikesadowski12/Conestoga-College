//Mike Sadowski
//March 3rd, 2013
//This program implements a complete solution to the video simulation. It is implemented using a C++ class 
//with the video memory, current row, and current column as private data members. It uses array linearization with 
//pointers for extra efficiency.

#include <stdio.h>
#include <stdlib.h>


#define MAX_ROWS 24
#define MAX_COLS 40

//The VideoSim Class
class VideoSim
{
private:
	char video[MAX_ROWS][MAX_COLS];
	int currentRow;
	int currentColumn;

public:

	//Constructor/Destructor
	VideoSim(void);
	~VideoSim();

	//Prototypes
	void ClearScreen(void); 
	void ScrollScreen(void);
	void SetCursorPosition(int x, int y);
	void OutputString(char *s); 
	void DisplayVideoMemory (void); 

	
};


int main (void)  
{  
	VideoSim v; 	          
	v.ClearScreen();
	// test API #1 
	v.OutputString ("top left corner");      
	v.DisplayVideoMemory(); 	     
	v.SetCursorPosition (10, 5);		    
	// test API #2 	     
	v.OutputString ("here's some text in the middle of the screen");	   
	// test API #3 	     
	v.DisplayVideoMemory(); 	    
	v.SetCursorPosition (23, 35);		    
	// test API #2 	     
	v.OutputString ("here's text that will scroll the screen!");	    
	// test API #3 	    
	v.DisplayVideoMemory();  	
	
	return 0; 
} 


//NAME: VideoSim
//DESCRIPTION: constructor for the VideoSim class, sets attributes to 0
//PARAMTERS: NONE
//RETURN: NONE
VideoSim::VideoSim(void)
{
	currentRow = 0;
	currentColumn = 0;
}



//NAME: ~VideoSim
//DESCRIPTION: destructor for the VideoSim class
//PARAMTERS: NONE
//RETURN: NONE
VideoSim::~VideoSim()
{

}



//NAME: SetCursorPosition
//DESCRIPTION: Sets the current row and column to the parameter values
//PARAMTERS: 2 ints that represent the desired row and column
//RETURN: NONE
void VideoSim::SetCursorPosition(int newRow, int newCol)
{
	if(newRow < 24 && newRow >= 0)
	{
		currentRow = newRow;
	}

	if(newCol < 40 && newCol >= 0)
	{
		currentColumn = newCol;
	}
}



//NAME: ClearScreen
//DESCRIPTION: Sets video memory to spaces and resets the current row and column variables to 0
//PARAMTERS: NONE
//RETURN: NONE
void VideoSim::ClearScreen(void)
{
	int i = 0;
	char *pVideo = &video[0][0];

	//Go to the end of the buffer, setting spaces in each character
	for(i = 0; i < MAX_ROWS * MAX_COLS; i++)
	{
		*(pVideo + i) = ' ';
	}

	currentRow = 0;
	currentColumn = 0;
}



//NAME: ScrollScreen
//DESCRIPTION: This functions copies from row 1 through (max_rows - 1) to row 0 (MAX_ROWS - 2) and then blanks the last row
//PARAMTERS: NONE
//RETURN: NONE
void VideoSim::ScrollScreen(void)
{
	int x = 0;
	char *pVideo = &video[0][0];
	int sourceBufferStart = 0;
	int sourceBufferLength = 0;
	int destinationBufferStart = 0;

	//start 2nd row (row 1)
	sourceBufferStart = MAX_COLS;
	sourceBufferLength = (MAX_ROWS - 1) * MAX_COLS;
	destinationBufferStart = 0;

	//Start at the 2nd row (row 1) and copy the buffer
	for(x = 0; x < sourceBufferLength; x++)
	{
		*(pVideo + x) = *(pVideo + sourceBufferStart + x);
	}

	//blank the last line
	for (x = 0; x < MAX_COLS; x++)
	{
		*(pVideo + ((MAX_ROWS - 1) * MAX_COLS) + x) = ' ';
	}
}



//NAME: OutputString
//DESCRIPTION: This function copies the string passed as a parameter into the video memory starting at the current position
//PARAMTERS: A string
//RETURN: NONE
void VideoSim::OutputString(char *s)
{
	int x = 0;
	int video_offset = currentRow * MAX_COLS + currentColumn;
	char *pVideo = &video[0][0];

	//keep copying the string into the buffer until the end
	while(s[x] != 0)
	{
		*(pVideo + video_offset) = s[x];
		video_offset++;

		//if printing on the last line, scroll the screen 
		if(video_offset >= (MAX_ROWS * MAX_COLS))
		{
			video_offset = (MAX_ROWS - 1) * MAX_COLS;
			ScrollScreen();
		}
		x++;
	}
}




//NAME: DisplayVideoMemory
//DESCRIPTION: This function displays the video memory of the program.
//PARAMTERS: NONE
//RETURN: NONE
void VideoSim::DisplayVideoMemory (void)
{
int i = 0, j = 0;

	printf ("Video memory holds:\n");

	printf ("   ");
	for (i = 0; i < MAX_COLS; i++) {	// constant that needs definition
		if ((i % 10) == 0)
			printf ("%d", i / 10);
		else
			printf (" ");
	}	/* end for */
	printf ("\n");

	printf ("   ");
	for (i = 0; i < MAX_COLS; i++) {
		printf ("%d", i % 10);
	}	/* end for */
	printf ("\n");

	for (i = 0; i < MAX_ROWS; i++) {	// constant that needs definition
		printf ("%02d ", i);
		for (j = 0; j < MAX_COLS; j++) {
			printf ("%c", video[i][j]);	// private data member
		}
		printf ("\n");
	}
	printf ("\n\n");
}