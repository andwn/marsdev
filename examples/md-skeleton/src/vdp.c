#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vdp.h"

const uint32_t TILE_BLANK[8] = {};
const uint16_t BLANK_DATA[0x80] = {};
const uint16_t PAL_FadeOut[64] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xEEE,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
const uint16_t PAL_FullWhite[64] = {
	0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,
	0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,
	0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,
	0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE,0xEEE
};

// Must be declared as an array instead of a pointer
extern const uint32_t FONT_TILES[];

static volatile uint16_t* const vdp_data_port = (uint16_t*) 0xC00000;
static volatile uint16_t* const vdp_ctrl_port = (uint16_t*) 0xC00004;
static volatile uint32_t* const vdp_ctrl_wide = (uint32_t*) 0xC00004;

uint8_t SCREEN_HEIGHT;
uint8_t SCREEN_HALF_H;
uint8_t FPS;
uint8_t pal_mode;

// Palette vars
static uint16_t pal_current[64];
static uint16_t pal_next[64];
static uint8_t pal_fading;
static uint8_t pal_fadespeed;
static uint8_t pal_fadecnt;

// Sprite vars
static uint16_t sprite_count;
static VDPSprite sprite_table[80];
static uint16_t sprite_ymax;

// Font vars
static uint16_t font_pal;

void vdp_init() {
	// Store pal_mode and adjust some stuff based on it
    pal_mode = *vdp_ctrl_port & 1;
    SCREEN_HEIGHT = pal_mode ? 240 : 224;
	SCREEN_HALF_H = SCREEN_HEIGHT >> 1;
	sprite_ymax = SCREEN_HEIGHT + 32;
	FPS = pal_mode ? 50 : 60;
	// Set the registers
	*vdp_ctrl_port = 0x8004;
	*vdp_ctrl_port = 0x8174 | (pal_mode ? 8 : 0); // Enable display
	*vdp_ctrl_port = 0x8200 | (VDP_PLAN_A >> 10); // Plane A address
	*vdp_ctrl_port = 0x8300 | (VDP_PLAN_W >> 10); // Window address
	*vdp_ctrl_port = 0x8400 | (VDP_PLAN_B >> 13); // Plane B address
	*vdp_ctrl_port = 0x8500 | (VDP_SPRITE_TABLE >> 9); // Sprite list address
	*vdp_ctrl_port = 0x8600;
	*vdp_ctrl_port = 0x8700; // Background color palette index
	*vdp_ctrl_port = 0x8800;
	*vdp_ctrl_port = 0x8900;
	*vdp_ctrl_port = 0x8A01; // Horizontal interrupt timer
	*vdp_ctrl_port = 0x8B00 | (VSCROLL_PLANE << 2) | HSCROLL_PLANE; // Scroll mode
	*vdp_ctrl_port = 0x8C81; // No interlace or shadow/highlight
	*vdp_ctrl_port = 0x8D00 | (VDP_HSCROLL_TABLE >> 10); // HScroll table address
	*vdp_ctrl_port = 0x8E00;
	*vdp_ctrl_port = 0x8F02; // Auto increment
	*vdp_ctrl_port = 0x9001; // Map size (64x32)
	*vdp_ctrl_port = 0x9100; // Window X
	*vdp_ctrl_port = 0x9200; // Window Y
	// Reset the tilemaps
	vdp_map_clear(VDP_PLAN_A);
	vdp_hscroll(VDP_PLAN_A, 0);
	vdp_vscroll(VDP_PLAN_A, 0);
	vdp_map_clear(VDP_PLAN_B);
	vdp_hscroll(VDP_PLAN_B, 0);
	vdp_vscroll(VDP_PLAN_B, 0);
	// Reset sprites
	vdp_sprites_clear();
	vdp_sprites_update();
	// (Re)load the font
	vdp_font_load(FONT_TILES);
	vdp_color(1, 0x000);
	vdp_color(15, 0xEEE);
	// Put blank tile in index 0
	vdp_tiles_load(TILE_BLANK, 0, 1);
}

void vdp_vsync() {
    while(!(*vdp_ctrl_port & 8)) {};
	while(*vdp_ctrl_port & 8) {};
}

// Register stuff

void vdp_set_display(uint8_t enabled) {
	*vdp_ctrl_port = 0x8134 | (enabled ? 0x40 : 0) | (pal_mode ? 0x08 : 0);
}

void vdp_set_autoinc(uint8_t val) {
	*vdp_ctrl_port = 0x8F00 | val;
}

void vdp_set_scrollmode(uint8_t hoz, uint8_t vert) {
	*vdp_ctrl_port = 0x8B00 | (vert << 2) | hoz;
}

