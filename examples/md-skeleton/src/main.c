#define hard_reset() __asm__("move   #0x2700,%sr\n\t" \
                             "move.l (0),%a7\n\t"     \
                             "jmp    _hard_reset")

#define enable_ints __asm__("move #0x2500,%sr")
#define disable_ints __asm__("move #0x2700,%sr")

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vdp.h"

char str_orig[32] = "Malloc Works";

int main() {
    vdp_init();
    enable_ints;
    
	vdp_color(0, 0x080);
	vdp_puts(VDP_PLAN_A, "Hello World!", 4, 4);
	
	char *str_copy = malloc(32);
	memcpy(str_copy, str_orig, 32);
	vdp_puts(VDP_PLAN_A, str_copy, 4, 6);
	free(str_copy);
	
	while(true) {
		vdp_vsync();
	}
	
	return 0;
}
