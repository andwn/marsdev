/*
 * Start entry point by Human68K XFile.
 *
 * Communication between the kernel and program is done
 * by setting cpu registers as is :
 * a0 : MCB pointer
 * a1 : End of bss segment
 * a2 : Command line pointer
 * a3 : Environ variable pointer
 * a4 : Execution entry point address
 * a5 : Interrupt routine command number (driver only)
 */

    .extern __stack_size
    .extern __heap_size

    .extern __crt1_startup

    .global _start
_start:
        bra	    _start_1
        .ascii  "X68000 LIBC"
        .ascii  "crt0-"
        .ascii  "x"

    .align 2
_start_1:
        move.l	0x30(a0), a5
        move.l	a1, d0
        sub.l	a5, d0
clear_bss:
	    clr.l	(a5)+
	    dbra	d0, clear_bss

        /* Save crt0 arguments */
        move.l	a0, _MCB		/* MCB */
        lea.l	0x100(a0), a5
        move.l	a5, _PSTA		/* TEXT Start */
        move.l	0x34(a0), d0
        move.l	d0, _PEND		/* TEXT End */
        move.l	d0, _DSTA		/* DATA Start */
        move.l	0x30(a0), d0
        move.l	d0, _DEND		/* DATA End */
        move.l	d0, _BSTA		/* BSS Start */
        move.l	a1, _BEND		/* BSS End */

        lea.l	0x10(a0), a5
        move.l	a5, _PSP

        /* Setup environment */
        move.l	a3, _ENV0
        /* Setup command line */
        move.l	a2, _cmdline
        /* Setup stack */
        move.l	a1, _SSTA
        add.l	#__stack_size, a1
        move.l	a1, _SEND

        move.l	a1, sp

        /* Setup heap */
        move.l	a1, _HSTA		/* HEAP Start */
        add.l	#__heap_size, a1
        move.l	a1, _HEND		/* HEAP End */
        move.l	8(a0), _HMAX	/* End block */

        lea.l	16(a0), a5		/* PSP */

        sub.l	a5, a1
        move.l	a1, -(sp)		/* incr */
        move.l	a5, -(sp)		/* ptr */
        dc.w	0xFF4A			/* setblock */

        pea	    (a0)			/* MCB */
        jmp	    __crt1_startup	/* Human initialization */
        /* No return */


    /* Variables */
	.comm	_MCB, 4
	.comm	_PSP, 4

	.comm	_PSTA, 4
	.comm	_PEND, 4
	.comm	_DSTA, 4
	.comm	_DEND, 4
	.comm	_BSTA, 4
	.comm	_BEND, 4
	.comm	_SSTA, 4
	.comm	_SEND, 4
	.comm	_HSTA, 4
	.comm	_HEND, 4
	.comm	_HMAX, 4

	.comm	_ENV0, 4
	.comm	_cmdline, 4
