.macro FUNC _name, _align=2
    .globl \_name
    .type  \_name, @function
    .align \_align
\_name:
.endm


# __dead void _iocs_abortjob (void);
FUNC _iocs_abortjob
		moveq	#0xffffffff, d0
		trap	#15
		
# void _iocs_abortrst (void);
FUNC _iocs_abortrst
		moveq	#0xfffffffd, d0
		trap	#15
		rts

# void _iocs_adpcmain (const struct _iocs_chain *, int, int);
FUNC _iocs_adpcmain
		move.l	d2, -(sp)
		movem.l	8(sp), d0-d2
		move.l	d0, a1
		moveq	#0x63, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_adpcmaot (const struct _iocs_chain *, int, int);
FUNC _iocs_adpcmaot
		move.l	d2, -(sp)
		movem.l	8(sp), d0-d2
		move.l	d0, a1
		moveq	#0x62, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_adpcminp (void *, int, int);
FUNC _iocs_adpcminp
		move.l	d2, -(sp)
		movem.l	8(sp), d0-d2
		move.l	d0, a1
		moveq	#0x61, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_adpcmlin (const struct _iocs_chain2 *, int);
FUNC _iocs_adpcmlin
		movea.l	4(sp), a1
		move.l	8(sp) , d1
		moveq	#0x65, d0
		trap	#15
		rts

# void _iocs_adpcmlot (const struct _iocs_chain2 *, int);
FUNC _iocs_adpcmlot
		movea.l	4(sp), a1
		move.l	8(sp) , d1
		moveq	#0x64, d0
		trap	#15
		rts

# void _iocs_adpcmmod (int);
FUNC _iocs_adpcmmod
		move.l	4(sp), d1
		moveq	#0x67, d0
		trap	#15
		rts

# void _iocs_adpcmout (const void *, int, int);
FUNC _iocs_adpcmout
		move.l	d2, -(sp)
		movem.l	8(sp), d0-d2
		move.l	d0, a1
		moveq	#0x60, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_adpcmsns (void);
FUNC _iocs_adpcmsns
		moveq	#0x66, d0
		trap	#15
		rts

# int __pure _iocs_akconv (int, int) __attribute__((const));
FUNC _iocs_akconv
		move.w	6(sp), d1
		swap	d1
		move.w	10(sp), d1
		moveq	#0xffffffa2, d0
		trap	#15
		rts

# int _iocs_alarmget (int *, int *, int *);
FUNC _iocs_alarmget
		move.l	d2, -(sp)
		moveq	#0x5f, d0
		trap	#15
		movem.l	8(sp), a0/a1
		move.l	d1, (a0)
		move.l	d2, (a1)
		movea.l	16(sp), a0
		move.l	d0, (a0)
		move.l	(sp)+, d2
		rts

# int _iocs_alarmmod (int);
FUNC _iocs_alarmmod
		move.l	4(sp), d1
		moveq	#0x5d, d0
		trap	#15
		rts

# int _iocs_alarmset (int, int, int);
FUNC _iocs_alarmset
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2/a1
		moveq	#0x5e, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_apage (int);
FUNC _iocs_apage
		move.l	4(sp), d1
		moveq	#0xffffffb1, d0
		trap	#15
		rts

# int _iocs_b_assign (int, int, int, const void *);
FUNC _iocs_b_assign
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x48, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_badfmt (int, int, int);
FUNC _iocs_b_badfmt
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0x4b, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_bpeek (const void *);
FUNC _iocs_b_bpeek
		move.l	4(sp), a1
		moveq	#0xffffff82, d0
		trap	#15
		rts

# void _iocs_b_bpoke (void *, int);
FUNC _iocs_b_bpoke
		movea.l	4(sp), a1
		move.l	8(sp) , d1
		moveq	#0xffffff86, d0
		trap	#15
		rts

# void _iocs_b_clr_al (void);
FUNC _iocs_b_clr_al
		moveq	#2, d1
		moveq	#0x2a, d0
		trap	#15
		rts

# void _iocs_b_clr_ed (void);
FUNC _iocs_b_clr_ed
		moveq	#0, d1
		moveq	#0x2a, d0
		trap	#15
		rts

# void _iocs_b_clr_st (void);
FUNC _iocs_b_clr_st
		moveq	#1, d1
		moveq	#0x2a, d0
		trap	#15
		rts

# int _iocs_b_color (int);
FUNC _iocs_b_color
		move.l	4(sp), d1
		moveq	#0x22, d0
		trap	#15
		rts

# int _iocs_b_consol (int, int, int, int);
FUNC _iocs_b_consol
		move.l	d2, -(sp)
		movem.l	8(sp), d1-d2
		swap	d1
		move.w	d2, d1
		move.w	18(sp), d2
		swap	d2
		move.w	22(sp), d2
		moveq	#0x2e, d0
		trap	#15
		move.l	d2, d0
		move.l	(sp)+, d2
		rts

# void _iocs_b_curdef (void *); /*1.3/iocs.x*/
FUNC _iocs_b_curdef
		move.l	d2, -(sp)
		move.l	8(sp), d2
		moveq	#3, d1
		moveq	#0xffffffad, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_b_curmod (int); /*1.3/iocs.x*/
