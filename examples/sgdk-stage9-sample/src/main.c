#include <genesis.h>
#include "s9_map.h"
#include "resources.h"

#define SCREEN_W		320
#define SCREEN_H		224
#define SCREEN_HALF_W	(SCREEN_W / 2)
#define SCREEN_HALF_H	(SCREEN_H / 2)
#define BLOCK_SIZE		16
#define WALK_SPEED		1
#define RUN_SPEED		2

enum { STATE_STAND, STATE_WALK };
enum { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN };

typedef struct {
	Sprite *sprite;
	s16 x, y;
	u8 state, direction;
} Player;

typedef struct {
	s16 x, y;
	s8 x_morph, y_morph;
} Camera;

// Player standing near middle of screen in upper left area of the map, facing downward
Player player = { NULL, 8 * BLOCK_SIZE, 6 * BLOCK_SIZE, STATE_STAND, DIR_DOWN };
Camera camera = { 0, 0, 0, 0 };

// Mophs the stage, meaning load rows/columns of tiles as the camera scrolls over them
void vblank() {
	if(camera.x_morph < 0) { // Draw left column
		SMAP_drawArea(
			camera.x / BLOCK_SIZE + (camera.x_morph + 1), 
			camera.y / BLOCK_SIZE + camera.y_morph, 
			abs(camera.x_morph), 15);
	} else if(camera.x_morph > 0) { // Draw right column
		SMAP_drawArea(
			camera.x / BLOCK_SIZE + 20 + (camera.x_morph - 1), 
			camera.y / BLOCK_SIZE + camera.y_morph, 
			abs(camera.x_morph), 15);
	}
	if(camera.y_morph < 0) { // Draw top row
		SMAP_drawArea(
			camera.x / BLOCK_SIZE + camera.x_morph, 
			camera.y / BLOCK_SIZE + (camera.y_morph + 1), 
			21, abs(camera.y_morph));
	} else if(camera.y_morph > 0) { // Draw bottom row
		SMAP_drawArea(
			camera.x / BLOCK_SIZE + camera.x_morph, 
			camera.y / BLOCK_SIZE + 14 + (camera.y_morph - 1), 
			21, abs(camera.y_morph));
	}
	camera.x_morph = camera.y_morph = 0;
	// Actually scroll the tile planes
	VDP_setHorizontalScroll(BG_B, -camera.x);
	VDP_setVerticalScroll(BG_B, camera.y);
	VDP_setHorizontalScroll(BG_A, -camera.x);
	VDP_setVerticalScroll(BG_A, camera.y);
}

