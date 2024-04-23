#include "mars.h"
#include "string.h"
#include "images.h"

uint32_t lastTick = 0;
uint16_t currentFB = 0;

char joypadStateText[2][16];

uint16_t joypadState[2] = {0};
uint16_t joypadPrevState[2] = {0};

// Swap backbuffer and wait for next tick from MD
void swapBuffers() {
	while(lastTick == MARS_SYS_COMM12);
	MARS_VDP_FBCTL = currentFB ^ 1;
	while((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB);
	currentFB ^= 1;	
	lastTick = MARS_SYS_COMM12;
}

// Update joypad states
void joypad_update(uint8_t player) {
	joypadPrevState[player] = joypadState[player];
	HwMdReadPad(player);
	joypadState[player] = MARS_SYS_COMM8;
	// Print controller state to the screen
	const char btn[12] = "UDLRBCASZYXM";
	for(int i = 0; i < ((joypadState[player] & 0x1000) ? 12 : 8); i++) {
		if(joypadState[player] & (1 << i)) {
			joypadStateText[player][i] = btn[i];
		} else {
			joypadStateText[player][i] = '.';
		}
	}
	joypadStateText[player][12] = 0;
}

// Primary CPU main loop
int m_main(void) {
	Hw32xInit(MARS_VDP_MODE_256, 0);
	Hw32xSetBGColor(0,0,0,0);
	Hw32xDelay(1); // Wait for MD's first VInt to complete
	HwMdPuts("HELLO WORLD", 0x2000, 10, 14);
	//game loop
	for(;;) {
		joypad_update(0);
		joypad_update(1);
		HwMdPuts(joypadStateText[0], 0x2000, 10, 16);
		HwMdPuts(joypadStateText[1], 0x2000, 10, 18);

		swapBuffers();
	}
	return 0;
}
