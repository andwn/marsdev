#include <genesis.h>
#include "resources.h"

int main() {
	VDP_drawText("Hello World!", 4, 4);
	// From the moon example
	PAL_setPalette(PAL1, moon.palette->data, CPU);
	VDP_drawImageEx(VDP_PLAN_B, &moon, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 28, 18, 0, CPU);
	
	// Print the text data that got stored in each bank
	const char *text = (const char*)SYS_getFarData((void*)text1);
	VDP_drawText(text, 4, 6);
	text = (const char*)SYS_getFarData((void*)text2);
	VDP_drawText(text, 4, 7);
	text = (const char*)SYS_getFarData((void*)text3);
	VDP_drawText(text, 4, 8);
	text = (const char*)SYS_getFarData((void*)text4);
	VDP_drawText(text, 4, 9);
	text = (const char*)SYS_getFarData((void*)text5);
	VDP_drawText(text, 4, 10);
	text = (const char*)SYS_getFarData((void*)text6);
	VDP_drawText(text, 4, 11);
	text = (const char*)SYS_getFarData((void*)text7);
	VDP_drawText(text, 4, 12);
	text = (const char*)SYS_getFarData((void*)text8);
	VDP_drawText(text, 4, 13);
	text = (const char*)SYS_getFarData((void*)text9);
	VDP_drawText(text, 4, 14);
	
	while(TRUE) {
		VDP_waitVSync();
	}
	return 0;
}