int main() {
	u16 joy;
	SPR_init();
	// Interrupts should be disabled while doing VDP stuff
	SYS_disableInts();
	//VDP_setEnable(0);
	//VDP_setPlanSize(64, 32);
	// Load sample tiles & palettes
	VDP_setPalette(PAL0, PAL_Character.data);
	VDP_setPalette(PAL2, PAL_Tiny16.data);
	VDP_loadTileSet(&TS_Tiny16, TILE_USERINDEX, DMA);
	player.sprite = SPR_addSprite(&SPR_Character, player.x, player.y, TILE_ATTR(PAL0,0,0,0));
	SMAP_loadData(MAP_World);
	SMAP_drawArea(camera.x / BLOCK_SIZE, camera.y / BLOCK_SIZE, 21, 15);
	// VInt function used for scrolling
	//SYS_setVIntCallback(vblank);
	//VDP_setEnable(1);
	SYS_enableInts();
	//SND_startPlay_XGM(BGM_Song);
	while(1) {
		// Update player according to user input
		joy = JOY_readJoypad(JOY_1);
		if(player.state == STATE_STAND) {
			// Start to walk if pressing any direction, make sure the player isn't
			// going out of bounds though. Holding B makes walking faster
			if((joy & BUTTON_LEFT) && player.x > 0) {
				player.state = STATE_WALK;
				player.direction = DIR_LEFT;
			} else if((joy & BUTTON_UP) && player.y > 0) {
				player.state = STATE_WALK;
				player.direction = DIR_UP;
			} else if((joy & BUTTON_RIGHT) && player.x / BLOCK_SIZE < SMAP_getWidth() - 1) {
				player.state = STATE_WALK;
				player.direction = DIR_RIGHT;
			} else if((joy & BUTTON_DOWN) && player.y / BLOCK_SIZE < SMAP_getHeight() - 1) {
				player.state = STATE_WALK;
				player.direction = DIR_DOWN;
			} else if(player.sprite->animInd != player.direction) {
				// Show standing animation if not moving
				SPR_setAnim(player.sprite, player.direction);
			}
		}
		if(player.state == STATE_WALK) {
			// Move in walking direction
			s16 old_x = player.x, old_y = player.y;
			if(player.direction == DIR_LEFT) 
				player.x -= (joy & BUTTON_B) ? RUN_SPEED : WALK_SPEED;
			else if(player.direction == DIR_UP) 
				player.y -= (joy & BUTTON_B) ? RUN_SPEED : WALK_SPEED;
			else if(player.direction == DIR_RIGHT) 
				player.x += (joy & BUTTON_B) ? RUN_SPEED : WALK_SPEED;
			else if(player.direction == DIR_DOWN) 
				player.y += (joy & BUTTON_B) ? RUN_SPEED : WALK_SPEED;
			// Set player sprite position
			SPR_setPosition(player.sprite, player.x - camera.x, player.y - camera.y);
			// Make sure player sprite is walking and facing right direction
			if(player.sprite->animInd != player.direction + 4) {
				SPR_setAnim(player.sprite, player.direction + 4);
			}
			// If the next tile has been reached, switch back to standing state
			if((player.x % BLOCK_SIZE == 0) && (player.y % BLOCK_SIZE == 0)) {
				player.state = STATE_STAND;
			}
			// Less naive check since running may not always be aligned to the grid
			if((old_x % BLOCK_SIZE != 0 && player.x / BLOCK_SIZE != old_x / BLOCK_SIZE) ||
				(old_y % BLOCK_SIZE != 0 && player.y / BLOCK_SIZE != old_y / BLOCK_SIZE)) {
				player.state = STATE_STAND;
				// Align to grid
				player.x += ((player.x % BLOCK_SIZE) >= (BLOCK_SIZE / 2))
					? BLOCK_SIZE - (player.x % BLOCK_SIZE)
					: -(player.x % BLOCK_SIZE);
				player.y += ((player.y % BLOCK_SIZE) >= (BLOCK_SIZE / 2))
					? BLOCK_SIZE - (player.y % BLOCK_SIZE)
					: -(player.y % BLOCK_SIZE);
			}
			
			// Update camera based on player movement
			old_x = camera.x; old_y = camera.y;
			camera.x = player.x - SCREEN_HALF_W + 8;
			camera.y = player.y - SCREEN_HALF_H + 8;
			// Keep camera in bounds
			if(camera.x < 0) camera.x = 0;
			else if(camera.x > SMAP_getWidth() * BLOCK_SIZE - SCREEN_W) 
				camera.x = SMAP_getWidth() * BLOCK_SIZE - SCREEN_W;
			if(camera.y < 0) camera.y = 0;
			else if(camera.y > SMAP_getHeight() * BLOCK_SIZE - SCREEN_H)
				camera.y = SMAP_getHeight() * BLOCK_SIZE - SCREEN_H;
			// These will be nonzero when new tiles come onto the screen
			camera.x_morph = camera.x / BLOCK_SIZE - old_x / BLOCK_SIZE;
			camera.y_morph = camera.y / BLOCK_SIZE - old_y / BLOCK_SIZE;
			
		}
		
		SPR_update();
		//VDP_waitVSync();
		SYS_doVBlankProcess();
		vblank();
	}
	return 0; // This is just to make GCC shut up
}