FUNC _iocs_b_curmod
		move.l	4(sp), d1
		moveq	#1, d0
		cmp.l	d1, d0
		bcss	6f
		moveq	#0xffffffad, d0
		trap	#15
6:
		rts

# void _iocs_b_curoff (void);
FUNC _iocs_b_curoff
		moveq	#0x1f, d0
		trap	#15
		rts

# void _iocs_b_curon (void);
FUNC _iocs_b_curon
		moveq	#0x1e, d0
		trap	#15
		rts

# void _iocs_b_curpat1 (void); /*1.3/iocs.x*/
FUNC _iocs_b_curpat1
		move.l	d2, -(sp)
		moveq	#2, d1
		moveq	#0, d2
		moveq	#0xffffffad, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_b_curpat (int); /*1.3/iocs.x*/
FUNC _iocs_b_curpat
		move.l	d2, -(sp)
		move.l	8(sp), d2
		tst.w	d2
		beqs	6f
		moveq	#2, d1
		moveq	#0xffffffad, d0
		trap	#15
6:
		move.l	(sp)+, d2
		rts

# void _iocs_b_del (int);
FUNC _iocs_b_del
		move.l	4(sp), d1
		moveq	#0x2d, d0
		trap	#15
		rts

# void _iocs_b_down (int);
FUNC _iocs_b_down
		move.l	4(sp), d1
		moveq	#0x27, d0
		trap	#15
		rts

# void _iocs_b_down_s (void);
FUNC _iocs_b_down_s
		moveq	#0x24, d0
		trap	#15
		rts

# int _iocs_b_drvchk (int, int);
FUNC _iocs_b_drvchk
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x4e, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_b_drvsns (int);
FUNC _iocs_b_drvsns
		move.l	4(sp), d1
		moveq	#0x44, d0
		trap	#15
		rts

# int _iocs_b_dskini (int, const void *, int);
FUNC _iocs_b_dskini
		move.l	d2, -(sp)
		movem.l	8(sp), d1-d2/a1
		exg	d2, a1
		moveq	#0x43, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_b_eject (int);
FUNC _iocs_b_eject
		move.l	4(sp), d1
		moveq	#0x4f, d0
		trap	#15
		rts

# void _iocs_b_era_al (void);
FUNC _iocs_b_era_al
		moveq	#2, d1
		moveq	#0x2b, d0
		trap	#15
		rts

# void _iocs_b_era_ed (void);
FUNC _iocs_b_era_ed
		moveq	#0, d1
		moveq	#0x2b, d0
		trap	#15
		rts

# void _iocs_b_era_st (void);
FUNC _iocs_b_era_st
		moveq	#1, d1
		moveq	#0x2b, d0
		trap	#15
		rts

# int _iocs_b_format (int, int, int, const void *);
FUNC _iocs_b_format
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x4d, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_bgctrlgt (int);
FUNC _iocs_bgctrlgt
		move.l	4(sp), d1
		moveq	#0xffffffcb, d0
		trap	#15
		rts

# int _iocs_bgctrlst (int, int, int);
FUNC _iocs_bgctrlst
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0xffffffca, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_bgscrlgt (int, int *, int *);
FUNC _iocs_bgscrlgt
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		move.l	12(sp), d1
		moveq	#0xffffffc9, d0
		trap	#15
		tst.l	d0
		bnes	6f
		movem.l	16(sp), a0/a1
		move.l	d2, (a0)
		move.l	d3, (a1)
6:
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_bgscrlst (int, int, int);
FUNC _iocs_bgscrlst
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0xffffffc8, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_bgtextcl (int, int);
FUNC _iocs_bgtextcl
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0xffffffcc, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_bgtextgt (int, int, int);
FUNC _iocs_bgtextgt
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0xffffffce, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_bgtextst (int, int, int, int);
FUNC _iocs_bgtextst
		movem.l	d2/d3/d4, -(sp)
		movem.l	16(sp),d1/d2/d3/d4
		moveq	#0xffffffcd, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4
		rts

# int _iocs_bindatebcd (int);
FUNC _iocs_bindatebcd
		move.l	4(sp), d1
		moveq	#0x50, d0
		trap	#15
		rts

# int _iocs_bindateget (void);
FUNC _iocs_bindateget
		moveq	#0x54, d0
		trap	#15
		rts

# void _iocs_bindateset (int);
FUNC _iocs_bindateset
		move.l	4(sp), d1
		moveq	#0x51, d0
		trap	#15
		rts

# void _iocs_b_ins (int);
FUNC _iocs_b_ins
		move.l	4(sp), d1
		moveq	#0x2c, d0
		trap	#15
		rts

# int _iocs_b_intvcs (int, int);
FUNC _iocs_b_intvcs
		movem.l	4(sp),d1/a1
		moveq	#0xffffff80, d0
		trap	#15
		rts

# int _iocs_bitsns (int);
FUNC _iocs_bitsns
		move.l	4(sp), d1
		moveq	#0x04, d0
		trap	#15
		rts

# int _iocs_b_keyinp (void);
FUNC _iocs_b_keyinp
		moveq	#0x00, d0
		trap	#15
		rts

# int _iocs_b_keysns (void);
FUNC _iocs_b_keysns
		moveq	#0x01, d0
		trap	#15
		rts

