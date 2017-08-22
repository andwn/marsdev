#ifndef INC_MAP_H_
#define INC_MAP_H_

#include <genesis.h>

void MAP_loadData(const u8 *data);

void MAP_drawArea(u16 x, u16 y, u16 w, u16 h);

u16 MAP_getWidth();

u16 MAP_getHeight();

u16 MAP_getTile(u16 x, u16 y);

u16 MAP_getUpperTile(u16 x, u16 y);

#endif
