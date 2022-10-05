#include "sprite.hpp"
#include "text.hpp"

#include "vdp.hpp"

extern const uint16 FONT_TILES[];

const uint16 blank_data[0x80] = {};

namespace vdp {

    // Palette vars
    static uint16 pal_current[64];
    static uint16 pal_next[64];
    static uint8 pal_fading;
    static uint8 pal_fadespeed;
    static uint8 pal_fadecnt;

    void init() {
        // Set the registers
        *ctrl_port = 0x8004;
        *ctrl_port = 0x8174; // Enable display
        *ctrl_port = 0x8200 | (PlaneA >> 10); // Plane A address
        *ctrl_port = 0x8300 | (Window >> 10); // Window address
        *ctrl_port = 0x8400 | (PlaneB >> 13); // Plane B address
        *ctrl_port = 0x8500 | (SpriteTable >> 9); // Sprite list address
        *ctrl_port = 0x8600;
        *ctrl_port = 0x8700; // Background color palette index
        *ctrl_port = 0x8800;
        *ctrl_port = 0x8900;
        *ctrl_port = 0x8A01; // Horizontal interrupt timer
        *ctrl_port = 0x8B00 | (VSCROLL_PLANE << 2) | HSCROLL_PLANE; // Scroll mode
        *ctrl_port = 0x8C81; // No interlace or shadow/highlight
        *ctrl_port = 0x8D00 | (HScrollTable >> 10); // HScroll table address
        *ctrl_port = 0x8E00;
        *ctrl_port = 0x8F02; // Auto increment
        *ctrl_port = 0x9001; // Map size (64x32)
        *ctrl_port = 0x9100; // Window X
        *ctrl_port = 0x9200; // Window Y
        // Reset the tile maps
        map_clear(PlaneA);
        hscroll(PlaneA, 0);
        vscroll(PlaneA, 0);
        map_clear(PlaneB);
        hscroll(PlaneB, 0);
        vscroll(PlaneB, 0);
        // (Re)load the font
        color(0, 0x080);
        color(1, 0x000);
        color(15, 0xEEE);
        Text::LoadFont(FONT_TILES);
        // Reset sprites
        SpriteList::Clear();
        SpriteList::Flush();
        // Put blank tile in index 0
        tiles_load(blank_data, 0, 1);
    }

    void vsync() {
        while (*ctrl_port & 8);
        while (!(*ctrl_port & 8));
    }

    // Register stuff

    void set_display(uint8 enabled) {
        *ctrl_port = 0x8134 | (enabled ? 0x40 : 0);
    }

    void set_autoinc(uint8 val) {
        *ctrl_port = 0x8F00 | val;
    }

    void set_scrollmode(uint8 hoz, uint8 vert) {
        *ctrl_port = 0x8B00 | (vert << 2) | hoz;
    }

    void set_highlight(uint8 enabled) {
        *ctrl_port = 0x8C81 | (enabled << 3);
    }

    void set_backcolor(uint8 index) {
        *ctrl_port = 0x8700 | index;
    }

    void set_window(uint8 x, uint8 y) {
        *ctrl_port = 0x9100 | x;
        *ctrl_port = 0x9200 | y;
    }

    // DMA stuff

    static void dma_do(uint32 from, uint16 len, uint32 cmd) {
        // Setup DMA length (in word here)
        *ctrl_port = 0x9300 + (len & 0xff);
        *ctrl_port = 0x9400 + ((len >> 8) & 0xff);
        // Setup DMA address
        from >>= 1;
        *ctrl_port = 0x9500 + (from & 0xff);
        from >>= 8;
        *ctrl_port = 0x9600 + (from & 0xff);
        from >>= 8;
        *ctrl_port = 0x9700 + (from & 0x7f);
        // Enable DMA transfer
        *ctrl_wide = cmd;
    }

    void dma_vram(uint32 from, uint16 to, uint16 len) {
        dma_do(from, len, ((0x4000 + (((uint32) to) & 0x3FFF)) << 16) + ((((uint32) to) >> 14) | 0x80));
    }

    void dma_cram(uint32 from, uint16 to, uint16 len) {
        dma_do(from, len, ((0xC000 + (((uint32) to) & 0x3FFF)) << 16) + ((((uint32) to) >> 14) | 0x80));
    }

    void dma_vsram(uint32 from, uint16 to, uint16 len) {
        dma_do(from, len, ((0x4000 + (((uint32) to) & 0x3FFF)) << 16) + ((((uint32) to) >> 14) | 0x90));
    }

    // Tile patterns

