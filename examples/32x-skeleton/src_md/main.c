#include "types.h"

static volatile uint16_t* const vdp_data_port = (uint16_t*) 0xC00000;
static volatile uint16_t* const vdp_ctrl_port = (uint16_t*) 0xC00004;
static volatile uint32_t* const vdp_ctrl_wide = (uint32_t*) 0xC00004;

void vdp_color(uint16_t index, uint16_t color) {
    index <<= 1;
    *vdp_ctrl_wide = ((0xC000 + (((uint32_t)index) & 0x3FFF)) << 16) + ((((uint32_t)index) >> 14) | 0x00);
    *vdp_data_port = color;
}

const uint16_t color_cycle[10] = { 0xEEE, 0xCCC, 0xAAA, 0x888, 0x666, 0444, 0x666, 0x888, 0xAAA, 0xCCC };
uint16_t col = 0;

void md_update() {
    if(++col >= 10) col = 0;
    vdp_color(17, color_cycle[col]);
}
