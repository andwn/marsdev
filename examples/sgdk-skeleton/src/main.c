#include <genesis.h>

int main() {
	PAL_setColor(0, 0x080);
	VDP_drawText("Hello World!", 4, 4);
	while(TRUE) {
		VDP_waitVSync();
	}
	return 0;
}
