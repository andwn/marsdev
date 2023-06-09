#include <genesis.h>
#include "resources.h"

int main() {
	VDP_drawText("Hello World!", 4, 4);
	// Fromt he moon example
	PAL_setPalette(PAL1, moon.palette->data, DMA);
	VDP_drawImageEx(BG_A, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 12, 12, 0, CPU);
	
	while(TRUE) {
		VDP_waitVSync();
	}
	return 0;
}
