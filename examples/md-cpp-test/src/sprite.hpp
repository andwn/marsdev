#ifndef CPPTEST_SPRITE_HPP
#define CPPTEST_SPRITE_HPP

#include "megadrive.hpp"

class Sprite {
private:
    int16 y;
    uint8 size;
    uint8 link;
    uint16 attr;
    int16 x;
public:
    Sprite() = default;
    ~Sprite() = default;

    int16 X() const;
    int16 Y() const;
    uint16 Attributes() const;

    void SetPosition(int16 _x, int16 _y);
    void SetX(int16 val);
    void SetY(int16 val);
    void SetSize(uint8 w, uint8 h);
    void SetLink(uint8 val);
    void SetTileAttributes(uint16 val);
};

// A buffer of sprites to be drawn by the VDP in the next frame
// The intended usage is to refill and push the entire list each frame
class SpriteList {
private:
    static uint16 length;
    static Sprite sprites[80];
public:
    // Add a single sprite to the sprite list
    // Returns immediately if the sprite list is full
    static void Add(const Sprite *spr);
    // Add multiple sprites to the sprite list
    // Will stop if the sprite list is full
    static void Add(const Sprite *spr, uint16 num);
    // Clear all sprites from the sprite list
    // As it is necessary to "erase" the sprite layer, a "null" sprite is left in the first element
    static void Clear();
    // Push sprite list to VDP sprite table and reset length to 0
    // !!DMA ALERT!! Only call this from the vertical interrupt handler
    static void Flush();
};

#endif //CPPTEST_SPRITE_HPP
