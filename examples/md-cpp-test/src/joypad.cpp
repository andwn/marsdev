#include "joypad.hpp"

namespace joypad {

    bool six_button;
    uint16 pad_state;
    uint16 old_state;

    void init() {
        pad_state = old_state = 0;
        /* set the port bits direction */
        *reg_ctrl1 = 0x40;
        *reg_ctrl2 = 0x40;
        *reg_ctrl3 = 0x40;
        /* set the port bits value */
        *reg_data1 = 0x40;
        *reg_data2 = 0x40;
        *reg_data3 = 0x40;
    }

    void update() {
        volatile uint16 v[4];
        for (uint16 i = 0; i < 4; i++) {
            *reg_data1 = 0x00; /* TH (select) low */
            v[i] = v[i] << 8;     /* Wait a few cycles */
            v[i] = *reg_data1;
            *reg_data1 = 0x40; /* TH (select) high */
            v[i] = v[i] << 8;
            v[i] = v[i] | *reg_data1;
        }
        if ((v[3] & 0x0F00) != 0x0F00) {
            six_button = false;
            v[2] = 0x0F00;
        } else {
            six_button = true;
            v[2] = (v[2] & 0x000F) << 8;
        }
        old_state = pad_state;
        pad_state = ((v[0] & 0x3000) >> 6) | (v[0] & 0x003F);
        pad_state |= v[2];
        pad_state ^= 0x0FFF;
    }

    bool is_six_button() {
        return six_button;
    }

    bool is_pressed(uint16 btn) {
        return (pad_state & btn) && ((~old_state) & btn);
    }

    bool is_released(uint16 btn) {
        return ((~pad_state) & btn) && (old_state & btn);
    }

    bool is_down(uint16 btn) {
        return pad_state & btn;
    }
}
