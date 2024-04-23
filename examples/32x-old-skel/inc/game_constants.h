#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__
/*
* Game specific constants go here
*/

/* tile related constants */
#define BG_TILE_SIZE 16
#define MAP_SCREEN_WIDTH 21
#define MAP_SCREEN_HEIGHT 14

#define WORLD_WIDTH 100

/*
* Constants for is in view or out of view
*/
#define GC_IN_VIEW 1
#define GC_OUT_OF_VIEW 0

/*
* Error codes
*/
#define ERR_MALLOC_FAIL -4

/*
* Master / Slave SH-2 Communication 
*/
#define MASTER_STATUS_OK 1
#define MASTER_LOCK 4
#define SLAVE_STATUS_OK 2
#define SLAVE_LOCK 8

#endif