void vdp_set_highlight(uint8_t enabled) {
	*vdp_ctrl_port = 0x8C81 | (enabled << 3);
}

void vdp_set_backcolor(uint8_t index) {
    *vdp_ctrl_port = 0x8700 | index;
}

void vdp_set_window(uint8_t x, uint8_t y) {
    *vdp_ctrl_port = 0x9100 | x;
    *vdp_ctrl_port = 0x9200 | y;
}

// DMA stuff

static void dma_do(uint32_t from, uint16_t len, uint32_t cmd) {
	// Setup DMA length (in word here)
    *vdp_ctrl_port = 0x9300 + (len & 0xff);
    *vdp_ctrl_port = 0x9400 + ((len >> 8) & 0xff);
    // Setup DMA address
    from >>= 1;
    *vdp_ctrl_port = 0x9500 + (from & 0xff);
    from >>= 8;
    *vdp_ctrl_port = 0x9600 + (from & 0xff);
    from >>= 8;
    *vdp_ctrl_port = 0x9700 + (from & 0x7f);
    // Enable DMA transfer
    *vdp_ctrl_wide = cmd;
}

void vdp_dma_vram(uint32_t from, uint16_t to, uint16_t len) {
	dma_do(from, len, ((0x4000 + (((uint32_t)to) & 0x3FFF)) << 16) + ((((uint32_t)to) >> 14) | 0x80));
}

void vdp_dma_cram(uint32_t from, uint16_t to, uint16_t len) {
	dma_do(from, len, ((0xC000 + (((uint32_t)to) & 0x3FFF)) << 16) + ((((uint32_t)to) >> 14) | 0x80));
}

void vdp_dma_vsram(uint32_t from, uint16_t to, uint16_t len) {
	dma_do(from, len, ((0x4000 + (((uint32_t)to) & 0x3FFF)) << 16) + ((((uint32_t)to) >> 14) | 0x90));
}

// Tile patterns

void vdp_tiles_load(volatile const uint32_t *data, uint16_t index, uint16_t num) {
	vdp_dma_vram((uint32_t) data, index << 5, num << 4);
}

// Tile maps

void vdp_map_xy(uint16_t plan, uint16_t tile, uint16_t x, uint16_t y) {
    uint32_t addr = plan + ((x + (y << PLAN_WIDTH_SFT)) << 1);
    *vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
	*vdp_data_port = tile;
}

void vdp_map_hline(uint16_t plan, const uint16_t *tiles, uint16_t x, uint16_t y, uint16_t len) {
	vdp_dma_vram((uint32_t) tiles, plan + ((x + (y << PLAN_WIDTH_SFT)) << 1), len);
}

void vdp_map_vline(uint16_t plan, const uint16_t *tiles, uint16_t x, uint16_t y, uint16_t len) {
	vdp_set_autoinc(128);
	vdp_dma_vram((uint32_t) tiles, plan + ((x + (y << PLAN_WIDTH_SFT)) << 1), len);
	vdp_set_autoinc(2);
}

void vdp_map_fill_rect(uint16_t plan, uint16_t index, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t inc) {
	volatile uint16_t tiles[64]; // Garbled graphics on -Ofast without this volatile here
    for(uint16_t yy = 0; yy < h; yy++) {
        for(uint16_t xx = 0; xx < w; xx++) {
            tiles[xx] = index;
            index += inc;
        }
		vdp_dma_vram((uint32_t) tiles, plan + ((x + ((y+yy) << PLAN_WIDTH_SFT)) << 1), w);
    }
}

void vdp_map_clear(uint16_t plan) {
	uint16_t addr = plan;
	while(addr < plan + 0x1000) {
		vdp_dma_vram((uint32_t) BLANK_DATA, addr, 0x80);
		addr += 0x100;
	}
}

// Palettes

void vdp_colors(uint16_t index, const uint16_t *values, uint16_t count) {
	vdp_dma_cram((uint32_t) values, index << 1, count);
    for(uint16_t i = count; i--;) pal_current[index+i] = values[i];
}

void vdp_color(uint16_t index, uint16_t color) {
    index <<= 1;
    *vdp_ctrl_wide = ((0xC000 + (((uint32_t)index) & 0x3FFF)) << 16) + ((((uint32_t)index) >> 14) | 0x00);
    *vdp_data_port = color;
    pal_current[index] = color;
}

void vdp_colors_next(uint16_t index, const uint16_t *values, uint16_t count) {
    for(uint16_t i = count; i--;) pal_next[index+i] = values[i];
}

void vdp_color_next(uint16_t index, uint16_t color) {
    pal_next[index] = color;
}

