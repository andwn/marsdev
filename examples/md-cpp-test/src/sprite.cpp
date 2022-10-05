#include "sprite.hpp"
#include "vdp.hpp"

int16 Sprite::X() const {
    return x - 0x80;
}
int16 Sprite::Y() const {
    return y - 0x80;
}
uint16 Sprite::Attributes() const {
    return attr;
}

void Sprite::SetPosition(int16 _x, int16 _y) {
    x = _x + 0x80;
    y = _y + 0x80;
}
void Sprite::SetX(int16 val) {
    x = val + 0x80;
}
void Sprite::SetY(int16 val) {
    y = val + 0x80;
}
void Sprite::SetSize(uint8 w, uint8 h) {
    size = ((w-1)<<2) | (h-1);
}
void Sprite::SetLink(uint8 val) {
    link = val;
}
void Sprite::SetTileAttributes(uint16 val) {
    attr = val;
}


uint16 SpriteList::length;
Sprite SpriteList::sprites[80];

void SpriteList::Add(const Sprite *spr) {
    // Exceeded max number of sprites
    if(length >= 80) return;
    // Prevent drawing off-screen sprites
    if((unsigned)(spr->X()+32) < 320+32 && (unsigned)(spr->Y()+32) < 224+32) {
        sprites[length] = *spr;
        sprites[length].SetLink(length + 1);
        length++;
    }
}
void SpriteList::Add(const Sprite *spr, uint16 num) {
    for(uint16 i = num; i--;) Add(&spr[i]);
}
void SpriteList::Clear() {
    static const Sprite NULL_SPRITE = Sprite();
    length = 0;
    Add(&NULL_SPRITE);
}
void SpriteList::Flush() {
    if(!length) return;
    sprites[length - 1].SetLink(0); // Mark end of sprite list
    vdp::dma_vram((uint32) sprites, vdp::SpriteTable, length << 2);
    length = 0;
}
