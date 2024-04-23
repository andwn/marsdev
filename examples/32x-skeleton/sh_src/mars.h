#ifndef __32X_H__
#define __32X_H__

#include <stddef.h>
#include <stdint.h>

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;

typedef signed char int8;
typedef signed short int int16;
typedef signed long int int32;

typedef signed short int s16;
typedef unsigned short int u16;

typedef volatile unsigned char vuint8;
typedef volatile unsigned short int vuint16;
typedef volatile unsigned long int vuint32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short int vu16;
typedef volatile unsigned long int vu32;

typedef volatile signed char vint8;
typedef volatile signed short int vint16;
typedef volatile signed long int vint32;

#define abs(n) ((n)<0?-(n):(n))

/* Create a 5:5:5 RGB color */
#define COLOR(r,g,b)    (((r)&0x1F)|((g)&0x1F)<<5|((b)&0x1F)<<10)

#define MARS_CRAM           (*(volatile uint16_t *)0x20004200)
#define MARS_FRAMEBUFFER    (*(volatile uint16_t *)0x24000000)
#define MARS_OVERWRITE_IMG  (*(volatile uint16_t *)0x24020000)
#define MARS_SDRAM          (*(volatile uint16_t *)0x26000000)

#define MARS_SYS_INTMSK     (*(volatile uint16_t *)0x20004000)
#define MARS_SYS_DMACTR     (*(volatile uint16_t *)0x20004006)
#define MARS_SYS_DMASAR     (*(volatile uint32_t *)0x20004008)
#define MARS_SYS_DMADAR     (*(volatile uint32_t *)0x2000400C)
#define MARS_SYS_DMALEN     (*(volatile uint16_t *)0x20004010)
#define MARS_SYS_DMAFIFO    (*(volatile uint16_t *)0x20004012)
#define MARS_SYS_VRESI_CLR  (*(volatile uint16_t *)0x20004014)
#define MARS_SYS_VINT_CLR   (*(volatile uint16_t *)0x20004016)
#define MARS_SYS_HINT_CLR   (*(volatile uint16_t *)0x20004018)
#define MARS_SYS_CMDI_CLR   (*(volatile uint16_t *)0x2000401A)
#define MARS_SYS_PWMI_CLR   (*(volatile uint16_t *)0x2000401C)
#define MARS_SYS_COMM0      (*(volatile uint16_t *)0x20004020) /* Master SH2 communication */
#define MARS_SYS_COMM2      (*(volatile uint16_t *)0x20004022)
#define MARS_SYS_COMM4      (*(volatile uint16_t *)0x20004024) /* Slave SH2 communication */
#define MARS_SYS_COMM6      (*(volatile uint16_t *)0x20004026)
#define MARS_SYS_COMM8      (*(volatile uint16_t *)0x20004028) /* controller 1 current value */
#define MARS_SYS_COMM10     (*(volatile uint16_t *)0x2000402A) /* controller 2 current value */
#define MARS_SYS_COMM12     (*(volatile uint32_t *)0x2000402C) /* vcount current value */

#define MARS_PWM_CTRL       (*(volatile uint16_t *)0x20004030) /* sound */
#define MARS_PWM_CYCLE      (*(volatile uint16_t *)0x20004032)
#define MARS_PWM_LEFT       (*(volatile uint16_t *)0x20004034)
#define MARS_PWM_RIGHT      (*(volatile uint16_t *)0x20004036)
#define MARS_PWM_MONO       (*(volatile uint16_t *)0x20004038)

#define MARS_VDP_DISPMODE   (*(volatile uint16_t *)0x20004100)
#define MARS_VDP_FILLEN     (*(volatile uint16_t *)0x20004104)
#define MARS_VDP_FILADR     (*(volatile uint16_t *)0x20004106)
#define MARS_VDP_FILDAT     (*(volatile uint16_t *)0x20004108)
#define MARS_VDP_FBCTL      (*(volatile uint16_t *)0x2000410A)

#define MARS_SH2_ACCESS_VDP 0x8000
#define MARS_68K_ACCESS_VDP 0x0000

#define MARS_PAL_FORMAT     0x0000
#define MARS_NTSC_FORMAT    0x8000

#define MARS_VDP_PRIO_68K   0x0000
#define MARS_VDP_PRIO_32X   0x0080

#define MARS_224_LINES      0x0000
#define MARS_240_LINES      0x0040

#define MARS_VDP_MODE_OFF   0x0000
#define MARS_VDP_MODE_256   0x0001
#define MARS_VDP_MODE_32K   0x0002
#define MARS_VDP_MODE_RLE   0x0003

#define MARS_VDP_VBLK       0x8000
#define MARS_VDP_HBLK       0x4000
#define MARS_VDP_PEN        0x2000
#define MARS_VDP_FEN        0x0002
#define MARS_VDP_FS         0x0001