# void _iocs_b_left (int);
FUNC _iocs_b_left
		move.l	4(sp), d1
		moveq	#0x29, d0
		trap	#15
		rts

# int _iocs_b_locate (int, int);
FUNC _iocs_b_locate
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x23, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_b_lpeek (const void *);
FUNC _iocs_b_lpeek
		move.l	4(sp), a1
		moveq	#0xffffff84, d0
		trap	#15
		rts

# void _iocs_b_lpoke (void *, int);
FUNC _iocs_b_lpoke
		movea.l	4(sp), a1
		move.l	8(sp) , d1
		moveq	#0xffffff88, d0
		trap	#15
		rts

# void _iocs_b_memset (void *, const void *, int);
FUNC _iocs_b_memset
		move.l	a2, -(sp)
		movem.l	8(sp), a1/a2
		move.l	16(sp), d1
		moveq	#0xffffff89, d0
		trap	#15
		move.l	(sp)+, a2
		rts

# void _iocs_b_memstr (const void *, void *, int);
FUNC _iocs_b_memstr
		move.l	a2, -(sp)
		movem.l	8(sp), a1/a2
		move.l	16(sp), d1
		moveq	#0xffffff85, d0
		trap	#15
		move.l	(sp)+, a2
		rts

# int __pure _iocs_bootinf (void) __attribute__((const));
FUNC _iocs_bootinf
		moveq	#0xffffff8e, d0
		trap	#15
		rts

# int _iocs_box (const struct _iocs_boxptr *);
FUNC _iocs_box
		move.l	4(sp), a1
		moveq	#0xffffffb9, d0
		trap	#15
		rts

# int _iocs_b_print (const char *);
FUNC _iocs_b_print
		move.l	4(sp), a1
		moveq	#0x21, d0
		trap	#15
		rts

# int _iocs_b_putc (int);
FUNC _iocs_b_putc
		move.l	4(sp), d1
		moveq	#0x20, d0
		trap	#15
		rts

# int _iocs_b_putmes (int, int, int, int, const char *);
FUNC _iocs_b_putmes
		movem.l	d2/d3/d4, -(sp)
		movem.l	16(sp),d1/d2/d3/d4/a1
		moveq	#0x2f, d0
		trap	#15
		move.l	d2, d0
		movem.l	(sp)+,d2/d3/d4
		rts

# int _iocs_b_readdi (int, int, int, void *);
FUNC _iocs_b_readdi
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x42, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_readdl (int, int, int, void *);
FUNC _iocs_b_readdl
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x4c, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_readid (int, int, void *);
FUNC _iocs_b_readid
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x4a, d0
		trap	#15
		movea.l	16(sp), a0
		move.l	d2, (a0)
		move.l	(sp)+, d2
		rts

# int _iocs_b_read (int, int, int, void *);
FUNC _iocs_b_read
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x46, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_recali (int);
FUNC _iocs_b_recali
		move.l	4(sp), d1
		moveq	#0x47, d0
		trap	#15
		rts

# void _iocs_b_right (int);
FUNC _iocs_b_right
		move.l	4(sp), d1
		moveq	#0x28, d0
		trap	#15
		rts

# void _iocs_b_scroll (int); /*1.3/iocs.x*/
FUNC _iocs_b_scroll
		move.l	d2, -(sp)
		move.l	8(sp), d2
		moveq	#16, d1
		cmp.l	d1, d2
		bcss	lscriocs
		move.l	d2, d1
lscriocs:
		moveq	#0xffffffad, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_b_seek (int, int);
FUNC _iocs_b_seek
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x40, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_b_sftsns (void);
FUNC _iocs_b_sftsns
		moveq	#0x02, d0
		trap	#15
		rts

# int _iocs_b_super (int);
FUNC _iocs_b_super
		movea.l	(sp)+, a0
		movea.l	(sp), a1
		moveq	#0xffffff81, d0
		trap	#15
		jmp	    (a0)

# void _iocs_b_up (int);
FUNC _iocs_b_up
		move.l	4(sp), d1
		moveq	#0x26, d0
		trap	#15
		rts

# void _iocs_b_up_s (void);
FUNC _iocs_b_up_s
		moveq	#0x25, d0
		trap	#15
		rts

# int _iocs_b_verify (int, int, int, const void *);
FUNC _iocs_b_verify
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x41, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_wpeek (const void *);
FUNC _iocs_b_wpeek
		move.l	4(sp), a1
		moveq	#0xffffff83, d0
		trap	#15
		rts

# void _iocs_b_wpoke (void *, int);
FUNC _iocs_b_wpoke
		movea.l	4(sp), a1
		move.l	8(sp) , d1
		moveq	#0xffffff87, d0
		trap	#15
		rts

# int _iocs_b_writed (int, int, int, const void *);
FUNC _iocs_b_writed
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x49, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_b_write (int, int, int, const void *);
FUNC _iocs_b_write
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3/a1
		moveq	#0x45, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_cache_md (int); /* rom 1.3 only */
FUNC _iocs_cache_md
		move.l	d2, -(sp)
		move.l	8(sp), d2
		moveq	#3, d1
		move.l	d2, d0
		addq.l	#1, d0
		beqs	lcachemd
		moveq	#2, d1
		addq.l	#1, d0
		bnes	lcachemd
		moveq	#4, d1
