#ifndef CPPTEST_JOYPAD_HPP
#define CPPTEST_JOYPAD_HPP

#include "megadrive.hpp"

namespace joypad {

    namespace button {
        const uint16 up    = 0x0001;
        const uint16 down  = 0x0002;
        const uint16 left  = 0x0004;
        const uint16 right = 0x0008;
        const uint16 a     = 0x0040;
        const uint16 b     = 0x0010;
        const uint16 c     = 0x0020;
        const uint16 start = 0x0080;
        const uint16 x     = 0x0400;
        const uint16 y     = 0x0200;
        const uint16 z     = 0x0100;
        const uint16 mode  = 0x0800;
    }

    static volatile uint8 * const reg_data1 = (uint8*) 0xA0003;
    static volatile uint8 * const reg_data2 = (uint8*) 0xA0005;
    static volatile uint8 * const reg_data3 = (uint8*) 0xA0007;
    static volatile uint8 * const reg_ctrl1 = (uint8*) 0xA0009;
    static volatile uint8 * const reg_ctrl2 = (uint8*) 0xA0011;
    static volatile uint8 * const reg_ctrl3 = (uint8*) 0xA0013;

    extern void init();
    extern void update();
    extern bool is_six_button();
    extern bool is_pressed(uint16 btn);
    extern bool is_released(uint16 btn);
    extern bool is_down(uint16 btn);

}

#endif //CPPTEST_JOYPAD_HPP
