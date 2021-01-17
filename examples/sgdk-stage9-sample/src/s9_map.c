#include "s9_map.h"

#define S9M_VERSION 1
#define TS_WIDTH	16

#define FLAG_UPPERLAYER	0x01
#define FLAG_PLANA		0x02
#define FLAG_BYTETILES	0x04

// Helper macro to read a word out of a byte array
#define BYTES_TO_WORD(x) (((x)[0] << 8) | ((x)[1]))

u8 upperLayer, usePlanA, byteTiles;
u8 *mapName;
u16 mapWidth, mapHeight;
const u8 *mapTiles;

void SMAP_loadData(const u8 *data) {
	if(BYTES_TO_WORD(&data[0]) != S9M_VERSION) {
		char str[32];
		sprintf(str, "Bad map version %hu", BYTES_TO_WORD(&data[0]));
		SYS_die(str);
	}
	u8 flags = data[2];
	upperLayer = (flags & FLAG_UPPERLAYER) > 0;
	usePlanA = (flags & FLAG_PLANA) > 0;
	byteTiles = (flags & FLAG_BYTETILES) > 0;
	u8 nameLen = data[3];
	// Move past the name
	data = &data[4 + nameLen];
	// Width and height
	mapWidth = BYTES_TO_WORD(&data[0]);
	mapHeight = BYTES_TO_WORD(&data[2]);
	// Set tile pointer to location of tile data
	mapTiles = &data[4];
}

void SMAP_drawArea(u16 x, u16 y, u16 w, u16 h) {
	u16 t, b, xx, yy;
	VDPPlane plan = usePlanA ? BG_A : BG_B;
	for(u8 layer = 0; layer <= upperLayer; layer++) {
		for(u16 by = y; by < y + h; by++) {
			for(u16 bx = x; bx < x + w; bx++) {
				t = (layer ? SMAP_getUpperTile(bx, by) : SMAP_getTile(bx, by)) * 2;
				b = TILE_USERINDEX + (t / TS_WIDTH * TS_WIDTH * 2) + (t % TS_WIDTH);
				xx = (bx * 2) % 64;
				yy = (by * 2) % 32;
				VDP_setTileMapXY(plan, TILE_ATTR_FULL(PAL2,0,0,0,b), 			xx, 	yy);
				VDP_setTileMapXY(plan, TILE_ATTR_FULL(PAL2,0,0,0,b+1), 			xx+1, 	yy);
				VDP_setTileMapXY(plan, TILE_ATTR_FULL(PAL2,0,0,0,b+TS_WIDTH), 	xx, 	yy+1);
				VDP_setTileMapXY(plan, TILE_ATTR_FULL(PAL2,0,0,0,b+TS_WIDTH+1), xx+1, 	yy+1);
			}
		}
		plan = BG_A;
	}
}

u16 SMAP_getWidth() { return mapWidth; }

u16 SMAP_getHeight() { return mapHeight; }

u16 SMAP_getTile(u16 x, u16 y) {
	u16 index = (x % mapWidth) + (y % mapHeight) * mapWidth;
	if(byteTiles) {
		return mapTiles[index];
	} else {
		return BYTES_TO_WORD(&mapTiles[index * 2]);
	}
}

u16 SMAP_getUpperTile(u16 x, u16 y) {
	if(!upperLayer) return 0;
	u16 index = mapWidth * mapHeight + (x % mapWidth) + (y % mapHeight) * mapWidth;
	if(byteTiles) {
		return mapTiles[index];
	} else {
		return BYTES_TO_WORD(&mapTiles[index * 2]);
	}
}