lcachemd:
		moveq	#0xffffffac, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_cache_st (void); /* rom 1.3 only */
FUNC _iocs_cache_st
		moveq	#1, d1
		moveq	#0xffffffac, d0
		trap	#15
		rts

# int _iocs_circle (const struct _iocs_circleptr *);
FUNC _iocs_circle
		move.l	4(sp), a1
		moveq	#0xffffffbb, d0
		trap	#15
		rts

# void _iocs_clipput (int, int, const struct _iocs_fntbuf *, const struct _iocs_clipxy *);
FUNC _iocs_clipput
		move.l	d2, -(sp)
		move.l	a2, -(sp)
		movem.l	12(sp),d1/d2/a1/a2
		moveq	#0x1c, d0
		trap	#15
		move.l	(sp)+, a2
		move.l	(sp)+, d2
		rts

# int _iocs_contrast (int);
FUNC _iocs_contrast
		move.l	4(sp), d1
		moveq	#0x11, d0
		trap	#15
		rts

# int _iocs_crtcras (const void *, int);
FUNC _iocs_crtcras
		movea.l	4(sp), a1
		move.l	8(sp) , d1
		moveq	#0x6d, d0
		trap	#15
		rts

# int _iocs_crtmod (int);
FUNC _iocs_crtmod
		move.l	4(sp), d1
		moveq	#0x10, d0
		trap	#15
		rts

# int _iocs_dakjob (char *);
FUNC _iocs_dakjob
		move.l	4(sp), a1
		moveq	#0xffffffa4, d0
		trap	#15
		rts

# int _iocs_dateasc (int, char *);
FUNC _iocs_dateasc
		movem.l	4(sp),d1/a1
		moveq	#0x5a, d0
		trap	#15
		rts

# int _iocs_datebin (int);
FUNC _iocs_datebin
		move.l	4(sp), d1
		moveq	#0x55, d0
		trap	#15
		rts

# int _iocs_datecnv (const char *);
FUNC _iocs_datecnv
		move.l	4(sp), a1
		moveq	#0x58, d0
		trap	#15
		rts

# void _iocs_dayasc (int, char *);
FUNC _iocs_dayasc
		movem.l	4(sp),d1/a1
		moveq	#0x5c, d0
		trap	#15
		rts

# int _iocs_defchr (int, int, const void *);
FUNC _iocs_defchr
		movem.l	4(sp), d0-d1/a1
		swap	d1
		move.w	d0, d1
		swap	d1
		moveq	#0x0f, d0
		trap	#15
		rts

# void _iocs_densns (void);
FUNC _iocs_densns
		moveq	#0x7e, d0
		trap	#15
		rts

# int _iocs_dmamode (void);
FUNC _iocs_dmamode
		moveq	#0xffffff8d, d0
		trap	#15
		rts

# void _iocs_dmamov_a (const struct _iocs_chain *, void *, int, int);
FUNC _iocs_dmamov_a
		move.l	d2, -(sp)
		move.l	a2, -(sp)
		movem.l	12(sp), d1-d2/a1-a2
		exg	d1, a1
		exg	d2, a2
		moveq	#0xffffff8b, d0
		trap	#15
		move.l	(sp)+, a2
		move.l	(sp)+, d2
		rts

# void _iocs_dmamove (void *, void *, int, int);
FUNC _iocs_dmamove
		move.l	d2, -(sp)
		move.l	a2, -(sp)
		movem.l	12(sp), d1-d2/a1-a2
		exg	d1, a1
		exg	d2, a2
		moveq	#0xffffff8a, d0
		trap	#15
		move.l	(sp)+, a2
		move.l	(sp)+, d2
		rts

# void _iocs_dmamov_l (const struct _iocs_chain2 *, void *, int);
FUNC _iocs_dmamov_l
		move.l	a2, -(sp)
		movem.l	8(sp), a1/a2
		move.l	16(sp), d1
		moveq	#0xffffff8c, d0
		trap	#15
		move.l	(sp)+, a2
		rts

# int _iocs_drawmode (int); /* rom 1.3, iocs.x */
FUNC _iocs_drawmode
		move.l	4(sp), d1
		moveq	#0xffffffb0, d0
		trap	#15
		rts

# int _iocs_fill (const struct _iocs_fillptr *);
FUNC _iocs_fill
		move.l	4(sp), a1
		moveq	#0xffffffba, d0
		trap	#15
		rts

# int _iocs_fntget (int, int, struct _iocs_fntbuf *);
FUNC _iocs_fntget
		movem.l	4(sp), d0-d1/a1
		swap	d1
		move.w	d0, d1
		swap	d1
		moveq	#0x19, d0
		trap	#15
		rts

# void _iocs_g_clr_on (void);
FUNC _iocs_g_clr_on
		moveq	#0xffffff90, d0
		trap	#15
		rts

# int _iocs_getgrm (struct _iocs_getptr *);
FUNC _iocs_getgrm
		move.l	4(sp), a1
		moveq	#0xffffffbe, d0
		trap	#15
		rts

