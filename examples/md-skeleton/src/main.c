#include "md.h"

int main() {
    vdp_init();
    enable_ints;
    
	vdp_color(0, 0x080);
	vdp_puts(VDP_PLAN_A, "Hello World!", 4, 4);
	
	while(1) {
		vdp_vsync();
	}
	
	return 0;
}
