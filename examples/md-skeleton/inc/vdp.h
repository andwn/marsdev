// Screen size
#define SCREEN_WIDTH 320
#define SCREEN_HALF_W 160

// On PAL the screen height is 16 pixels more, so these can't be constants
extern uint8_t SCREEN_HEIGHT;
extern uint8_t SCREEN_HALF_H;
extern uint8_t FPS;

typedef struct {
    int16_t y;
    union {
        struct {
            uint8_t size;
            uint8_t link;
        };
        uint16_t size_link;
    };
    uint16_t attr;
    int16_t x;
} VDPSprite;

#define VDP_PLAN_W				((uint16_t)0xB000)
#define VDP_PLAN_A              ((uint16_t)0xC000)
#define VDP_PLAN_B              ((uint16_t)0xE000)
#define VDP_SPRITE_TABLE        ((uint16_t)0xF800)
#define VDP_HSCROLL_TABLE       ((uint16_t)0xFC00)

#define PLAN_WIDTH				64
#define PLAN_HEIGHT				32
#define PLAN_WIDTH_SFT			6
#define PLAN_HEIGHT_SFT			5

#define HSCROLL_PLANE           0
#define HSCROLL_TILE            2
#define HSCROLL_LINE            3
#define VSCROLL_PLANE           0
#define VSCROLL_2TILE           1

#define PAL0					0
#define PAL1					1
#define PAL2					2
#define PAL3					3

#define TILE_SIZE				32
#define TILE_INDEX_MASK         0x7FF

#define TILE_SYSTEMINDEX        0x0000
#define TILE_USERINDEX			0x0010
#define TILE_FONTINDEX			((VDP_PLAN_W >> 5) - 96)
#define TILE_EXTRA1INDEX		(((uint16_t)0xD000) >> 5) // 128 tiles after PLAN_A
#define TILE_EXTRA2INDEX		(((uint16_t)0xF000) >> 5) // 64 tiles after PLAN_B

#define TILE_ATTR(pal, prio, flipV, flipH, index)                               \
	((((uint16_t)flipH) << 11) | (((uint16_t)flipV) << 12) |                    \
	(((uint16_t)pal) << 13) | (((uint16_t)prio) << 15) | ((uint16_t)index))

#define SPRITE_SIZE(w, h)   ((((w) - 1) << 2) | ((h) - 1))

#define sprite_pos(s, px, py) { (s).x = 0x80 + (px); (s).y = 0x80 + (py); }
#define sprite_size(s, w, h) { (s).size = ((((w) - 1) << 2) | ((h) - 1)); }
#define sprite_pri(s, pri)   { (s).attr &= ~(1<<15); (s).attr |= ((pri)&1) << 15; }
#define sprite_pal(s, pal)   { (s).attr &= ~(3<<13); (s).attr |= ((pal)&3) << 13; }
#define sprite_vflip(s, flp) { (s).attr &= ~(1<<12); (s).attr |= ((flp)&1) << 12; }
#define sprite_hflip(s, flp) { (s).attr &= ~(1<<11); (s).attr |= ((flp)&1) << 11; }
#define sprite_index(s, ind) { (s).attr &= ~0x7FF;   (s).attr |= (ind)&0x7FF; }

// 32 bytes of zero, can be sent to VDP to clear any tile
extern const uint32_t TILE_BLANK[8];
// FadeOut is almost completely black, except index 15 which is white
// This allows text to still be displayed after the screen fades to black
extern const uint16_t PAL_FadeOut[64];
extern const uint16_t PAL_FadeOutBlue[64];
// FullWhite is used for a TSC instruction that flashes the screen white
extern const uint16_t PAL_FullWhite[64];
// Remember the pal mode flag so we don't have to read the control port every time
extern uint8_t pal_mode;

// Set defaults, clear everything
void vdp_init();
// Wait until next vblank
void vdp_vsync();

// Register stuff
void vdp_set_display(uint8_t enabled);
void vdp_set_autoinc(uint8_t val);
void vdp_set_scrollmode(uint8_t hoz, uint8_t vert);
void vdp_set_highlight(uint8_t enabled);
void vdp_set_backcolor(uint8_t index);
void vdp_set_window(uint8_t x, uint8_t y);

// Status
uint16_t vdp_get_palmode();
uint16_t vdp_get_vblank();

// DMA stuff
void vdp_dma_vram(uint32_t from, uint16_t to, uint16_t len);
void vdp_dma_cram(uint32_t from, uint16_t to, uint16_t len);
void vdp_dma_vsram(uint32_t from, uint16_t to, uint16_t len);

// Tile patterns
void vdp_tiles_load(volatile const uint32_t *data, uint16_t index, uint16_t num);

// Tile maps
void vdp_map_xy(uint16_t plan, uint16_t tile, uint16_t x, uint16_t y);
void vdp_map_hline(uint16_t plan, const uint16_t *tiles, uint16_t x, uint16_t y, uint16_t len);
void vdp_map_vline(uint16_t plan, const uint16_t *tiles, uint16_t x, uint16_t y, uint16_t len);
void vdp_map_fill_rect(uint16_t plan, uint16_t index, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t inc);
void vdp_map_clear(uint16_t plan);

// Palettes
void vdp_colors(uint16_t index, const uint16_t *values, uint16_t count);
void vdp_color(uint16_t index, uint16_t color);
void vdp_colors_next(uint16_t index, const uint16_t *values, uint16_t count);
void vdp_color_next(uint16_t index, uint16_t color);
uint16_t vdp_fade_step();
void vdp_fade(const uint16_t *src, const uint16_t *dst, uint16_t speed, uint8_t async);

// Scrolling
void vdp_hscroll(uint16_t plan, int16_t hscroll);
void vdp_hscroll_tile(uint16_t plan, int16_t *hscroll);
void vdp_vscroll(uint16_t plan, int16_t vscroll);

// Sprites
void vdp_sprite_add(const VDPSprite *spr);
void vdp_sprites_add(const VDPSprite *spr, uint16_t num);
void vdp_sprites_clear();
void vdp_sprites_update();

// Text
void vdp_font_load(const uint32_t *tiles);
void vdp_font_pal(uint16_t pal);
void vdp_puts(uint16_t plan, const char *str, uint16_t x, uint16_t y);
void vdp_text_clear(uint16_t plan, uint16_t x, uint16_t y, uint16_t len);
