/*
* Copyright 2014 ammianus
*/
//#include <stdlib.h>
//#include <math.h>
#include "types.h"
#include "string.h"
#include "32x.h"
#include "hw_32x.h"
#include "32x_images.h"
#include "game_constants.h"
#include "graphics.h"
#include "shared_objects.h"



#define DEBUG 1
#define MAP_WIDTH 320


#define IMAGE_START_ADDRESS 0
#define IMAGE_END_ADDRESS 1
#define NINJA_STANDING_INDEX 0

//global variable
char keyPressedText[100];

//const int world_width = WORLD_WIDTH;
//int paused = UNPAUSED;
//stores the previous buttons pressed for handle_input
unsigned short prev_buttons = 0;


/*
* Converts an integer to the relevant ascii char where 0 = ascii 65 ('A')
*/
char ascii(int letterIndex){
	int asciiOffset = 65;
	char newChar;
	newChar = (char)(asciiOffset + letterIndex);
	return newChar;
}

/*
* Call 32x hardware initialization routine
*/
void mars_init(void)
{
  //using 256 color mode using palette
  Hw32xInit(MARS_VDP_MODE_256, 0);
}

/*
* Check the current SEGA Controllers for inputs, update player, direction
* , speed, and action accordingly.
*/
void handle_input()
{
	unsigned short new_buttons, curr_buttons;
	//unsigned short buttons = 0;

	//The type is either 0xF if no controller is present, 1 if a six button pad is present, or 0 if a three button pad is present. The buttons are SET to 1 if the corresponding button is pressed, and consist of:
	//(0 0 0 1 M X Y Z S A C B R L D U) or (0 0 0 0 0 0 0 0 S A C B R L D U)

	// MARS_SYS_COMM10 holds the current button values: - - - - M X Y Z S A C B R L D U
	curr_buttons = MARS_SYS_COMM8;
	if ((curr_buttons & SEGA_CTRL_TYPE) == SEGA_CTRL_NONE)
		curr_buttons = MARS_SYS_COMM10; // if no pad 1, try using pad 2
	
	// set if button changed
    new_buttons = (curr_buttons & 0x0FFF) ^ prev_buttons;
    prev_buttons = curr_buttons & 0x0FFF;
	
	while (MARS_SYS_COMM6 == SLAVE_LOCK) ; // wait until slave isn't blocking
	MARS_SYS_COMM6 = MASTER_LOCK; //tell slave to wait
	
	//pause when start is first pressed only
	if (curr_buttons & SEGA_CTRL_START )
	{
		sprintf(keyPressedText,"Key Pressed: Start");
	}
	else if (curr_buttons & SEGA_CTRL_UP )
	{
		sprintf(keyPressedText,"Key Pressed: Up");
	}
	else if (curr_buttons & SEGA_CTRL_DOWN )
	{
		sprintf(keyPressedText,"Key Pressed: Down");	
	}
	else if (curr_buttons & SEGA_CTRL_LEFT )
	{
		sprintf(keyPressedText,"Key Pressed: Left");
	}
	else if (curr_buttons & SEGA_CTRL_RIGHT )
	{
		sprintf(keyPressedText,"Key Pressed: Right");
	}
	else if (curr_buttons & SEGA_CTRL_A)
	{
		sprintf(keyPressedText,"Key Pressed: A");
	}
	
	else if (curr_buttons & SEGA_CTRL_B)
	{
		sprintf(keyPressedText,"Key Pressed: B");
	}
	
	else if (curr_buttons & SEGA_CTRL_C)
	{
		sprintf(keyPressedText,"Key Pressed: C");
	}
	
	MARS_SYS_COMM6 = MASTER_STATUS_OK; //tell slave to resume
}


/*
* Starts application
*/
int main(void)
{
    //
	// Declarations
	//
	int more = 1;
	int frameDelay = 5;
	
	
	MARS_SYS_COMM6 = 0; //init COMM6 for slave
	

	
	//
	// Init Graphics
	//
	mars_init();

	
	//init screen
	Hw32xScreenClear();
	HwMdClearScreen();
	Hw32xSetBGColor(0,0,0,0);
	sprintf(keyPressedText,"Key Pressed: ...");
	
	currentFB = MARS_VDP_FBCTL & MARS_VDP_FS; 
	
	
	MARS_SYS_COMM6 = MASTER_STATUS_OK; // tells slave to start
	
	//game loop
	while ( more ) {
		handle_input();
		//HwMdClearScreen(); // causes flicker when enabled. 

		
		// wait on flip to finish 
		while ((MARS_VDP_FBCTL & MARS_VDP_FS) != currentFB) {}
		
		//print paused to screen
		HwMdPuts("Hello World", 0x2000, 16, 14);
		HwMdPuts(keyPressedText, 0x2000, 10, 16);
		//
		// draw to FB
		//
		//redraw background 10*BG_TILE_SIZE
		while (MARS_SYS_COMM6 == SLAVE_LOCK) ; // wait until slave isn't blocking
		MARS_SYS_COMM6 = 4; //tell slave to wait
		
		
		
		MARS_SYS_COMM6 = 1; //tell slave to resume
		

		
		//draw the 32X framebuffer line table with offset of 4
		drawLineTable(4);
		

		
		//flip the FB, without waiting on flip 
		currentFB ^= 1;
		MARS_VDP_FBCTL = currentFB; 
		
		//do game loo
		//artificially introduce delay
		Hw32xDelay(frameDelay);
	}
	
    HwMdClearScreen ();
    return 0;
} // end of main function