# int _iocs_gpalet (int, int);
FUNC _iocs_gpalet
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0xffffff94, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_hanjob (char *);
FUNC _iocs_hanjob
		move.l	4(sp), a1
		moveq	#0xffffffa5, d0
		trap	#15
		rts

# int _iocs_home (int, int, int);
FUNC _iocs_home
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0xffffffb3, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int __pure _iocs_hsvtorgb (int, int, int) __attribute__((const));
FUNC _iocs_hsvtorgb
		move.b	7(sp), d1
		swap	d1
		move.b	11(sp), d1
		lsl.w	#8, d1
		move.b	15(sp), d1
		and.l	#0x00ff1f1f, d1
		moveq	#0x12, d0
		trap	#15
		rts

# int _iocs_hsyncst (const void *);
FUNC _iocs_hsyncst
		move.l	4(sp), a1
		moveq	#0x6e, d0
		trap	#15
		rts

# int _iocs_init_prn (int, int);
FUNC _iocs_init_prn
		moveq	#0, d1
		move.b	7(sp), d1
		lsl.w	#8, d1
		move.b	11(sp), d1
		moveq	#0x3c, d0
		trap	#15
		rts

# int _iocs_inp232c (void);
FUNC _iocs_inp232c
		moveq	#0x32, d0
		trap	#15
		rts

# __dead void _iocs_iplerr (void);
FUNC _iocs_iplerr
		moveq	#0xfffffffe, d0
		trap	#15
# int _iocs_isns232c (void);
FUNC _iocs_isns232c
		moveq	#0x33, d0
		trap	#15
		rts

# int __pure _iocs_jissft (int) __attribute__((const));
FUNC _iocs_jissft
		move.l	4(sp), d1
		moveq	#0xffffffa1, d0
		trap	#15
		rts

# int _iocs_joyget (int);
FUNC _iocs_joyget
		move.l	4(sp), d1
		moveq	#0x3b, d0
		trap	#15
		rts

# void _iocs_ledmod (int, int);
FUNC _iocs_ledmod
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x0d, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_line (const struct _iocs_lineptr *);
FUNC _iocs_line
		move.l	4(sp), a1
		moveq	#0xffffffb8, d0
		trap	#15
		rts

# int _iocs_lof232c (void);
FUNC _iocs_lof232c
		moveq	#0x31, d0
		trap	#15
		rts

# int _iocs_mpu_stat (void); /* rom 1.3 only */
FUNC _iocs_mpu_stat
		moveq	#0, d1
		moveq	#0xffffffac, d0
		trap	#15
		rts

# int _iocs_ms_curgt (void);
FUNC _iocs_ms_curgt
		moveq	#0x75, d0
		trap	#15
		rts

# void _iocs_ms_curof (void);
FUNC _iocs_ms_curof
		moveq	#0x72, d0
		trap	#15
		rts

# void _iocs_ms_curon (void);
FUNC _iocs_ms_curon
		moveq	#0x71, d0
		trap	#15
		rts

# int _iocs_ms_curst (int, int);
FUNC _iocs_ms_curst
		move.w	6(sp), d1
		swap	d1
		move.w	10(sp), d1
		moveq	#0x76, d0
		trap	#15
		rts

# int _iocs_ms_getdt (void);
FUNC _iocs_ms_getdt
		moveq	#0x74, d0
		trap	#15
		rts

# void _iocs_ms_init (void);
FUNC _iocs_ms_init
		moveq	#0x70, d0
		trap	#15
		rts

# int _iocs_ms_limit (int, int, int, int);
FUNC _iocs_ms_limit
		move.l	d2, -(sp)
		movem.l	8(sp), d1-d2
		swap	d1
		move.w	d2, d1
		move.w	18(sp), d2
		swap	d2
		move.w	22(sp), d2
		moveq	#0x77, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_ms_offtm (int, int);
FUNC _iocs_ms_offtm
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x78, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_ms_ontm (int, int);
FUNC _iocs_ms_ontm
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x79, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_ms_patst (int, const struct _iocs_patst *);
FUNC _iocs_ms_patst
		movem.l	4(sp),d1/a1
		moveq	#0x7a, d0
		trap	#15
		rts

# void _iocs_ms_sel2 (const short *);
FUNC _iocs_ms_sel2
		move.l	4(sp), a1
		moveq	#0x7c, d0
		trap	#15
		rts

# void _iocs_ms_sel (int);
FUNC _iocs_ms_sel
		move.l	4(sp), d1
		moveq	#0x7b, d0
		trap	#15
		rts

# int _iocs_ms_stat (void);
FUNC _iocs_ms_stat
		moveq	#0x73, d0
		trap	#15
		rts

# struct iocs_time _iocs_ontime (void);
FUNC _iocs_ontime
		moveq	#0x7f, d0
		trap	#15
		rts

# int _iocs_opmintst (const void *);
FUNC _iocs_opmintst
		move.l	4(sp), a1
		moveq	#0x6a, d0
		trap	#15
		rts

# void _iocs_opmset (int, int);
FUNC _iocs_opmset
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x68, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_opmsns (void);
FUNC _iocs_opmsns
		moveq	#0x69, d0
		trap	#15
		rts

# void _iocs_os_curof (void);
FUNC _iocs_os_curof
		moveq	#0xffffffaf, d0
		trap	#15
		rts