    void tiles_load(volatile const uint16 *data, uint16 index, uint16 num) {
        dma_vram((uint32) data, index << 5, num << 4);
    }

    // Tile maps

    void map_xy(uint16 plan, uint16 tile, uint16 x, uint16 y) {
        uint32 addr = plan + ((x + (y << PlaneWidthSft)) << 1);
        *ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
        *data_port = tile;
    }

    void map_hline(uint16 plan, const uint16 *tiles, uint16 x, uint16 y, uint16 len) {
        dma_vram((uint32) tiles, plan + ((x + (y << PlaneWidthSft)) << 1), len);
    }

    void map_vline(uint16 plan, const uint16 *tiles, uint16 x, uint16 y, uint16 len) {
        set_autoinc(128);
        dma_vram((uint32) tiles, plan + ((x + (y << PlaneWidthSft)) << 1), len);
        set_autoinc(2);
    }

    void map_fill_rect(uint16 plan, uint16 index, uint16 x, uint16 y, uint16 w, uint16 h, uint8 inc) {
        volatile uint16 tiles[64]; // Garbled graphics on -Ofast without this volatile here
        for (uint16 yy = 0; yy < h; yy++) {
            for (uint16 xx = 0; xx < w; xx++) {
                tiles[xx] = index;
                index += inc;
            }
            dma_vram((uint32) tiles, plan + ((x + ((y + yy) << PlaneWidthSft)) << 1), w);
        }
    }

    void map_clear(uint16 plan) {
        uint16 addr = plan;
        while (addr < plan + 0x1000) {
            dma_vram((uint32) blank_data, addr, 0x80);
            addr += 0x100;
        }
    }

    // Palettes

    void colors(uint16 index, const uint16 *values, uint16 count) {
        dma_cram((uint32) values, index << 1, count);
        for (uint16 i = count; i--;) pal_current[index + i] = values[i];
    }

    void color(uint16 index, uint16 color) {
        uint16 ind = index << 1;
        *ctrl_wide = ((0xC000 + (((uint32) ind) & 0x3FFF)) << 16) + ((((uint32) ind) >> 14) | 0x00);
        *data_port = color;
        pal_current[index] = color;
    }

    void colors_next(uint16 index, const uint16 *values, uint16 count) {
        for (uint16 i = count; i--;) pal_next[index + i] = values[i];
    }

    void color_next(uint16 index, uint16 color) {
        pal_next[index] = color;
    }

    uint16 fade_step() {
        if (!pal_fading) return 0;
        if (++pal_fadecnt >= pal_fadespeed) {
            pal_fadecnt = 0;
            uint16 colors_changed = 0;
            for (uint16 i = 64; i--;) {
                uint16 cR = pal_current[i] & 0x00E;
                uint16 nR = pal_next[i] & 0x00E;
                uint16 cG = pal_current[i] & 0x0E0;
                uint16 nG = pal_next[i] & 0x0E0;
                uint16 cB = pal_current[i] & 0xE00;
                uint16 nB = pal_next[i] & 0xE00;
                if (cR != nR) {
                    pal_current[i] += cR < nR ? 0x002 : -0x002;
                    colors_changed++;
                }
                if (cG != nG) {
                    pal_current[i] += cG < nG ? 0x020 : -0x020;
                    colors_changed++;
                }
                if (cB != nB) {
                    pal_current[i] += cB < nB ? 0x200 : -0x200;
                    colors_changed++;
                }
            }
            if (!colors_changed) {
                pal_fading = false;
                return 0;
            }
            dma_cram((uint32) pal_current, 0, 64);
        }
        return 1;
    }

    void fade(const uint16 *src, const uint16 *dst, uint16 speed, uint8 async) {
        if (src) colors(0, src, 64);
        if (dst) colors_next(0, dst, 64);
        pal_fading = true;
        pal_fadespeed = speed;
        pal_fadecnt = 0;
        if (!async) {
            while (fade_step()) {
                vsync();
                //xgm_vblank();
            }
        }
    }

    // Scroll

    void hscroll(uint16 plan, int16 hscroll) {
        uint32 addr = (plan == PlaneA) ? HScrollTable : HScrollTable + 2;
        *ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
        *data_port = hscroll;
    }

    void hscroll_tile(uint16 plan, int16 *hscroll) {
        set_autoinc(32);
        dma_vram((uint32) hscroll, HScrollTable + (plan == PlaneA ? 0 : 2), 32);
        set_autoinc(2);
    }

    void vscroll(uint16 plan, int16 vscroll) {
        uint32 addr = (plan == PlaneA) ? 0 : 2;
        *ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x10);
        *data_port = vscroll;
    }

}
