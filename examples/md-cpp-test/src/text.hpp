#ifndef CPPTEST_TEXT_HPP
#define CPPTEST_TEXT_HPP

#include "megadrive.hpp"

class Text {
private:
    static uint16 font_plane;
    static uint16 font_palette;
public:
    static void LoadFont(const uint16 *tiles);
    static void SetFontPalette(uint16 pal);
    static void SetFontPlane(uint16 plane);

    static void puts(const char *str, uint16 x, uint16 y);
    static void clear(uint16 x, uint16 y, uint16 len);
};

#endif //CPPTEST_TEXT_HPP