# void _iocs_os_curon (void);
FUNC _iocs_os_curon
		moveq	#0xffffffae, d0
		trap	#15
		rts

# int _iocs_osns232c (void);
FUNC _iocs_osns232c
		moveq	#0x34, d0
		trap	#15
		rts

# void _iocs_out232c (int);
FUNC _iocs_out232c
		move.l	4(sp), d1
		moveq	#0x35, d0
		trap	#15
		rts

# void _iocs_outlpt (int);
FUNC _iocs_outlpt
		move.l	4(sp), d1
		moveq	#0x3e, d0
		trap	#15
		rts

# void _iocs_outprn (int);
FUNC _iocs_outprn
		move.l	4(sp), d1
		moveq	#0x3f, d0
		trap	#15
		rts

# int _iocs_paint (struct _iocs_paintptr *);
FUNC _iocs_paint
		move.l	4(sp), a1
		moveq	#0xffffffbc, d0
		trap	#15
		rts

# int _iocs_point (const struct _iocs_pointptr *);
FUNC _iocs_point
		move.l	4(sp), a1
		moveq	#0xffffffb7, d0
		trap	#15
		rts

# int _iocs_prnintst (const void *);
FUNC _iocs_prnintst
		move.l	4(sp), a1
		moveq	#0x6f, d0
		trap	#15
		rts

# int _iocs_pset (const struct _iocs_psetptr *);
FUNC _iocs_pset
		move.l	4(sp), a1
		moveq	#0xffffffb6, d0
		trap	#15
		rts

# int _iocs_putgrm (const struct _iocs_putptr *);
FUNC _iocs_putgrm
		move.l	4(sp), a1
		moveq	#0xffffffbf, d0
		trap	#15
		rts

# int _iocs_rmacnv (int, char *, char *);
FUNC _iocs_rmacnv
		move.l	a2, -(sp)
		movem.l	8(sp),d1/a1/a2
		moveq	#0xffffffa3, d0
		trap	#15
		move.l	(sp)+, a2
		rts

# int __pure _iocs_romver (void) __attribute__((const));
FUNC _iocs_romver
		moveq	#0xffffff8f, d0
		trap	#15
		rts

# int _iocs_s_cmdout (int, void *);
FUNC _iocs_s_cmdout
		move.l	d3, -(sp)
		movem.l	8(sp),d3/a1
		moveq	#3, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d3
		rts

# void _iocs_scroll (int, int, int);
FUNC _iocs_scroll
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0x1d, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_s_datain (int, void *);
FUNC _iocs_s_datain
		move.l	d3, -(sp)
		movem.l	8(sp),d3/a1
		moveq	#4, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d3
		rts

# int _iocs_s_dataout (int, void *);
FUNC _iocs_s_dataout
		move.l	d3, -(sp)
		movem.l	8(sp),d3/a1
		moveq	#5, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d3
		rts

# int _iocs_set232c (int);
FUNC _iocs_set232c
		move.l	4(sp), d1
		moveq	#0x30, d0
		trap	#15
		rts

# int _iocs_s_format (int, int);
FUNC _iocs_s_format
		move.l	d3, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d3/d4
		moveq	#35, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d3
		rts

# int __pure _iocs_sftjis (int) __attribute__((const));
FUNC _iocs_sftjis
		move.l	4(sp), d1
		moveq	#0xffffffa0, d0
		trap	#15
		rts

# int _iocs_s_inquiry (int, int, struct _iocs_inquiry *);
FUNC _iocs_s_inquiry
		move.l	d3, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d3/d4/a1
		moveq	#32, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d3
		rts

# int _iocs_skey_mod (int, int, int);
FUNC _iocs_skey_mod
		move.l	d2, -(sp)
		move.l	8(sp), d1
		move.w	14(sp), d2
		swap	d2
		move.w	18(sp), d2
		moveq	#0x7d, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_skeyset (int);
FUNC _iocs_skeyset
		move.l	4(sp), d1
		moveq	#0x05, d0
		trap	#15
		rts

# int _iocs_s_msgin (void *);
FUNC _iocs_s_msgin
		move.l	4(sp), a1
		moveq	#7, d1
		moveq	#0xfffffff5, d0
		trap	#15
		rts

# int _iocs_s_msgout (void *);
FUNC _iocs_s_msgout
		move.l	4(sp), a1
		moveq	#8, d1
		moveq	#0xfffffff5, d0
		trap	#15
		rts

# int _iocs_snsprn (void);
FUNC _iocs_snsprn
		moveq	#0x3d, d0
		trap	#15
		rts

# int _iocs_spalet (int, int, int);
FUNC _iocs_spalet
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0xffffffcf, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# int _iocs_s_pamedium (int, int);
FUNC _iocs_s_pamedium
		move.l	d3, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d3/d4
		moveq	#50, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d3
		rts

# int _iocs_sp_cgclr (int);
FUNC _iocs_sp_cgclr
		move.l	4(sp), d1
		moveq	#0xffffffc3, d0
		trap	#15
		rts

# int _iocs_sp_defcg (int, int, const void *);
FUNC _iocs_sp_defcg
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2/a1
		moveq	#0xffffffc4, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_sp_gtpcg (int, int, void *);
