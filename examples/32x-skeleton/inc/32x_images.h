/*
* 32X functions for drawing images
* 
* author: ammianus
* 3/3/2012
*
*/
#ifndef _32X_IMAGES_H
#define _32X_IMAGES_H

#define MARS_SDRAM_CACHE          (*(volatile unsigned short *)0x06000000)
#define MARS_CACHE_OFFSET         0x20000000

/*
* Loads all colors from region in ROM defined by paletteStart to paletteEnd
* into the CRAM
* @param paletteStart - pointer to starting position of palette data
* @param paletteEnd - pointer to end position of palette data
* @param paletteOffset - offset in the CRAM to start writing the palette data to. Normally is 0.
*/
void loadPalette(const char *paletteStart, const char *paletteEnd, const int paletteOffset);


/*
* Writes the lzss encoded image to the target buffer in memory
* @param imageStart - in: pointer to starting position of image data
* @param imageEnd - in: pointer to end position of image data
* @param targetMem - out: pointer to memory buffer to write uncompressed image data
*/
void loadLzssToRam(const char *imageStart, const char *imageEnd, vu8 *targetMem);


void drawLzssBG2(const char *imageStart, const char *imageEnd, int fbOffset);

/*
* Writes the lzss encoded image to the framebuffer, assuming the image will be fullscreen (320 x 224)
* @param imageStart - pointer to starting position of image data
* @param imageEnd - pointer to end position of image data
*/
void drawLzssBG(const char *imageStart, const char *imageEnd);


/*
* Draws a compressed image to position on MARS framebuffer
* @param spriteStart - pointer to starting position of image data
* @param spriteEnd - pointer to end position of image data
* @param x - x pixel coordinate of top-left corner of the image 
* @param y - y pixel coordinate of top-left corner of the image
* @param xWidth - vertical size of image to be drawn in pixels
* @param yWidth - horizontal size of image to be drawn in pixels 
*/
void drawLzssSprite(char *spriteStart, char *spriteEnd, vu16 x, vu16 y, int xWidth, int yWidth);

/*
* Draws a compressed image to position on MARS framebuffer
* @param spriteStart - pointer to starting position of image data
* @param spriteEnd - pointer to end position of image data
* @param x - x pixel coordinate of top-left corner of the image 
* @param y - y pixel coordinate of top-left corner of the image
* @param xWidth - vertical size of image to be drawn in pixels
* @param yWidth - horizontal size of image to be drawn in pixels
* @param mirror - 0 for normal 1 for flipped along y-axis 
*/
void drawLzssSprite2(char *spriteStart, char *spriteEnd, vu16 x, vu16 y, int xWidth, int yWidth, int mirror);


/*
* Draws an image to position on MARS framebuffer allowing you to flip the image using mirror param.
* 
* @param spriteBuffer - pointer to starting position of image data to read
* @param x - x pixel coordinate of top-left corner of the image 
* @param y - y pixel coordinate of top-left corner of the image
* @param xWidth - vertical size of image to be drawn in pixels - must be actual size, does not resize or trim
* @param yWidth - horizontal size of image to be drawn in pixels
* @param mirror - 0 for normal 1 for flipped along y-axis
* @param screenWrap - 0 for no screenWrap, 1 for screen wrapping  
*/
int drawSprite(const vu8 *spriteBuffer, const int16 x, const int16 y, const int xWidth, const int yWidth, const int mirror,const int screenWrap);

/*
* Draws a background image on MARS framebuffer allowing you to flip the image using mirror param, no transparency
* 
* @param spriteBuffer - pointer to starting position of image data
*
*/
int drawBG(const vu8 *spriteBuffer);

/* 
* Draws blank pixels to rectangle specified by x, y, xWidth and yWidth (height)
*/
void clearArea(vu16 x, vu16 y, int xWidth, int yWidth);


/*
* Draw line table to framebuffer
*/
void drawLineTable(int xOff);


/* 
* Draws pixels to rectangle specified by x, y, xWidth and yWidth (height). Must be on screen.
* xWidth must be sized in multiples of 8 wide (8 pixels, 16 pixels, etc..)
*
*/
void drawFillRect(const int16 x, const int16 y, const int xWidth, const int yWidth, vu8* color);

/* 
* Draws pixels to outline a rectangle specified by x, y, xWidth and yWidth (height). Must be on screen.
* xWidth must be sized in multiples of 8 wide (8 pixels, 16 pixels, etc..)
*
*/
void drawRect(const int16 x, const int16 y, const int xWidth, const int yWidth, vu8* color);
void my_debug_put_char_8(int x, int y, unsigned char ch, vu8* fgColor, vu8* bgColor);
int myScreenPrintData(const char *buff, const int x, const int y, const vu8* fgColor, const vu8* bgColor );
#endif
