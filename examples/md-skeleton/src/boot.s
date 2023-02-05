.section .data

/* .globl exposes symbols to the linker, and may be referred to in C code as extern */
        .globl v_err_reg
        .globl v_err_pc
        .globl v_err_addr
        .globl v_err_ext1
        .globl v_err_ext2
        .globl v_err_sr
        .globl v_err_type

/* Used for the crash handler (see error.c and the error handlers below) */
v_err_reg:	ds.l 16
v_err_pc:	ds.l 1
v_err_addr:	ds.l 1
v_err_ext1:	ds.w 1
v_err_ext2: ds.w 1
v_err_sr:	ds.w 1
v_err_type:	ds.b 1

.section .text.keepboot

    .org    0x00000000					/* Forces linker to put us at the beginning */

RomStart:
        dc.l    0x000000				/* Initial stack pointer address */
        dc.l	_start					/* Program start address */
        dc.l    BusError				/* Not thrown on MD */
        dc.l	AddressError			        /* Thrown when a W or L instruction uses an odd address */
        dc.l	IllegalInst				/* Thrown when the CPU encounters an invalid instruction */
        dc.l	ZeroDivide				/* Thrown when DIV receives a 0 on the left hand side */
        dc.l	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        dc.l	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        dc.l	ExtInt, 0				/* External Interrupt */
        dc.l	HBlank, 0				/* Horizontal Blank Interrupt */
        dc.l	VBlank, 0				/* Vertical Blank Interrupt */
    .rept 8
        dc.l	0, 0, 0, 0
    .endr

RomHeader:
        .ascii	"SEGA MEGA DRIVE "		/* First 4 bytes must be "SEGA" */
        .ascii	"GRIND   2019.DEC"		/* Copyright and date */
        .ascii	"Example Project                                 " /* JP Name */
        .ascii	"Example Project                                 " /* EN Name */
        .ascii	"GM CHANGEME-XX"		/* Serial No. */
        dc.w	0
        .ascii	"J               "		/* Controller support */
        dc.l	0x000000				/* ROM Start */
        dc.l	0x3FFFFF				/* ROM End (4MB) */
        dc.l	0xFF0000				/* RAM Start */
        dc.l	0xFFFFFF				/* RAM End (64KB) */
        .ascii	"RA"					/* "RA" to enable SRAM, "  " to disable */
        dc.w	0xF820					/* SRAM writes to odd bytes */
        dc.l	0x200001				/* SRAM Start */
        dc.l	0x20FFFF				/* SRAM End (32KB) */
        .ascii	"            "
        .ascii	"                                        "
        .ascii	"JUE             "		/* Region */

_start:
        move    #0x2700,sr              /* Disable interrupts */
        move.b	(0xA10001),d0           /* Check console version */
        andi.b  #0x0F,d0                /* Version 0 = skip TMSS */
        beq.s   NoTMSS
        move.l  (0x100),0xA14000        /* Write 'SEGA' to TMSS register */
NoTMSS:
        move.w  (0xC00004),d0           /* Read VDP status */
        move.w  #0x0100,(0xA11100)      /* Halt / Reset Z80 */
        move.w  #0x0100,(0xA11200)
    .globl 	_hard_reset
_hard_reset:                            /* SYS_HardReset() resets sp and jumps here */
        lea     0xFF0000,a0             /* First RAM address */
        moveq   #0,d0
        move.w  #0x3FFF,d1              /* (Size of RAM - 1) / Size of long */
ClearRam:
        move.l  d0,(a0)+
        dbra    d1,ClearRam
        lea     _stext,a0               /* Start of initialized data (BSS) in ROM */
        lea     0xFF0000,a1             /* First RAM address */
        move.l  #_sdata,d0              /* (Size of BSS + 1) / 2 */
        addq.l  #1,d0
        lsr.l   #1,d0
        beq     NoCopy
        subq.w  #1,d0                   /* sub extra iteration */
CopyVar:
        move.w  (a0)+,(a1)+             /* Copy initialized data to RAM */
        dbra    d0,CopyVar
NoCopy:
        jsr     main                    /* IT BEGINS */
        beq.s   _hard_reset             /* main returned, reset */

/* Error handling */

BusError:
        move.b #0,(v_err_type)
        bra.s  AddressDump

AddressError:
        move.b #1,(v_err_type)
        bra.s  AddressDump

IllegalInst:
        move.b #2,(v_err_type)
        bra.s  IllegalDump

ZeroDivide:
        move.b #3,(v_err_type)
        bra.s  ZeroDump

AddressDump:
        move.w 4(sp),v_err_ext1
        move.l 6(sp),v_err_addr
        move.w 10(sp),v_err_ext2
        move.w 12(sp),v_err_sr
        move.l 14(sp),v_err_pc
        bra.s  RegDump
IllegalDump:
        move.w 10(sp),v_err_ext1
ZeroDump:
        move.w 4(sp),v_err_sr
        move.l 6(sp),v_err_pc
RegDump:
        move.l d0,v_err_reg+0
        move.l d1,v_err_reg+4
        move.l d2,v_err_reg+8
        move.l d3,v_err_reg+12
        move.l d4,v_err_reg+16
        move.l d5,v_err_reg+20
        move.l d6,v_err_reg+24
        move.l d7,v_err_reg+28
        move.l a0,v_err_reg+32
        move.l a1,v_err_reg+36
        move.l a2,v_err_reg+40
        move.l a3,v_err_reg+44
        move.l a4,v_err_reg+48
        move.l a5,v_err_reg+52
        move.l a6,v_err_reg+56
        move.l a7,v_err_reg+60
        jmp    _error

/* Standard interrupts */

ExtInt:
        rte
		
HBlank:
        rte

VBlank:
        rte
