#define VDP_PLAN_W				0xB000
#define VDP_PLAN_A              0xC000
#define VDP_PLAN_B              0xE000
#define VDP_HSCROLL_TABLE       0xF800
#define VDP_SPRITE_TABLE        0xFC00

#define PLAN_WIDTH				64
#define PLAN_HEIGHT				32
#define PLAN_WIDTH_SFT			6
#define PLAN_HEIGHT_SFT			5

#define TILE_INDEX_MASK         0x7FF

#define TILE_SYSTEMINDEX        0x0000
#define TILE_USERINDEX          0x0016
#define TILE_FONTINDEX 			(0xD000 >> 5) // 128 tiles after PLAN_A

#define TILE_ATTR(pal, prio, flipV, flipH, index)                                              \
	(((flipH) << 11) + ((flipV) << 12) + ((pal) << 13) + ((prio) << 15) + (index))

void vdp_init();

// Register stuff
void vdp_set_display(uint8_t enabled);
void vdp_set_autoinc(uint8_t val);
void vdp_set_scrollmode(uint8_t hoz, uint8_t vert);

uint16_t vdp_get_palmode();

void vdp_vsync();

// DMA stuff
void vdp_dma_vram(uint32_t from, uint16_t to, uint16_t len);
void vdp_dma_cram(uint32_t from, uint16_t to, uint16_t len);
void vdp_dma_vsram(uint32_t from, uint16_t to, uint16_t len);
uint16_t vdp_dma_status();
void vdp_dma_wait();

// Tile patterns
void vdp_load_tiles(const void *data, uint16_t index, uint16_t num);

// Tile maps
void vdp_set_map_xy(uint16_t plan, uint16_t tile, uint16_t x, uint16_t y);

// Palettes
void vdp_set_colors(uint16_t index, const void *values, uint16_t count);

// Text
void vdp_load_font();
void vdp_puts(uint16_t plan, const char *str, uint16_t x, uint16_t y);
