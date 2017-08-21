#include "stdint.h"
#include "joy.h"
#include "vdp.h"

static volatile uint8_t joyType[2];
static volatile uint16_t joyState[2];

void joy_init() {
    // set the port bits direction
    volatile uint8_t *pb = (volatile uint8_t *)0xA10009;
    *pb = 0x40;
    pb += 2;
    *pb = 0x40;
    pb += 2;
    *pb = 0x40;
    // set the port bits value
    pb = (volatile uint8_t *)0xA10003;
    *pb = 0x40;
    pb += 2;
    *pb = 0x40;
    pb += 2;
    *pb = 0x40;

    vdp_vsync();
    joy_update();
    vdp_vsync();
    joy_update();

    for (uint8_t i=JOY_1; i<2; i++) {
        joyType[i] = JOY_TYPE_PAD6;
        joyState[i] = 0;
    }
    // wait a few vblanks to get valid data
    vdp_vsync();
    joy_update();
    vdp_vsync();
    joy_update();
    vdp_vsync();
    joy_update();
}

uint8_t joy_get_type(uint16_t joy) {
    return joyType[joy];
}

uint16_t joy_get_state(uint16_t joy) {
    return joyState[joy];
}

static uint16_t TH_CONTROL_PHASE(volatile uint8_t *pb) {
    *pb = 0x00; /* TH (select) low */
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    uint16_t val = *pb;

    *pb = 0x40; /* TH (select) high */
    val <<= 8;
    val |= *pb;

    return val;
}

static uint16_t read3Btn(uint16_t port) {
    volatile uint8_t *pb = (volatile uint8_t *)0xA10003 + (port<<1);
    uint16_t val = TH_CONTROL_PHASE(pb);          // -0sa00du-1cbrldu
    val = ((val & 0x3000) >> 6) | (val & 0x003F); // 00000000sacbrldu
    val ^= 0x00FF;                                // 00000000SACBRLDU

    return val | (JOY_TYPE_PAD3 << 12);
}

static uint16_t read6Btn(uint16_t port) {
    volatile uint8_t *pb = (volatile uint8_t *)0xA10003 + (port<<1);
    uint16_t v1 = TH_CONTROL_PHASE(pb);           // -0sa00du-1cbrldu
    uint16_t val = TH_CONTROL_PHASE(pb);          // -0sa00du-1cbrldu
    uint16_t v2 = TH_CONTROL_PHASE(pb);           // -0sa0000-1cbmxyz
    val = TH_CONTROL_PHASE(pb);                   // -0sa1111-1cbrldu

    if ((val & 0x0F00) != 0x0F00) v2 = (JOY_TYPE_PAD3 << 12) | 0x0F00; // 3 button
    else v2 = (JOY_TYPE_PAD6 << 12) | ((v2 & 0x000F) << 8); // 6 button

    val = ((v1 & 0x3000) >> 6) | (v1 & 0x003F);   // 00000000sacbrldu
    val |= v2;                                    // 0001mxyzsacbrldu or 00001111sacbrldu
    val ^= 0x0FFF;                                // 0001MXYZSACBRLDU or 00000000SACBRLDU

    return val;
}

void joy_update() {
	// Joy 1
	joyState[0] = (joyType[0] == JOY_TYPE_PAD6) ? read6Btn(0) : read3Btn(0);
	joyType[0] = joyState[0] >> 12;
	// Joy 2
	joyState[1] = (joyType[1] == JOY_TYPE_PAD6) ? read6Btn(1) : read3Btn(1);
	joyType[1] = joyState[1] >> 12;
}
