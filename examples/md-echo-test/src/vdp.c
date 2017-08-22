#include "stdint.h"
#include "vdp.h"
#include "res_tset.h"

extern volatile uint8_t vblank;

static volatile uint16_t* const vdp_data_port = (uint16_t*) 0xC00000;
static volatile uint16_t* const vdp_ctrl_port = (uint16_t*) 0xC00004;
// 4 byte ctrl port (the extra 2 bytes are a mirror of first 2)
static volatile uint32_t* const vdp_ctrl_wide = (uint32_t*) 0xC00004;

void vdp_init() {
	// Set the registers
	*vdp_ctrl_port = 0x8004;
	*vdp_ctrl_port = 0x8174; // Enable display
	*vdp_ctrl_port = 0x8200 | (VDP_PLAN_A >> 10); // Plane A address
	*vdp_ctrl_port = 0x8300 | (VDP_PLAN_W >> 10); // Window address
	*vdp_ctrl_port = 0x8400 | (VDP_PLAN_B >> 13); // Plane B address
	*vdp_ctrl_port = 0x8500 | (VDP_SPRITE_TABLE >> 9); // Sprite list address
	*vdp_ctrl_port = 0x8600;
	*vdp_ctrl_port = 0x8700; // Background color palette index
	*vdp_ctrl_port = 0x8800;
	*vdp_ctrl_port = 0x8900;
	*vdp_ctrl_port = 0x8A01; // Horizontal interrupt timer
	*vdp_ctrl_port = 0x8B00; // Scroll mode
	*vdp_ctrl_port = 0x8C81; // No interlace or shadow/highlight
	*vdp_ctrl_port = 0x8D00 | (VDP_HSCROLL_TABLE >> 10); // HScroll table address
	*vdp_ctrl_port = 0x8E00;
	*vdp_ctrl_port = 0x8F02; // Auto increment
	*vdp_ctrl_port = 0x9001; // Map size (64x32)
	*vdp_ctrl_port = 0x9100; // Window X
	*vdp_ctrl_port = 0x9200; // Window Y
	
	vdp_load_font();
}

// Register stuff

void vdp_set_display(uint8_t enabled) {
	*vdp_ctrl_port = 0x8134 | (enabled ? 0x40 : 0x00);
}

void vdp_set_autoinc(uint8_t val) {
	*vdp_ctrl_port = 0x8F00 | val;
}

void vdp_set_scrollmode(uint8_t hoz, uint8_t vert) {
	*vdp_ctrl_port = 0x8B00 | (vert << 2) | hoz;
}

uint16_t vdp_get_palmode() {
	return *vdp_ctrl_port & 1;
}

void vdp_vsync() {
	vblank = 1;
	while(vblank);
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
	dma_do(from, len, ((0x4000 + ((to) & 0x3FFF)) << 16) + (((to) >> 14) | 0x80));
}

void vdp_dma_cram(uint32_t from, uint16_t to, uint16_t len) {
	dma_do(from, len, ((0xC000 + ((to) & 0x3FFF)) << 16) + (((to) >> 14) | 0x80));
}

void vdp_dma_vsram(uint32_t from, uint16_t to, uint16_t len) {
	dma_do(from, len, ((0x4000 + ((to) & 0x3FFF)) << 16) + (((to) >> 14) | 0x90));
}

uint16_t vdp_dma_status() {
	return *vdp_ctrl_port & 2;
}

void vdp_dma_wait() {
	while(*vdp_ctrl_port & 2);
}

// Tile patterns

void vdp_load_tiles(const void *data, uint16_t index, uint16_t num) {
	vdp_dma_wait();
	vdp_dma_vram((uint32_t) data, index << 5, num << 4);
}

// Tile maps

void vdp_set_tilemap_xy(uint16_t plan, uint16_t tile, uint16_t x, uint16_t y) {
    uint16_t addr = plan + ((x + (y << PLAN_WIDTH_SFT)) << 1);
    *vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
	*vdp_data_port = tile;
}

// Palettes

void vdp_set_colors(uint16_t index, const void *values, uint16_t count) {
	vdp_dma_wait();
	vdp_dma_cram((uint32_t) values, index << 1, count);
}

// Font / Text

void vdp_load_font() {
	vdp_load_tiles(res_tset_font, TILE_FONTINDEX, 0x60);
}

void vdp_puts(uint16_t plan, const char *str, uint16_t x, uint16_t y) {
	uint16_t addr = plan + ((x + (y << PLAN_WIDTH_SFT)) << 1);
	*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
	
	for(uint16_t i = 0; i < 64 && *str; ++i) {
		// Wrap around the plane, don't fall to next line
		if(i + x == 64) {
			addr -= x << 1;
			*vdp_ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
		}
		uint16_t attr = TILE_ATTR(0,1,0,0,TILE_FONTINDEX + *str++ - 0x20);
		*vdp_data_port = attr;
	}
}
