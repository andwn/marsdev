#include "mars.h"
#include "string.h"

static int X = 0, Y = 0;
static int MX = 40, MY = 25;
static int init = 0;
static uint16_t fgc = 0, bgc = 0;
static uint8_t fgs = 0, bgs = 0;

static uint16_t currentFB = 0;

void Hw32xSetFGColor(int s, int r, int g, int b) {
	volatile uint16_t *palette = &MARS_CRAM;
	fgs = s;
	fgc = COLOR(r, g, b);
	palette[fgs] = fgc;
}

void Hw32xSetBGColor(int s, int r, int g, int b) {
	volatile uint16_t *palette = &MARS_CRAM;
	bgs = s;
	bgc = COLOR(r, g, b);
	palette[bgs] = bgc;
}

void Hw32xInit(int vmode, int lineskip) {
	volatile uint16_t *frameBuffer16 = &MARS_FRAMEBUFFER;

	// Wait for the SH2 to gain access to the VDP
	while((MARS_SYS_INTMSK & MARS_SH2_ACCESS_VDP) == 0);

	if(vmode == MARS_VDP_MODE_256) {
		// Set 8-bit paletted mode, 224 lines
		MARS_VDP_DISPMODE = MARS_224_LINES | MARS_VDP_MODE_256;

		// Flip the framebuffer selection bit and wait for it to take effect
		MARS_VDP_FBCTL = currentFB ^ 1;
		while((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
		currentFB ^= 1;
		// rewrite line table
		for(int i=0; i<224/(lineskip+1); i++) {
			int j = lineskip + 1;
			while(j) {
				frameBuffer16[i*(lineskip+1) + (lineskip + 1 - j)] = i*160 + 0x100; /* word offset of line */
				j--;
			}
		}
		// clear screen
		for(int i=0x100; i<0x10000; i++) frameBuffer16[i] = 0;

		// Flip the framebuffer selection bit and wait for it to take effect
		MARS_VDP_FBCTL = currentFB ^ 1;
		while((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
		currentFB ^= 1;
		// rewrite line table
		for(int i=0; i<224/(lineskip+1); i++) {
			int j = lineskip + 1;
			while(j) {
				frameBuffer16[i*(lineskip+1) + (lineskip + 1 - j)] = i*160 + 0x100; /* word offset of line */
				j--;
			}
		}
		// clear screen
		for(int i=0x100; i<0x10000; i++) frameBuffer16[i] = 0;

		MX = 40;
		MY = 28/(lineskip+1);
	} else if(vmode == MARS_VDP_MODE_32K) {
		// Set 16-bit direct mode, 224 lines
		MARS_VDP_DISPMODE = MARS_224_LINES | MARS_VDP_MODE_32K;

		// Flip the framebuffer selection bit and wait for it to take effect
		MARS_VDP_FBCTL = currentFB ^ 1;
		while ((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
		currentFB ^= 1;
		// rewrite line table
		for(int i=0; i<224/(lineskip+1); i++) {
			if (lineskip) {
				int j = lineskip + 1;
				while (j)  {
					frameBuffer16[i*(lineskip+1) + (lineskip + 1 - j)] = i*320 + 0x100; /* word offset of line */
					j--;
				}
			} else {
				if(i<200) frameBuffer16[i] = i*320 + 0x100; /* word offset of line */
				else frameBuffer16[i] = 200*320 + 0x100;    /* word offset of line */
			}
		}
		// clear screen
		for(int i=0x100; i<0x10000; i++) frameBuffer16[i] = 0;

		// Flip the framebuffer selection bit and wait for it to take effect
		MARS_VDP_FBCTL = currentFB ^ 1;
		while((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
		currentFB ^= 1;
		// rewrite line table
		for(int i=0; i<224/(lineskip+1); i++) {
			if (lineskip) {
				int j = lineskip + 1;
				while (j) {
					frameBuffer16[i*(lineskip+1) + (lineskip + 1 - j)] = i*320 + 0x100; /* word offset of line */
					j--;
				}
			} else {
				if(i<200) frameBuffer16[i] = i*320 + 0x100; /* word offset of line */
				else frameBuffer16[i] = 200*320 + 0x100; /* word offset of line */
			}
		}
		// clear screen
		for(int i=0x100; i<0x10000; i++) frameBuffer16[i] = 0;

		MX = 40;
		MY = 25/(lineskip+1);
	}

	Hw32xSetFGColor(255,31,31,31);
	Hw32xSetBGColor(0,0,0,0);
	X = Y = 0;
	init = vmode;
}

int Hw32xScreenGetX(void) {
	return X;
}

int Hw32xScreenGetY(void) {
	return Y;
}

void Hw32xScreenSetXY(int x, int y) {
	if(x<MX && x>=0) X = x;
	if(y<MY && y>=0) Y = y;
}

void Hw32xScreenClear(void) {
	int l = (init == MARS_VDP_MODE_256) ? 320*224/2 + 0x100 : 320*200 + 0x100;
	volatile unsigned short *frameBuffer16 = &MARS_FRAMEBUFFER;

	// clear screen
	for(int i=0x100; i<l; i++) frameBuffer16[i] = 0;

	// Flip the framebuffer selection bit and wait for it to take effect
	MARS_VDP_FBCTL = currentFB ^ 1;
	while((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
	currentFB ^= 1;

	// clear screen
	for(int i=0x100; i<l; i++) frameBuffer16[i] = 0;

	Hw32xSetFGColor(255,31,31,31);
	Hw32xSetBGColor(0,0,0,0);
	X = Y = 0;
}

void Hw32xDelay(int ticks) {
	unsigned long ct = MARS_SYS_COMM12 + ticks;
	while(MARS_SYS_COMM12 < ct) ;
}

void Hw32xScreenFlip(int wait) {
	// Flip the framebuffer selection bit
	MARS_VDP_FBCTL = currentFB ^ 1;
	if(wait) {
		while((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
		currentFB ^= 1;
	}
}

void Hw32xFlipWait(void) {
	while ((MARS_VDP_FBCTL & MARS_VDP_FS) == currentFB) ;
	currentFB ^= 1;
}


// MD Command support code ---------------------------------------------

void HwMdReadPad(uint8_t port) {
	while(MARS_SYS_COMM0) ; // wait until 68000 has responded to any earlier requests
	MARS_SYS_COMM0 = 0x0300 | port;
	while(MARS_SYS_COMM0) ;
}

void HwMdClearScreen(void) {
	while(MARS_SYS_COMM0) ; // wait until 68000 has responded to any earlier requests
	MARS_SYS_COMM0 = 0x0400; // Clear Screen (Name Table B)
	while(MARS_SYS_COMM0) ;
}

void HwMdSetOffset(unsigned short offset) {
	while(MARS_SYS_COMM0) ; // wait until 68000 has responded to any earlier requests
	MARS_SYS_COMM2 = offset;
	MARS_SYS_COMM0 = 0x0500; // Set offset (into either Name Table B or VRAM)
	while(MARS_SYS_COMM0) ;
}

void HwMdSetNTable(unsigned short word) {
	while(MARS_SYS_COMM0) ; // wait until 68000 has responded to any earlier requests
	MARS_SYS_COMM2 = word;
	MARS_SYS_COMM0 = 0x0600; // Set word at offset in Name Table B
	while(MARS_SYS_COMM0) ;
}

void HwMdSetVram(unsigned short word) {
	while(MARS_SYS_COMM0) ; // wait until 68000 has responded to any earlier requests
	MARS_SYS_COMM2 = word;
	MARS_SYS_COMM0 = 0x0700; // Set word at offset in VRAM
	while(MARS_SYS_COMM0) ;
}

static void NextChr(char c, uint16_t color) {
	if(c >= '0' && c <= '9') {
		c = c - '0' + 2;
	} else if(c >= 'A' && c <= 'Z') {
		c = c - 'A' + 12;
	} else if(c >= 'a' && c <= 'z') {
		c = c - 'a' + 12;
	} else if(c == ' ') {
		c = 0;
	} else {
		c = 1;
	}
	HwMdSetNTable(c | color);
}

void HwMdPuts(char *str, uint16_t color, int x, int y) {
	HwMdSetOffset(((y<<6) | x) << 1);
	while(*str) NextChr(*str++, color);
}

void HwMdPutc(char chr, uint16_t color, int x, int y) {
	HwMdSetOffset(((y<<6) | x) << 1);
	NextChr(chr, color);
}
