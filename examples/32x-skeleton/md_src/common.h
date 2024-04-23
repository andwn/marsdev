/* Constants */

#define Z80_RAM			0xA00000	/* Where Z80 RAM starts */
#define Z80_BUS_REQ		0xA11100	/* Z80 bus request line */
#define Z80_RESET		0xA11200	/* Z80 reset line */

#define IO_BASE			0xA10000
#define IO_CTRL1		(IO_BASE+9)		/* 1P control port */
#define IO_CTRL2		(IO_BASE+11)	/* 2P control port */
#define IO_DATA1		(IO_BASE+3)		/* 1P data port */
#define IO_DATA2		(IO_BASE+5)		/* 2P data port */

#define VDP_DATA_PORT	0xC00000
#define VDP_CTRL_PORT	0xC00004
#define VDP_COUNTER		0xC00008

#define VRAM_ADDR_CMD	0x40000000
#define CRAM_ADDR_CMD	0xC0000000
#define VSRAM_ADDR_CMD	0x40000010
#define VRAM_DMA_CMD	0x40000080
#define CRAM_DMA_CMD	0xC0000080
#define VSRAM_DMA_CMD	0x40000090

/* Variables */

#define MARS_COMM0		0xA15120
#define MARS_COMM2		0xA15122
#define MARS_COMM4		0xA15124
#define MARS_COMM6		0xA15126
#define MARS_COMM8		0xA15128
#define MARS_COMM10		0xA1512A
#define MARS_COMM12		0xA1512C
#define MARS_COMM14		0xA1512E

#define JoypadState		MARS_COMM8
#define VBlankCounter	MARS_COMM12

/* Macros */
#ifdef __ASSEMBLER__

#define DISABLE_INTS	move #0x2700,sr
#define ENABLE_VINT		move #0x2500,sr
#define ENABLE_INTS		move #0x2300,sr

#define PAUSE_Z80		move.w #0x100,(Z80_BUS_REQ)
#define RESUME_Z80		move.w #0x000,(Z80_BUS_REQ)

#else

#include <stddef.h>
#include <stdint.h>

#define DISABLE_INTS	__asm__("move #0x2700,sr")
#define ENABLE_VINT		__asm__("move #0x2500,sr")
#define ENABLE_INTS		__asm__("move #0x2300,sr")

#define PAUSE_Z80		__asm__("move.w #0x100,(Z80_BUS_REQ)")
#define RESUME_Z80		__asm__("move.w #0x000,(Z80_BUS_REQ)")

#endif
