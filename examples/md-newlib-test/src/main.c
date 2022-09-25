#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md.h"

const char str_orig[64] = "malloc() and memcpy() work.";
char str_mem[64] = "Does memmove() work? Nope.\0Yes, it does!";

int main() {
    vdp_init();
    enable_ints;
    
	vdp_color(0, 0x080);
	vdp_puts(VDP_PLAN_A, "Hello World!", 2, 4);
	
	char *str_copy;
	chk_malloc(str_copy, 64);
	memcpy(str_copy, str_orig, 64);
	vdp_puts(VDP_PLAN_A, str_copy, 2, 6);
	free(str_copy);
	
	memmove(str_mem+21, str_mem+27, 14);
	vdp_puts(VDP_PLAN_A, str_mem, 2, 8);
	
	puts("puts() works.");
	printf("printf() works.\n");
	printf("This is a really long %s that should wrap to multiple lines.\n", "string");
	
	while(1) {
		vdp_vsync();
	}
	
	return 0;
}