FUNC _iocs_sp_gtpcg
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2/a1
		moveq	#0xffffffc5, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_s_phase (void);
FUNC _iocs_s_phase
		moveq	#9, d1
		moveq	#0xfffffff5, d0
		trap	#15
		rts

# int _iocs_sp_init (void);
FUNC _iocs_sp_init
		moveq	#0xffffffc0, d0
		trap	#15
		rts

# void _iocs_sp_off (void);
FUNC _iocs_sp_off
		moveq	#0xffffffc2, d0
		trap	#15
		rts

# int _iocs_sp_on (void);
FUNC _iocs_sp_on
		moveq	#0xffffffc1, d0
		trap	#15
		rts

# int _iocs_sp_reggt (int, int *, int *, int *, int *);
FUNC _iocs_sp_reggt
		movem.l	d2/d3/d4/d5, -(sp)
		move.l	20(sp), d1
		moveq	#0xffffffc7, d0
		trap	#15
		tst.l	d0
		bnes	6f
		movem.l	24(sp), a0/a1
		move.l	d2, (a0)
		move.l	d3, (a1)
		movem.l	32(sp), a0/a1
		move.l	d4, (a0)
		move.l	d5, (a1)
6:
		movem.l	(sp)+,d2/d3/d4/d5
		rts

# int _iocs_sp_regst (int, int, int, int, int, int);
FUNC _iocs_sp_regst
		movem.l	d2/d3/d4/d5, -(sp)
		movem.l	20(sp),d0/d1/d2/d3/d4/d5
		and.l	#0x80000000, d1
		move.b	d0, d1
		moveq	#0xffffffc6, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4/d5
		rts

# int _iocs_s_readcap (int, struct _iocs_readcap *);
FUNC _iocs_s_readcap
		move.l	d4, -(sp)
		movem.l	8(sp),d4/a1
		moveq	#37, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		rts

# int _iocs_s_readext (int, int, int, int, void *);
FUNC _iocs_s_readext
		movem.l	d2/d3/d4/d5, -(sp)
		movem.l	20(sp),d2/d3/d4/d5/a1
		moveq	#38, d1
		moveq	#0xfffffff5, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4/d5
		rts

# int _iocs_s_read (int, int, int, int, void *);
FUNC _iocs_s_read
		movem.l	d2/d3/d4/d5, -(sp)
		movem.l	20(sp),d2/d3/d4/d5/a1
		moveq	#33, d1
		moveq	#0xfffffff5, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4/d5
		rts

# int _iocs_s_reassign (int, int, void *);
FUNC _iocs_s_reassign
		move.l	d3, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d3/d4/a1
		moveq	#49, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d3
		rts

# int _iocs_s_request (int, int, void *);
FUNC _iocs_s_request
		move.l	d3, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d3/d4/a1
		moveq	#44, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d3
		rts

# void _iocs_s_reset (void);
FUNC _iocs_s_reset
		moveq	#0, d1
		moveq	#0xfffffff5, d0
		trap	#15
		rts

# int _iocs_s_rezerounit (int);
FUNC _iocs_s_rezerounit
		move.l	d4, -(sp)
		move.l	8(sp), d4
		moveq	#43, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		rts

# int _iocs_s_seek (int, int);
FUNC _iocs_s_seek
		move.l	d2, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d2/d4
		moveq	#45, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d2
		rts

# int _iocs_s_select (int);
FUNC _iocs_s_select
		move.l	d4, -(sp)
		move.l	8(sp), d4
		moveq	#1, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		rts

# int _iocs_s_startstop (int, int);
FUNC _iocs_s_startstop
		move.l	d3, -(sp)
		move.l	d4, -(sp)
		movem.l	12(sp),d3/d4
		moveq	#47, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		move.l	(sp)+, d3
		rts

# int _iocs_s_stsin (void *);
FUNC _iocs_s_stsin
		move.l	4(sp), a1
		moveq	#6, d1
		moveq	#0xfffffff5, d0
		trap	#15
		rts

# int _iocs_s_testunit (int);
FUNC _iocs_s_testunit
		move.l	d4, -(sp)
		move.l	8(sp), d4
		moveq	#36, d1
		moveq	#0xfffffff5, d0
		trap	#15
		move.l	(sp)+, d4
		rts

# int _iocs_s_writeext (int, int, int, int, void *);
FUNC _iocs_s_writeext
		movem.l	d2/d3/d4/d5, -(sp)
		movem.l	20(sp),d2/d3/d4/d5/a1
		moveq	#39, d1
		moveq	#0xfffffff5, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4/d5
		rts

# int _iocs_s_write (int, int, int, int, void *);
FUNC _iocs_s_write
		movem.l	d2/d3/d4/d5, -(sp)
		movem.l	20(sp),d2/d3/d4/d5/a1
		moveq	#34, d1
		moveq	#0xfffffff5, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4/d5
		rts

# int _iocs_symbol (const struct _iocs_symbolptr *);
FUNC _iocs_symbol
		move.l	4(sp), a1
		moveq	#0xffffffbd, d0
		trap	#15
		rts

# void _iocs_tcolor (int);
FUNC _iocs_tcolor
		move.l	4(sp), d1
		moveq	#0x15, d0
		trap	#15
		rts

