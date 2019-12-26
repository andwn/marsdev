#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "types.h"
#include "32x.h"

/*
* For a given details value 0 - 63 returns the equivalent
* of sin((d/10)). Precalculated.
*/
double xSinTable(const int details);

/*
* For a given details value 0 - 63 returns the equivalent
* of sin((d/10)+(pi/2)). Precalculated.
*/
double ySinTable(const int details);

/*
* Draws an elipse
*/
void circle2(const int16 height, const int16 width, const int16 rx,const int16 ry,const int16 r,vu8 *spriteBuffer, int16 colorIndex);

#endif
