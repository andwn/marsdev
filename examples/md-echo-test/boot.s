.section .data

	.globl vblank
crash_pc:	ds.l 1
vblank:		ds.b 1

.section .text.keepboot

	.globl Reset
    .org    0x00000000
RomStart:
        dc.l    0x00000000
        dc.l    CodeEntry
        dc.l    CRASH
        dc.l    AddressError, IllegalInst, ZeroDivide
        dc.l    CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
        dc.l	CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
        dc.l	CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
        dc.l    VerticalInt
        dc.l    CRASH
        dc.l    CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
        dc.l    CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
        dc.l    CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
        dc.l    CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH, CRASH
RomHead:
		.ascii 	"SEGA MEGA DRIVE "
		.ascii 	"SAMPLE  2017.AUG"
		.ascii 	"Skel                                            "
		.ascii 	"Skel                                            "
		.ascii 	"GM ANDYG007-00"
		dc.w 	0
		.ascii 	"J               "
		dc.l 	RomStart
		dc.l 	0x3FFFFF
		dc.l 	0xFF0000
		dc.l 	0xFFFFFF
		.ascii 	"RA"
		dc.w 	0xF820
		dc.l 	0x200001
		dc.l 	0x20FFFF
		.ascii 	"                                                    "
		.ascii 	"JUE             "

CRASH:
	nop
	bra.s CRASH

CodeEntry:
        move    #0x2700,sr
        tst.l   0xA10008
        bne.s   SkipJoyDetect
        tst.w   0xA1000C
SkipJoyDetect:
        move.b  (0xA10001),d0
        andi.b  #0x0f,d0
        beq.s   NoTMSS
        move.l  #0x53454741,(0xA14000)
NoTMSS:
        move.w  (0xC00004),d0
        moveq   #0x00,d0
        movea.l d0,a6
        move    a6,usp
        move.w  0x0100,(0xA11100)
        move.w  0x0100,(0xA11200)
Reset:
        lea     _stext,a0
        lea     0xFF0000,a1
        move.l  #_sdata,d0
        lsr.l   #1,d0
        subq.w  #1,d0
CopyVar:
        move.w  (a0)+,(a1)+
        dbra    d0,CopyVar
        jmp     _main

* TODO: Actually write a crash handler
AddressError:
		move.l 14(sp),crash_pc
AE_LOOP:
		nop
        bra.s AE_LOOP

IllegalInst:
		move.l 6(sp),crash_pc
II_LOOP:
		nop
        bra.s II_LOOP

ZeroDivide:
		move.l 6(sp),crash_pc
ZD_LOOP:
		nop
        bra.s ZD_LOOP

VerticalInt:
        clr.b	(vblank)
        rte
