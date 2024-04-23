* SEGA 32X support code for the 68000
* by Chilly Willy

		.text

* Initial exception vectors. When the console is first turned on, it is
* in MegaDrive mode. All vectors just point to the code to start up the
* Mars adapter. After the adapter is enabled, none of these vectors will
* appear as the adapter uses its own vector table to route exceptions to
* the jump table. 0x3F0 is where the 68000 starts at for the 32X.

        .long   0x01000000,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0
        .long   0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0,0x000003F0

* Standard MegaDrive ROM header at 0x100

        .ascii	"SEGA 32X        "		/* First 4 bytes must be "SEGA" */
		.ascii	"rld (C)2014     "		/* Copyright and date */
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
		
* Mars exception vector jump table at 0x200

        jmp     0x880800.l  /* reset = hot start */
        jsr     0x880806.l  /* EX_BusError */
        jsr     0x880806.l  /* EX_AddrError */
        jsr     0x880806.l  /* EX_IllInstr */
        jsr     0x880806.l  /* EX_DivByZero */
        jsr     0x880806.l  /* EX_CHK */
        jsr     0x880806.l  /* EX_TrapV */
        jsr     0x880806.l  /* EX_Priviledge */
        jsr     0x880806.l  /* EX_Trace */
        jsr     0x880806.l  /* EX_LineA */
        jsr     0x880806.l  /* EX_LineF */
        .space  72          /* reserved */
        jsr     0x880806.l  /* EX_Spurious */
        jsr     0x880806.l  /* EX_Level1 */
        jsr     0x880806.l  /* EX_Level2 */
        jsr     0x880806.l  /* EX_Level3 */
        jmp     0x88080C.l  /* EX_Level4 HBlank */
        jsr     0x880806.l  /* EX_Level5 */
        jmp     0x880812.l  /* EX_Level6 VBlank */
        jsr     0x880806.l  /* EX_Level7 */
        jsr     0x880806.l  /* EX_Trap0 */
        jsr     0x880806.l  /* EX_Trap1 */
        jsr     0x880806.l  /* EX_Trap2 */
        jsr     0x880806.l  /* EX_Trap3 */
        jsr     0x880806.l  /* EX_Trap4 */
        jsr     0x880806.l  /* EX_Trap5 */
        jsr     0x880806.l  /* EX_Trap6 */
        jsr     0x880806.l  /* EX_Trap7 */
        jsr     0x880806.l  /* EX_Trap8 */
        jsr     0x880806.l  /* EX_Trap9 */
        jsr     0x880806.l  /* EX_TrapA */
        jsr     0x880806.l  /* EX_TrapB */
        jsr     0x880806.l  /* EX_TrapC */
        jsr     0x880806.l  /* EX_TrapD */
        jsr     0x880806.l  /* EX_TrapE */
        jsr     0x880806.l  /* EX_TrapF */
        .space  166         /* reserved */