uint16_t vdp_fade_step() {
	if(!pal_fading) return 0;
	if(++pal_fadecnt >= pal_fadespeed) {
		pal_fadecnt = 0;
		uint16_t colors_changed = 0;
		for(uint16_t i = 64; i--;) {
			uint16_t cR = pal_current[i] & 0x00E;
			uint16_t nR = pal_next[i]    & 0x00E;
			uint16_t cG = pal_current[i] & 0x0E0;
			uint16_t nG = pal_next[i]    & 0x0E0;
			uint16_t cB = pal_current[i] & 0xE00;
			uint16_t nB = pal_next[i]    & 0xE00;
			if(cR != nR) { pal_current[i] += cR < nR ? 0x002 : -0x002; colors_changed++; }
			if(cG != nG) { pal_current[i] += cG < nG ? 0x020 : -0x020; colors_changed++; }
			if(cB != nB) { pal_current[i] += cB < nB ? 0x200 : -0x200; colors_changed++; }
		}
		if(!colors_changed) {
			pal_fading = false;
			return 0;
		}
		vdp_dma_cram((uint32_t) pal_current, 0, 64);
	}
    return 1;
}

void vdp_fade(const uint16_t *src, const uint16_t *dst, uint16_t speed, uint8_t async) {
    if(src) vdp_colors(0, src, 64);
    if(dst) vdp_colors_next(0, dst, 64);
	pal_fading = true;
	pal_fadespeed = speed;
	pal_fadecnt = 0;
    if(!async) {
        while(vdp_fade_step()) {
			vdp_vsync();
		}
    }
}

// Scroll

void vdp_hscroll(uint16_t plan, int16_t hscroll) {
	uint32_t addr = (plan == VDP_PLAN_A) ? VDP_HSCROLL_TABLE : VDP_HSCROLL_TABLE + 2;
	*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
	*vdp_data_port = hscroll;
}

void vdp_hscroll_tile(uint16_t plan, int16_t *hscroll) {
    vdp_set_autoinc(32);
    vdp_dma_vram((uint32_t) hscroll, VDP_HSCROLL_TABLE + (plan == VDP_PLAN_A ? 0 : 2), 32);
    vdp_set_autoinc(2);
}

void vdp_vscroll(uint16_t plan, int16_t vscroll) {
	uint32_t addr = (plan == VDP_PLAN_A) ? 0 : 2;
	*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x10);
	*vdp_data_port = vscroll;
}

// Sprites

void vdp_sprite_add(const VDPSprite *spr) {
    // Exceeded max number of sprites
    if(sprite_count >= 80) return;
    // Prevent drawing off screen sprites
    if((unsigned)(spr->x-96) < 352 && (unsigned)(spr->y-96) < sprite_ymax) {
        sprite_table[sprite_count] = *spr;
        sprite_table[sprite_count].link = sprite_count + 1;
        sprite_count++;
    }
}

void vdp_sprites_add(const VDPSprite *spr, uint16_t num) {
	for(uint16_t i = num; i--;) vdp_sprite_add(&spr[i]);
}

void vdp_sprites_clear() {
	static const VDPSprite NULL_SPRITE = { .x = 0x80, .y = 0x80 };
	sprite_count = 0;
	vdp_sprites_add(&NULL_SPRITE, 1);
}

void vdp_sprites_update() {
	if(!sprite_count) return;
	sprite_table[sprite_count - 1].link = 0; // Mark end of sprite list
	vdp_dma_vram((uint32_t) sprite_table, VDP_SPRITE_TABLE, sprite_count << 2);
	sprite_count = 0;
}

// Font / Text

void vdp_font_load(const uint32_t *tiles) {
	font_pal = 0;
	vdp_tiles_load(tiles, TILE_FONTINDEX, 0x60);
}

void vdp_font_pal(uint16_t pal) {
	font_pal = pal;
}

void vdp_puts(uint16_t plan, const char *str, uint16_t x, uint16_t y) {
	uint32_t addr = plan + ((x + (y << PLAN_WIDTH_SFT)) << 1);
	*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
	for(uint16_t i = 0; i < 64 && *str; ++i) {
		// Wrap around the plane, don't fall to next line
		if(i + x == 64) {
			addr -= x << 1;
			*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
		}
		uint16_t attr = TILE_ATTR(font_pal,1,0,0,TILE_FONTINDEX + *str++ - 0x20);
		*vdp_data_port = attr;
	}
}

void vdp_text_clear(uint16_t plan, uint16_t x, uint16_t y, uint16_t len) {
    uint32_t addr = plan + ((x + (y << PLAN_WIDTH_SFT)) << 1);
	*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
	while(len--) *vdp_data_port = 0;
}
