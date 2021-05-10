// Slave SH2 support code ----------------------------------------------
//#include <stdlib.h>
#include "types.h"
#include "32x.h"
#include "hw_32x.h"
#include "game_constants.h"
#include "graphics.h"
#include "shared_objects.h"



/*
* Function called from sh2_crt0.s to start the slave CPU
*/
void slave(void)
{
	// any local vars here... watch the slave sh2 stack size!
	unsigned long ct = 0;

	
	
	//wait for main to initialize stuff
	while (MARS_SYS_COMM6 != MASTER_STATUS_OK) ; // wait until master has signaled to start
	MARS_SYS_COMM6 = SLAVE_STATUS_OK; //tell master slave is starting
	
	// code goes here 
    while (1){
		
		//delay
		ct = MARS_SYS_COMM12 + 3;
		
		//Updates while unpaused (movement, AI)
		if(paused == UNPAUSED){
		
			while (MARS_SYS_COMM6 == MASTER_LOCK) ; // wait until master has signaled to start
			MARS_SYS_COMM6 = SLAVE_LOCK; //tell master slave is running
			
			//could put misc game logic here to save CPU e.g. AI
			//uses shared memory with the master process (main.c)
			//does not draw graphics or contact MD
			//...
			
			MARS_SYS_COMM6 = SLAVE_STATUS_OK; //tell master slave is done
		}//end if paused == UNPAUSED
		
		
		//will delay until time is up
		while (MARS_SYS_COMM12 < ct) ;
	}
	
	    
}
