#ifndef CPPTEST_VDP_H
#define CPPTEST_VDP_H

#include "megadrive.hpp"

namespace vdp {

    // VRAM Addresses
    const uint16 Window = 0xB000;
    const uint16 PlaneA = 0xC000;
    const uint16 PlaneB = 0xE000;
    const uint16 SpriteTable  = 0xF800;
    const uint16 HScrollTable = 0xFC00;

    // Plane Size
    const uint16 PlaneWidthSft  = 6;
    const uint16 PlaneHeightSft = 5;
    const uint16 PlaneWidth  = 1 << PlaneWidthSft;
    const uint16 PlaneHeight = 1 << PlaneHeightSft;

    // Scroll Modes
    typedef enum : uint8 {
        HSCROLL_PLANE = 0, HSCROLL_TILE = 2, HSCROLL_LINE = 3
    } HScrollMode;
    typedef enum : uint8 {
        VSCROLL_PLANE = 0, VSCROLL_2TILE = 1
    } VScrollMode;

    // Tile Attributes
    const uint16 PRI = (1 << 15);
    const uint16 PAL0 = (0 << 13);
    const uint16 PAL1 = (1 << 13);
    const uint16 PAL2 = (2 << 13);
    const uint16 PAL3 = (3 << 13);
    const uint16 VFLIP = (1 << 12);
    const uint16 HFLIP = (1 << 11);

    // Hardware Registers
    static volatile uint16* const data_port = (uint16*) 0xC00000;
    static volatile uint16* const ctrl_port = (uint16*) 0xC00004;
    static volatile uint32* const ctrl_wide = (uint32*) 0xC00004;
    static volatile uint16* const hv_counter = (uint16*) 0xC00008;

#define TILE_EXTRA1_INDEX        (((uint16)0xD000) >> 5) // 128 tiles after PLAN_A
#define TILE_FONT_INDEX            (((uint16)0xF000) >> 5) // 64 tiles after PLAN_B

    // Set defaults, clear everything
    void init();

    // Wait until next vblank
    void vsync();

    // Register stuff
    void set_display(uint8 enabled);

    void set_autoinc(uint8 val);

    void set_scrollmode(uint8 hoz, uint8 vert);

    void set_highlight(uint8 enabled);

    void set_backcolor(uint8 index);

    void set_window(uint8 x, uint8 y);

    // DMA stuff
    void dma_vram(uint32 from, uint16 to, uint16 len);

    void dma_cram(uint32 from, uint16 to, uint16 len);

    void dma_vsram(uint32 from, uint16 to, uint16 len);

    // Tile patterns
    void tiles_load(volatile const uint16 *data, uint16 index, uint16 num);

    // Tile maps
    void map_xy(uint16 plan, uint16 tile, uint16 x, uint16 y);

    void map_hline(uint16 plan, const uint16 *tiles, uint16 x, uint16 y, uint16 len);

    void map_vline(uint16 plan, const uint16 *tiles, uint16 x, uint16 y, uint16 len);

    void map_fill_rect(uint16 plan, uint16 index, uint16 x, uint16 y, uint16 w, uint16 h, uint8 inc);

    void map_clear(uint16 plan);

    // Palettes
    void colors(uint16 index, const uint16 *values, uint16 count);

    void color(uint16 index, uint16 color);

    void colors_next(uint16 index, const uint16 *values, uint16 count);

    void color_next(uint16 index, uint16 color);

    uint16 fade_step();

    void fade(const uint16 *src, const uint16 *dst, uint16 speed, uint8 async);

    // Scrolling
    void hscroll(uint16 plan, int16 hscroll);

    void hscroll_tile(uint16 plan, int16 *hscroll);

    void vscroll(uint16 plan, int16 vscroll);

}

#endif // CPPTEST_VDP_H
