#include <genesis.h>
#include "resources.h"

int main() {
	VDP_drawText("Hello World!", 4, 4);
	// From the moon example
	VDP_setPalette(PAL1, moon.palette->data);
	VDP_drawImageEx(VDP_PLAN_B, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 28, 18, 0, CPU);
	
	// Print the text data that got stored in each bank
	const char *text = (const char*)SYS_getFarData(text1);
	VDP_drawText(text, 4, 6);
	text = (const char*)SYS_getFarData(text2);
	VDP_drawText(text, 4, 7);
	text = (const char*)SYS_getFarData(text3);
	VDP_drawText(text, 4, 8);
	text = (const char*)SYS_getFarData(text4);
	VDP_drawText(text, 4, 9);
	text = (const char*)SYS_getFarData(text5);
	VDP_drawText(text, 4, 10);
	text = (const char*)SYS_getFarData(text6);
	VDP_drawText(text, 4, 11);
	text = (const char*)SYS_getFarData(text7);
	VDP_drawText(text, 4, 12);
	text = (const char*)SYS_getFarData(text8);
	VDP_drawText(text, 4, 13);
	text = (const char*)SYS_getFarData(text9);
	VDP_drawText(text, 4, 14);
	
	while(TRUE) {
		VDP_waitVSync();
	}
	return 0;
}
