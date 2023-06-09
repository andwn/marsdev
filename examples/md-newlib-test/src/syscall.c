// New versions of Newlib throw linker warnings if these functions are not defined.
// They are included here mainly to work around the warnings, but you can
// make them do something more advanced if you want to use stuff like printf.
// The (void)s on the first line are to suppress unused variable warnings.

#include "md.h"

void _exit() {
	hard_reset();
}
int close(int file) {
	(void)file;
	return -1;
}
int fstat(int file, struct stat *st) {
	(void)file; (void)st;
	return 0;
}
int getpid() {
	return 0;
}
int isatty(int file) {
	(void)file;
	return 1;
}
int kill(int pid, int sig) {
	(void)pid; (void)sig;
	return 0;
}
int lseek(int file, int ptr, int dir) {
	(void)file; (void)ptr; (void)dir;
	return 0;
}
int open(const char *name, int flags, int mode) {
	(void)name; (void)flags; (void)mode;
	return -1;
}
int read(int file, char *ptr, int len) {
	(void)file; (void)ptr; (void)len;
	return 0;
}

extern uint32_t __end;
void* sbrk(intptr_t incr) {
	static uintptr_t current_break = (uintptr_t)&__end;
	uintptr_t old_break = current_break;
	current_break += incr;
	return (void*) old_break;
}

// This will direct stdout and stderr to draw font tiles on plane A,
// between rows 16 and 26, and wrap text longer than 36 characters
#define CONSOLE_X1 2
#define CONSOLE_Y1 16
#define CONSOLE_X2 38
#define CONSOLE_Y2 26
uint16_t write_y = CONSOLE_Y1;
int write(int file, const char *ptr, int len) {
	if(file != 1 && file != 2) return len;
	uint16_t x = CONSOLE_X1;
	for(int i = 0; i < len; i++) {
		if(ptr[i] == '\n') { // Newline
			x = CONSOLE_X1;
			if(++write_y >= CONSOLE_Y2) write_y = CONSOLE_Y1;
		} else {
			vdp_map_xy(VDP_PLAN_A, TILE_ATTR(0,1,0,0,TILE_FONTINDEX+ptr[i]-0x20), x, write_y);
			if(++x >= CONSOLE_X2) { // Wrap
				x = CONSOLE_X1;
				if(++write_y >= CONSOLE_Y2) write_y = CONSOLE_Y1;
			}
		}
	}
	return len;
}

