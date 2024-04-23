#include "types.h"

typedef void (*func)();

#define enable_ints __asm__("move #0x2000,%sr")
#define disable_ints __asm__("move #0x2700,%sr")

// External routines

extern void __m68k_start();
extern void __wait_vblank();

// 32X COMM

static volatile uint16_t* const mars_comm0 = (uint16_t*) 0xA15120;

// VDP

static volatile uint16_t* const vdp_data_port = (uint16_t*) 0xC00000;
static volatile uint16_t* const vdp_ctrl_port = (uint16_t*) 0xC00004;
static volatile uint32_t* const vdp_ctrl_wide = (uint32_t*) 0xC00004;

void vdp_color(uint16_t index, uint16_t color) {
    index <<= 1;
    *vdp_ctrl_wide = ((0xC000 + (((uint32_t)index) & 0x3FFF)) << 16) + (((uint32_t)index) >> 14);
    *vdp_data_port = color;
}

const uint16_t color_cycle[10] = { 0xEEE, 0xCCC, 0xAAA, 0x888, 0x666, 0x444, 0x666, 0x888, 0xAAA, 0xCCC };

void main() {
    // Boot code copies routines (starting at __m68k_start) into memory at address 0xFF1000
    // We want to call the wait_vblank function from in here, so some math to find where it is in RAM
    func wait_vblank = (func)(0xFF1000 + __wait_vblank - __m68k_start);

    uint16_t ticks = 0, col = 0;
    while(1) {
        if(++ticks >= 8) {
            ticks = 0;
            if(++col >= 10) col = 0;
        }
        //disable_ints;
        vdp_color(17, color_cycle[col]);
        //enable_ints;
        wait_vblank();
    }
}