// Master / Slave SH-2 Communication 
#define MASTER_STATUS_OK 1
#define MASTER_LOCK 4
#define SLAVE_STATUS_OK 2
#define SLAVE_LOCK 8

#define SH2_CCTL_CP         0x10
#define SH2_CCTL_TW         0x08
#define SH2_CCTL_CE         0x01

#define SH2_FRT_TIER        (*(volatile uint8_t *)0xFFFFFE10)
#define SH2_FRT_FTCSR       (*(volatile uint8_t *)0xFFFFFE11)
#define SH2_FRT_FRCH        (*(volatile uint8_t *)0xFFFFFE12)
#define SH2_FRT_FRCL        (*(volatile uint8_t *)0xFFFFFE13)
#define SH2_FRT_OCRH        (*(volatile uint8_t *)0xFFFFFE14)
#define SH2_FRT_OCRL        (*(volatile uint8_t *)0xFFFFFE15)
#define SH2_FRT_TCR         (*(volatile uint8_t *)0xFFFFFE16)
#define SH2_FRT_TOCR        (*(volatile uint8_t *)0xFFFFFE17)
#define SH2_FRT_ICRH        (*(volatile uint8_t *)0xFFFFFE18)
#define SH2_FRT_ICRL        (*(volatile uint8_t *)0xFFFFFE19)

#define SH2_DMA_SAR0        (*(volatile uint32_t *)0xFFFFFF80)
#define SH2_DMA_DAR0        (*(volatile uint32_t *)0xFFFFFF84)
#define SH2_DMA_TCR0        (*(volatile uint32_t *)0xFFFFFF88)
#define SH2_DMA_CHCR0       (*(volatile uint32_t *)0xFFFFFF8C)
#define SH2_DMA_VCR0        (*(volatile uint32_t *)0xFFFFFFA0)
#define SH2_DMA_DRCR0       (*(volatile uint8_t *)0xFFFFFE71)

#define SH2_DMA_SAR1        (*(volatile uint32_t *)0xFFFFFF90)
#define SH2_DMA_DAR1        (*(volatile uint32_t *)0xFFFFFF94)
#define SH2_DMA_TCR1        (*(volatile uint32_t *)0xFFFFFF98)
#define SH2_DMA_CHCR1       (*(volatile uint32_t *)0xFFFFFF9C)
#define SH2_DMA_VCR1        (*(volatile uint32_t *)0xFFFFFFA8)
#define SH2_DMA_DRCR1       (*(volatile uint8_t *)0xFFFFFE72)

#define SH2_DMA_DMAOR       (*(volatile uint32_t *)0xFFFFFFB0)

#define SH2_INT_IPRA        (*(volatile uint16_t *)0xFFFFFEE2)

#define SEGA_CTRL_UP        0x0001
#define SEGA_CTRL_DOWN      0x0002
#define SEGA_CTRL_LEFT      0x0004
#define SEGA_CTRL_RIGHT     0x0008
#define SEGA_CTRL_B         0x0010
#define SEGA_CTRL_C         0x0020
#define SEGA_CTRL_A         0x0040
#define SEGA_CTRL_START     0x0080
#define SEGA_CTRL_Z         0x0100
#define SEGA_CTRL_Y         0x0200
#define SEGA_CTRL_X         0x0400
#define SEGA_CTRL_MODE      0x0800

#define SEGA_CTRL_TYPE      0xF000
#define SEGA_CTRL_THREE     0x0000
#define SEGA_CTRL_SIX       0x1000
#define SEGA_CTRL_NONE      0xF000

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224

#ifdef __cplusplus
extern "C" {
#endif

extern void Hw32xSetFGColor(int s, int r, int g, int b);
extern void Hw32xSetBGColor(int s, int r, int g, int b);
extern void Hw32xInit(int vmode, int lineskip);
extern int Hw32xScreenGetX(void);
extern int Hw32xScreenGetY(void);
extern void Hw32xScreenSetXY(int x, int y);
extern void Hw32xScreenClear(void);
extern void Hw32xDelay(int ticks);
extern void Hw32xScreenFlip(int wait);
extern void Hw32xFlipWait(void);

extern void HwMdReadPad(uint8_t port);
extern void HwMdClearScreen(void);
extern void HwMdSetOffset(unsigned short offset);
extern void HwMdSetNTable(unsigned short word);
extern void HwMdSetVram(unsigned short word);
extern void HwMdPuts(char *str, uint16_t color, int x, int y);
extern void HwMdPutc(char chr, uint16_t color, int x, int y);

extern void fast_memcpy(void *dst, void *src, int len);
extern void fast_wmemcpy(void *dst, void *src, int len);

extern void word_8byte_copy(void *dst, void *src, int count);
extern void word_8byte_copy_bytereverse(short *dst, short *src, int count);

extern int get_stack_pointer(void);

extern void CacheControl(int mode);
extern void CacheClearLine(void* ptr);
extern void ScreenStretch(int src, int width, int height, int interp);

#ifdef __cplusplus
}
#endif

#endif
