#include "text.hpp"
#include "vdp.hpp"

uint16 Text::font_plane;
uint16 Text::font_palette;

void Text::LoadFont(const uint16 *tiles) {
    font_plane = vdp::PlaneA;
    font_palette = vdp::PAL0;
    // ASCII 32-127
    vdp::tiles_load(tiles, TILE_FONT_INDEX, 0x60);
}
void Text::SetFontPalette(uint16 pal) {
    font_palette = pal;
}
void Text::SetFontPlane(uint16 plane) {
    font_plane = plane;
}

void Text::puts(const char *str, uint16 x, uint16 y) {
    uint32 addr = font_plane + ((x + (y << vdp::PlaneWidthSft)) << 1);
    *vdp::ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
    for(uint16 i = 0; i < 64 && *str; ++i) {
        // Wrap around the plane, don't fall to next line
        if (i + x == 64) {
            addr -= x << 1;
            *vdp::ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
        }
        uint16 c = TILE_FONT_INDEX + *str++ - 0x20;
        *vdp::data_port = vdp::PRI | font_palette | c;
    }
}
void Text::clear(uint16 x, uint16 y, uint16 len) {
    uint32 addr = font_plane + ((x + (y << vdp::PlaneWidthSft)) << 1);
    *vdp::ctrl_wide = ((0x4000 + ((addr) & 0x3FFF)) << 16) + (((addr) >> 14) | 0x00);
    while(len--) *vdp::data_port = 0;
}
