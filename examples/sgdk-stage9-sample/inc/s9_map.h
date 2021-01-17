#ifndef INC_MAP_H_
#define INC_MAP_H_

#include <genesis.h>

void SMAP_loadData(const u8 *data);

void SMAP_drawArea(u16 x, u16 y, u16 w, u16 h);

u16 SMAP_getWidth();

u16 SMAP_getHeight();

u16 SMAP_getTile(u16 x, u16 y);

u16 SMAP_getUpperTile(u16 x, u16 y);

#endif