# void _iocs_textget (int, int, struct _iocs_fntbuf *);
FUNC _iocs_textget
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2/a1
		moveq	#0x1a, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# void _iocs_textput (int, int, const struct _iocs_fntbuf *);
FUNC _iocs_textput
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2/a1
		moveq	#0x1b, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_tgusemd (int, int);
FUNC _iocs_tgusemd
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x0e, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_timeasc (int, char *);
FUNC _iocs_timeasc
		movem.l	4(sp),d1/a1
		moveq	#0x5b, d0
		trap	#15
		rts

# int _iocs_timebcd (int);
FUNC _iocs_timebcd
		move.l	4(sp), d1
		moveq	#0x52, d0
		trap	#15
		rts

# int _iocs_timebin (int);
FUNC _iocs_timebin
		move.l	4(sp), d1
		moveq	#0x57, d0
		trap	#15
		rts

# int _iocs_timecnv (const char *);
FUNC _iocs_timecnv
		move.l	4(sp), a1
		moveq	#0x59, d0
		trap	#15
		rts

# int _iocs_timeget (void);
FUNC _iocs_timeget
		moveq	#0x56, d0
		trap	#15
		rts

# int _iocs_timerdst (const void *, int, int);
FUNC _iocs_timerdst
		movea.l	4(sp), a1
		moveq	#0, d1
		move.b	11(sp), d1
		lsl.w	#8, d1
		move.b	15(sp), d1
		moveq	#0x6b, d0
		trap	#15
		rts

# void _iocs_timeset (int);
FUNC _iocs_timeset
		move.l	4(sp), d1
		moveq	#0x53, d0
		trap	#15
		rts

# int _iocs_tpalet2 (int, int);
FUNC _iocs_tpalet2
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x14, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_tpalet (int, int);
FUNC _iocs_tpalet
		move.l	d2, -(sp)
		movem.l	8(sp),d1/d2
		moveq	#0x13, d0
		trap	#15
		move.l	(sp)+, d2
		rts

# int _iocs_trap15 (struct iocs_regs *, struct iocs_regs *)
FUNC _iocs_trap15
		moveml	d2-d7/a2-a6,-(sp)
		moveal	48(sp),a0	/* inregs */
		moveml	(a0),d0-d7/a1-a6
		trap	#15
		moveal	52(sp),a0	/* outregs */
		moveml	d0-d7/a1-a6,(a0)
		moveml	(sp)+,d2-d7/a2-a6
		rts


# void _iocs_tvctrl (int);
FUNC _iocs_tvctrl
		move.l	4(sp), d1
		moveq	#0x0c, d0
		trap	#15
		rts

# void _iocs_txbox (const struct _iocs_tboxptr *);
FUNC _iocs_txbox
		move.l	4(sp), a1
		moveq	#0xffffffd6, d0
		trap	#15
		rts

# void _iocs_txfill (const struct _iocs_txfillptr *);
FUNC _iocs_txfill
		move.l	4(sp), a1
		moveq	#0xffffffd7, d0
		trap	#15
		rts

# void _iocs_txline (struct _iocs_tlineptr); /* 1.3, iocs.x */
FUNC _iocs_txline
		move.l	4(sp), a1
		moveq	#0xffffffd5, d0
		trap	#15
		rts

# void _iocs_txrascpy (int, int, int);
FUNC _iocs_txrascpy
		move.l	d2, -(sp)
		move.l	d3, -(sp)
		movem.l	12(sp),d1/d2/d3
		moveq	#0xffffffdf, d0
		trap	#15
		move.l	(sp)+, d3
		move.l	(sp)+, d2
		rts

# void _iocs_txrev (const struct _iocs_trevptr *);
FUNC _iocs_txrev
		move.l	4(sp), a1
		moveq	#0xffffffd8, d0
		trap	#15
		rts

# void _iocs_txxline (const struct _iocs_xlineptr *);
FUNC _iocs_txxline
		move.l	4(sp), a1
		moveq	#0xffffffd3, d0
		trap	#15
		rts

# void _iocs_txyline (const struct _iocs_ylineptr *);
FUNC _iocs_txyline
		move.l	4(sp), a1
		moveq	#0xffffffd4, d0
		trap	#15
		rts

# int _iocs_vdispst (const void *, int, int);
FUNC _iocs_vdispst
		movea.l	4(sp), a1
		moveq	#0, d1
		move.b	11(sp), d1
		lsl.w	#8, d1
		move.b	15(sp), d1
		moveq	#0x6c, d0
		trap	#15
		rts

# int _iocs_vpage (int);
FUNC _iocs_vpage
		move.l	4(sp), d1
		moveq	#0xffffffb2, d0
		trap	#15
		rts

# int _iocs_window (int, int, int, int);
FUNC _iocs_window
		movem.l	d2/d3/d4, -(sp)
		movem.l	16(sp),d1/d2/d3/d4
		moveq	#0xffffffb4, d0
		trap	#15
		movem.l	(sp)+,d2/d3/d4
		rts

# int _iocs_wipe (void);
FUNC _iocs_wipe
		moveq	#0xffffffb5, d0
		trap	#15
		rts

