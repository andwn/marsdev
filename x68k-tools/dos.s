.macro FUNC _name, _align=2
    .globl \_name
    .type  \_name, @function
    .align \_align
\_name:
.endm


# void _dos_allclose (void);
FUNC _dos_allclose
        dc.w    0xFF1F
        rts

# int _dos_bindno (const char *, const char *);
FUNC _dos_bindno
        movem.l	d2-d7/a2-a6,-(sp)
        clr.l	-(sp)
        move.l	56(sp),-(sp)
        move.l	56(sp),-(sp)
        move.w	#5,-(sp)
        dc.w	0xFF4B
        lea	    14(sp),sp
        movem.l	(sp)+,d2-d7/a2-a6
        rts

# int _dos_breakck (int);
FUNC _dos_breakck
        move.w	6(sp),-(sp)
        dc.w	0xFF33
        addq.l	#2,sp
        rts

# int _dos_c_cls_al (void);
FUNC _dos_c_cls_al
        move.w	#2, -(sp)
        move.w	#10, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_cls_ed (void);
FUNC _dos_c_cls_ed
        clr.w	-(sp)
        move.w	#10, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_cls_st (void);
FUNC _dos_c_cls_st
        move.w	#1, -(sp)
        move.w	#10, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_color (int);
FUNC _dos_c_color
        move.w	6(sp), -(sp)
        move.w	#2, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_curoff (void);
FUNC _dos_c_curoff
        move.w	#18, -(sp)
        dc.w	0xff23
        addq.l	#2, sp
        rts

# int _dos_c_curon (void);
FUNC _dos_c_curon
        move.w	#17, -(sp)
        dc.w	0xff23
        addq.l	#2, sp
        rts

# int _dos_c_del (int);
FUNC _dos_c_del
        move.w	6(sp), -(sp)
        move.w	#13, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_down (int);
FUNC _dos_c_down
        move.w	6(sp), -(sp)
        move.w	#7, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_down_s (void);
FUNC _dos_c_down_s
        move.w	#4, -(sp)
        dc.w	0xff23
        addq.l	#2, sp
        rts

# int _dos_c_era_al (void);
FUNC _dos_c_era_al
        move.w	#2, -(sp)
        move.w	#11, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_era_ed (void);
FUNC _dos_c_era_ed
        clr.w	-(sp)
        move.w	#11, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_era_st (void);
FUNC _dos_c_era_st
        move.w	#1, -(sp)
        move.w	#11, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_fnkmod (int);
FUNC _dos_c_fnkmod
        move.w	6(sp), -(sp)
        move.w	#14, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_ins (int);
FUNC _dos_c_ins
        move.w	6(sp), -(sp)
        move.w	#12, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_left (int);
FUNC _dos_c_left
        move.w	6(sp), -(sp)
        move.w	#9, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_locate (int, int);
FUNC _dos_c_locate
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        move.w	#3, -(sp)
        dc.w	0xff23
        addq.l	#6, sp
        rts

# int _dos_c_print (const char *);
FUNC _dos_c_print
        move.l	4(sp), -(sp)
        move.w	#1, -(sp)
        dc.w	0xff23
        addq.l	#6, sp
        rts

# int _dos_c_putc (int);
FUNC _dos_c_putc
        move.w	6(sp), -(sp)
        clr.w	-(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_right (int);
FUNC _dos_c_right
        move.w	6(sp), -(sp)
        move.w	#8, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_up (int);
FUNC _dos_c_up
        move.w	6(sp), -(sp)
        move.w	#6, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_up_s (void);
FUNC _dos_c_up_s
        move.w	#5, -(sp)
        dc.w	0xff23
        addq.l	#2, sp
        rts

# int _dos_c_width (int);
FUNC _dos_c_width
        move.w	6(sp), -(sp)
        move.w	#16, -(sp)
        dc.w	0xff23
        addq.l	#4, sp
        rts

# int _dos_c_window (int, int);
FUNC _dos_c_window
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        move.w	#15, -(sp)
        dc.w	0xff23
        addq.l	#6, sp
        rts

# void _dos_change_pr (void);
FUNC _dos_change_pr
	    dc.w	0xFFFF
	    rts

# int _dos_chdir (const char *);
FUNC _dos_chdir
        move.l	4(sp),-(sp)
        dc.w	0xFF3B
        addq.l	#4,sp
        rts

# int _dos_chgdrv (int);
FUNC _dos_chgdrv
        move.w	6(sp),-(sp)
        dc.w	0xFF0E
        addq.l	#2,sp
        rts

# _dos_mode_t _dos_chmod (const char *, _dos_mode_t);
FUNC _dos_chmod
        move.w	10(sp),-(sp)
        move.l	6(sp),-(sp)
        dc.w	0xFF43
        addq.l	#6,sp
        rts

# int _dos_cinsns (void);
FUNC _dos_cinsns
        dc.w	0xFF12
        rts

# int _dos_close (int);
FUNC _dos_close
        move.w	6(sp),-(sp)
        dc.w	0xFF3E
        addq.l	#2,sp
        rts

# int _dos_cominp (void);
FUNC _dos_cominp
        dc.w	0xFF03
        rts

# void _dos_comout (int);
FUNC _dos_comout
        move.w	6(sp),-(sp)
        dc.w	0xFF04
        addq.l	#2,sp
        rts

# int _dos_common_ck (const char *);
FUNC _dos_common_ck
        move.l	4(sp), -(sp)
        clr.w	-(sp)
        dc.w	0xff85
        addq.l	#6, sp
        rts

# int _dos_common_del (const char *);
FUNC _dos_common_del
        move.l	4(sp), -(sp)
        move.w	#5, -(sp)
        dc.w	0xff85
        addq.l	#6, sp
        rts

# int _dos_common_fre (const char *, int, int, int);
FUNC _dos_common_fre
        movem.l	4(sp), d0-d1/a0-a1
        movem.l	d0-d1/a0-a1, -(sp)
        move.w	#4, -(sp)
        dc.w	0xff85
        lea	    18(sp), sp
        rts

# int _dos_common_lk (const char *, int, int, int);
FUNC _dos_common_lk
        movem.l	4(sp), d0-d1/a0-a1
        movem.l	d0-d1/a0-a1, -(sp)
        move.w	#3, -(sp)
        dc.w	0xff85
        lea	    18(sp), sp
        rts

# int _dos_common_rd (const char *, int, char *, int);
FUNC _dos_common_rd
        movem.l	4(sp), d0-d1/a0-a1
        movem.l	d0-d1/a0-a1, -(sp)
        move.w	#1, -(sp)
        dc.w	0xff85
        lea	    18(sp), sp
        rts

# int _dos_common_wt (const char *, int, const char *, int);
FUNC _dos_common_wt
        movem.l	4(sp), d0-d1/a0-a1
        movem.l	d0-d1/a0-a1, -(sp)
        move.w	#2, -(sp)
        dc.w	0xff85
        lea	    18(sp), sp
        rts

# int _dos_consns (void);
FUNC _dos_consns
        dc.w	0xFF10
        rts

# int _dos_coutsns (void);
FUNC _dos_coutsns
        dc.w	0xFF13
        rts

# int _dos_create (const char *, _dos_mode_t);
FUNC _dos_create
        move.w	10(sp),-(sp)
        move.l	6(sp),-(sp)
        dc.w	0xFF3C
        addq.l	#6,sp
        rts

# __dead void _dos_ctlabort (void);
FUNC _dos_ctlabort
	    dc.w	0xFFF1

# int _dos_curdir (int, char *);
FUNC _dos_curdir
        move.l	8(sp),-(sp)
        move.w	10(sp),-(sp)
        dc.w	0xFF47
        addq.l	#6,sp
        rts

# int _dos_curdrv (void);
FUNC _dos_curdrv
        dc.w	0xff19
        rts

# int _dos_delete (const char *);
FUNC _dos_delete
        move.l	4(sp), -(sp)
        dc.w	0xff41
        addq.l	#4, sp
        rts

# void _dos_diskred (void *, int, int, int);
FUNC _dos_diskred
        move.w	18(sp), -(sp)
        move.w	16(sp), -(sp)
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        dc.w	0xfff3
        lea	10(sp), sp
        rts

# void _dos_diskred2 (void *, int, int, int);
FUNC _dos_diskred2
        move.l	16(sp), -(sp)
        move.l	16(sp), -(sp)
        move.w	18(sp), -(sp)
        move.l	14(sp), d0
        bset	#31, d0
        move.l	d0, -(sp)
        dc.w	0xfff3
        lea	14(sp), sp
        rts

# void _dos_diskwrt (const void *, int, int, int);
FUNC _dos_diskwrt
        move.w	18(sp), -(sp)
        move.w	16(sp), -(sp)
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        dc.w	0xfff4
        lea	10(sp), sp
        rts

# void _dos_diskwrt2 (const void *, int, int, int);
FUNC _dos_diskwrt2
        move.l	16(sp), -(sp)
        move.l	16(sp), -(sp)
        move.w	18(sp), -(sp)
        move.l	14(sp), d0
        bset	#31, d0
        move.l	d0, -(sp)
        dc.w	0xfff4
        lea	14(sp), sp
        rts

# int _dos_drvctrl (int, int);
FUNC _dos_drvctrl
        move.b	7(sp), d0
        lsl.w	#8, d0
        move.b	11(sp), d0
        move.w	d0, -(sp)
        dc.w	0xff0f
        addq.l	#2, sp
        rts

# void _dos_drvxchg (int, int);
FUNC _dos_drvxchg
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        dc.w	0xff34
        addq.l	#4, sp
        rts

# int _dos_dskfre (int, struct _dos_freeinf *);
FUNC _dos_dskfre
    	move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xff36
        addq.l	#6, sp
        rts

# int _dos_dup (int);
FUNC _dos_dup
        move.w	6(sp), -(sp)
        dc.w	0xff45
        addq.l	#2, sp
        rts

# int _dos_dup0 (int, int);
FUNC _dos_dup0
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        dc.w	0xff2f
        addq.l	#4, sp
        rts

# int _dos_dup2 (int, int);
FUNC _dos_dup2
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        dc.w	0xff46
        addq.l	#4, sp
        rts

# __dead void _dos_errabort (void);
FUNC _dos_errabort
        dc.w	0xfff2

# int _dos_exec2 (int, const char *, const char *, const char *);
FUNC _dos_exec2
        movem.l	d2-d7/a2-a6, -(sp)
        movem.l	48(sp), d0-d1/a0-a1
        movem.l	d1/a0-a1, -(sp)
        move.w	d0, -(sp)
        dc.w	0xff4b
        lea	14(sp), sp
        movem.l	sp@+, d2-d7/a2-a6
        rts

# int _dos_execonly (void *);
FUNC _dos_execonly
        movem.l	d2-d7/a2-a6, -(sp)
        move.l	48(sp), -(sp)
        move.w	#4, -(sp)
        dc.w	0xff4b
        addq.l	#6, sp
        movem.l	sp@+, d2-d7/a2-a6
        rts

# int _dos_exfiles (struct _dos_exfilbuf *, const char *, int);
FUNC _dos_exfiles
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        move.l	10(sp), d0
        bset	#31, d0
        move.l	d0, -(sp)
        dc.w	0xff4e
        lea	    10(sp), sp
        rts

# __dead void _dos_exit (void);
FUNC _dos_exit
        dc.w	0xff00

# __dead void _dos_exit2 (int);
FUNC _dos_exit2
        move.w	6(sp), -(sp)
        dc.w	0xff4c

# int _dos_exnfiles (struct _dos_exfilbuf *);
FUNC _dos_exnfiles
        move.l	4(sp), d0
        bset	#31, d0
        move.l	d0, -(sp)
        dc.w	0xff4f
        addq.l	#4, sp
        rts

# int _dos_fatchk (const char *, unsigned short *);
FUNC _dos_fatchk
        move.l	8(sp), -(sp)
        move.l	8(sp), -(sp)
        dc.w	0xff17
        addq.l	#8, sp
        rts

# int _dos_fatchk2 (const char *, unsigned short *, int);
FUNC _dos_fatchk2
        move.w	14(sp), -(sp)
        move.l	10(sp), d0
        bset	#31, d0
        move.l	d0, -(sp)
        move.l	10(sp), -(sp)
        dc.w	0xff17
        lea	    10(sp), sp
        rts

# void _dos_fflush (void);
FUNC _dos_fflush
        dc.w	0xff0d
        rts

# int _dos_fflush_set (int);
FUNC _dos_fflush_set
        move.w	6(sp), -(sp)
        dc.w	0xffaa
        addq.l	#2, sp
        rts

# int _dos_fgetc (int);
FUNC _dos_fgetc
        move.w	6(sp), -(sp)
        dc.w	0xff1b
        addq.l	#2, sp
        rts

# int _dos_fgets (struct _dos_inpptr *, int);
FUNC _dos_fgets
        move.w	10(sp), -(sp)
        move.l	6(sp), -(sp)
        dc.w	0xff1c
        addq.l	#6, sp
        rts

# int _dos_filedate (int, int);
FUNC _dos_filedate
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xff87
        addq.l	#6, sp
        rts

# int _dos_files (struct _dos_filbuf *, const char *, int);
FUNC _dos_filbuf
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        move.l	10(sp), -(sp)
        dc.w	0xff4e
        lea	10(sp), sp
        rts

# void _dos_fnckeygt (int, char *);
FUNC _dos_fnckeygt
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xff21
        addq.l	#6, sp
        rts

# void _dos_fnckeyst (int, const char *);
FUNC _dos_fnckeyst
        move.l	8(sp), -(sp)
        move.w	10(sp), d0
        or.w	#0x100, d0
        move.w	d0, -(sp)
        dc.w	0xff21
        addq.l	#6, sp
        rts

# void _dos_fputc (int, int);
FUNC _dos_fputc
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        dc.w	0xff1d
        addq.l	#4, sp
        rts

# void _dos_fputs (const char *, int);
FUNC _dos_fputs
        move.w	10(sp), -(sp)
        move.l	6(sp), -(sp)
        dc.w	0xff1e
        addq.l	#6, sp
        rts

# union _dos_fcb *_dos_get_fcb_adr (unsigned int);
FUNC _dos_get_fcb_adr
        move.w	6(sp), -(sp)
        dc.w	0xffac
        addq.l	#2, sp
        rts

# int _dos_get_pr (int, struct _dos_prcptr *);
FUNC _dos_get_pr
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xfffa
        addq.l	#6, sp
        rts

# int _dos_getassign (const char *, char *);
FUNC _dos_getassign
        move.l	8(sp), -(sp)
        move.l	8(sp), -(sp)
        clr.w	-(sp)
        dc.w	0xff8f
        lea	10(sp), sp
        rts

# int _dos_getc (void);
FUNC _dos_getc
        dc.w	0xff08
        rts

# int _dos_getchar (void);
FUNC _dos_getchar
        dc.w	0xff01
        rts

# int _dos_getdate (void);
FUNC _dos_getdate
        dc.w	0xff2a
        rts

# int _dos_getdpb (int, struct _dos_dpbptr *);
FUNC _dos_getdpb
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xff32
        addq.l	#6, sp
        rts

# int _dos_getenv (const char *, const char *, char *);
FUNC _dos_getenv
        movem.l	4(sp), d0-d1/a0
        movem.l	d0-d1/a0, -(sp)
        dc.w	0xff83
        lea	12(sp), sp
        rts

# struct _dos_psp *_dos_getpdb (void);
FUNC _dos_getpdb
        dc.w	0xff81
        rts

# int _dos_gets (struct _dos_inpptr *);
FUNC _dos_gets
        move.l	4(sp), -(sp)
        dc.w	0xff0a
        addq.l	#4, sp
        rts

# int _dos_getss (struct _dos_inpptr *);
FUNC _dos_getss
        move.l	4(sp), -(sp)
        dc.w	0xff1a
        addq.l	#4, sp
        rts

# int _dos_gettim2 (void);
FUNC _dos_gettim2
        dc.w	0xff27
        rts

# int _dos_gettime (void);
FUNC _dos_gettime
        dc.w	0xff2c
        rts

# void _dos_hendspic (int);
FUNC _dos_hendspic
        move.w	6(sp), -(sp)
        move.w	#7, -(sp)
        dc.w	0xff18
        addq.l	#4, sp
        rts

# int _dos_hendspio (void);
FUNC _dos_hendspio
        move.w	#4, -(sp)
        dc.w	0xff18
        addq.l	#2, sp
        rts

# int _dos_hendspip (int, const char *);
FUNC _dos_hendspip
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        move.w	#5, -(sp)
        dc.w	0xff18
        addq.l	#8, sp
        rts

# int _dos_hendspir (int, const char *);
FUNC _dos_hendspir
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        move.w	#6, -(sp)
        dc.w	0xff18
        addq.l	#8, sp
        rts

# void _dos_hendspmc (void);
FUNC _dos_hendspmc
        move.w	#3, -(sp)
        dc.w	0xff18
        addq.l	#2, sp
        rts

# int _dos_hendspmo (void);
FUNC _dos_hendspmo
        clr.w	-(sp)
        dc.w	0xff18
        addq.l	#2, sp
        rts

# int _dos_hendspmp (int, const char *);
FUNC _dos_hendspmp
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        move.w	#1, -(sp)
        dc.w	0xff18
        addq.l	#8, sp
        rts

# int _dos_hendspmr (int, const char *);
FUNC _dos_hendspmr
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        move.w	#2, -(sp)
        dc.w	0xff18
        addq.l	#8, sp
        rts

# void _dos_hendspsc (void);
FUNC _dos_hendspsc
        move.w	#11, -(sp)
        dc.w	0xff18
        addq.l	#2, sp
        rts

# int _dos_hendspso (void);
FUNC _dos_hendspso
        move.w	#8, -(sp)
        dc.w	0xff18
        addq.l	#2, sp
        rts

# int _dos_hendspsp (int, const char *);
FUNC _dos_hendspsp
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        move.w	#9, -(sp)
        dc.w	0xff18
        addq.l	#8, sp
        rts

# int _dos_hendspsr (int, const char *);
FUNC _dos_hendspsr
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        move.w	#10, -(sp)
        dc.w	0xff18
        addq.l	#8, sp
        rts

# struct _dos_indos *_dos_indosflg (void);
FUNC _dos_indosflg
        dc.w	0xfff5
        rts

# int _dos_inkey (void);
FUNC _dos_inkey
        dc.w	0xff07
        rts

# int _dos_inpout (int);
FUNC _dos_inpout
        move.w	6(sp), -(sp)
        dc.w	0xff06
        addq.l	#2, sp
        rts

# void *_dos_intvcg (int);
FUNC _dos_intvcg
        move.w	6(sp), -(sp)
        dc.w	0xff35
        addq.l	#2, sp
        rts

# void *_dos_intvcs (int, void *);
FUNC _dos_intvcs
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xff25
        addq.l	#6, sp
        rts

# int _dos_ioctrldvctl (int, int, char *);
FUNC _dos_ioctrldvctl
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	12(sp), -(sp)
        move.w	#12, -(sp)
        dc.w	0xff44
        lea	    10(sp), sp
        rts

# int _dos_ioctrldvgt (int);
FUNC _dos_ioctrldvgt
        move.w	6(sp), -(sp)
        move.w	#9, -(sp)
        dc.w	0xff44
        addq.l	#4, sp
        rts

# int _dos_ioctrlfdctl (int, int, char *);
FUNC _dos_ioctrlfdctl
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	12(sp), -(sp)
        move.w	#13, -(sp)
        dc.w	0xff44
        lea	    10(sp), sp
        rts

# int _dos_ioctrlfdgt (int);
FUNC _dos_ioctrlfdgt
        move.w	6(sp), -(sp)
        move.w	#10, -(sp)
        dc.w	0xff44
        addq.l	#4, sp
        rts

# int _dos_ioctrlgt (int);
FUNC _dos_ioctrlgt
        move.w	6(sp), -(sp)
        clr.w	-(sp)
        dc.w	0xff44
        addq.l	#4, sp
        rts

# int _dos_ioctrlis (int);
FUNC _dos_ioctrlis
        move.w	6(sp), -(sp)
        move.w	#6, -(sp)
        dc.w	0xff44
        addq.l	#4, sp
        rts

# int _dos_ioctrlos (int);
FUNC _dos_ioctrlos
        move.w	6(sp), -(sp)
        move.w	#7, -(sp)
        dc.w	0xff44
        addq.l	#4, sp
        rts

# int _dos_ioctrlrd (int, char *, int);
FUNC _dos_ioctrlrd
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	#4, -(sp)
        dc.w	0xff44
        lea	    12(sp), sp
        rts

# int _dos_ioctrlrh (int, char *, int);
FUNC _dos_ioctrlrh
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	#2, -(sp)
        dc.w	0xff44
        lea	    12(sp), sp
        rts

# int _dos_ioctrlrtset (int, int);
FUNC _dos_ioctrlrtset
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        move.w	#11, -(sp)
        dc.w	0xff44
        addq.l	#6, sp
        rts

# int _dos_ioctrlst (int, int);
FUNC _dos_ioctrlst
        move.w	10(sp), -(sp)
        move.w	8(sp), -(sp)
        move.w	#1, -(sp)
        dc.w	0xff44
        addq.l	#6, sp
        rts

# int _dos_ioctrlwd (int, const char *, int);
FUNC _dos_ioctrlwd
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	#5, -(sp)
        dc.w	0xff44
        lea	    12(sp), sp
        rts

# int _dos_ioctrlwh (int, const char *, int);
FUNC _dos_ioctrlwh
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	#3, -(sp)
        dc.w	0xff44
        lea	    12(sp), sp
        rts

# __dead void _dos_keeppr (int, int);
FUNC _dos_keeppr
        move.w	10(sp), -(sp)
        move.l	6(sp), -(sp)
        dc.w	0xff31

# int _dos_keysns (void);
FUNC _dos_keysns
        dc.w	0xff0b
        rts

# int _dos_kill_pr (void);
FUNC _dos_kill_pr
        dc.w	0xfff9
        rts

# int _dos_load (const char *, const struct _dos_comline *, const char *);
FUNC _dos_comline
        movem.l	d2-d7/a2-a6, -(sp)
        movem.l	48(sp), d0-d1/a0
        movem.l	d0-d1/a0, -(sp)
        move.w	#1, -(sp)
        dc.w	0xff4b
        lea	14(sp), sp
        movem.l	(sp)+, d2-d7/a2-a6
        rts

# int _dos_loadexec (const char *, const struct _dos_comline *, const char *);
FUNC _dos_loadexec
        movem.l	d2-d7/a2-a6, -(sp)
        movem.l	48(sp), d0-d1/a0
        movem.l	d0-d1/a0, -(sp)
        clr.w	-(sp)
        dc.w	0xff4b
        lea	    14(sp), sp
        movem.l	(sp)+, d2-d7/a2-a6
        rts

# int _dos_loadonly (const char *, const void *, const void *);
FUNC _dos_loadonly
        movem.l	4(sp), d0-d1/a0
        movem.l	d0-d1/a0, -(sp)
        move.w	#3, -(sp)
        dc.w	0xff4b
        lea	    14(sp), sp
        rts

# int _dos_lock (int, int, int);
FUNC _dos_lock
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        clr.w	-(sp)
        dc.w	0xff8c
        lea	    12(sp), sp
        rts

# int _dos_makeassign (const char *, const char *, int);
FUNC _dos_makeassign
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        move.l	10(sp), -(sp)
        move.w	#1, -(sp)
        dc.w	0xff8f
        lea	    12(sp), sp
        rts

# int _dos_maketmp (const char *, int);
FUNC _dos_maketmp
        move.w	10(sp), -(sp)
        move.l	6(sp), -(sp)
        dc.w	0xff8a
        addq.l	#6, sp
        rts

# void *_dos_malloc (int);
FUNC _dos_malloc
        move.l	4(sp), -(sp)
        dc.w	0xff48
        addq.l	#4, sp
        rts

# void *_dos_malloc0 (int, int, int);
FUNC _dos_malloc0
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), d0
        or.w	#0x8000, d0
        move.w	d0, -(sp)
        dc.w	0xff88
        lea	    10(sp), sp
        rts

# void *_dos_malloc2 (int, int);
FUNC _dos_malloc2
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xff88
        addq.l	#6, sp
        rts

# int _dos_memcpy (void *, void *, int);
FUNC _dos_memcpy
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        move.l	10(sp), -(sp)
        dc.w	0xfff7
        lea	    10(sp), sp
        rts

# int _dos_mfree (void *);
FUNC _dos_mfree
        move.l	4(sp), -(sp)
        dc.w	0xff49
        addq.l	#4, sp
        rts

# int _dos_mkdir (const char *);
FUNC _dos_mkdir
        move.l	4(sp), -(sp)
        dc.w	0xff39
        addq.l	#4, sp
        rts

# int _dos_move (const char *, const char *);
FUNC _dos_move
        move.l	8(sp), -(sp)
        move.l	8(sp), -(sp)
        dc.w	0xff86
        addq.l	#8, sp
        rts

# int _dos_nameck (const char *, struct _dos_nameckbuf *);
FUNC _dos_nameck
        move.l	8(sp), -(sp)
        move.l	8(sp), -(sp)
        dc.w	0xff37
        addq.l	#8, sp
        rts

# int _dos_namests (const char *, struct _dos_namestbuf *);
FUNC _dos_namestbuf
        move.l	8(sp), -(sp)
        move.l	8(sp), -(sp)
        dc.w	0xff29
        addq.l	#8, sp
        rts

# int _dos_newfile (const char *, _dos_mode_t);
FUNC _dos_newfile
        move.w	10(sp), -(sp)
        move.l	6(sp), -(sp)
        dc.w	0xff8b
        addq.l	#6, sp
        rts

# int _dos_nfiles (struct _dos_filbuf *);
FUNC _dos_nfiles
        move.l	4(sp), -(sp)
        dc.w	0xff4f
        addq.l	#4, sp
        rts

# int _dos_open (const char *, int);
FUNC _dos_open
        move.w	10(sp), -(sp)
        move.l	6(sp), -(sp)
        dc.w	0xff3d
        addq.l	#6, sp
        rts

# int _dos_open_pr (const char *, int, int, int, int, int, struct _dos_prcctrl *, long);
FUNC _dos_open_pr
        movem.l	20(sp), d0-d1/a0-a1
        movem.l	d1/a0-a1, -(sp)
        move.w	d0, -(sp)
        move.l	32(sp), -(sp)
        move.l	32(sp), -(sp)
        move.w	34(sp), -(sp)
        move.l	30(sp), -(sp)
        dc.w	0xfff8
        lea	    28(sp), sp
        rts

# void *_dos_os_patch (unsigned int, void *);
FUNC _dos_os_patch
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xffab
        addq.l	#6, sp
        rts

# int _dos_pathchk (const char *, const struct _dos_comline *, const char *);
FUNC _dos_pathchk
        movem.l	4(sp), d0-d1/a0
        movem.l	d0-d1/a0, -(sp)
        move.w	#2, -(sp)
        dc.w	0xff4b
        lea	    14(sp), sp
        rts

# void _dos_print (const char *);
FUNC _dos_print
        move.l	4(sp), -(sp)
        dc.w	0xff09
        addq.l	#4, sp
        rts

# void _dos_prnout (int);
FUNC _dos_prnout
        move.w	6(sp), -(sp)
        dc.w	0xff05
        addq.l	#2, sp
        rts

# int _dos_prnsns (void);
FUNC _dos_prnsns
        dc.w	0xff11
        rts

# void _dos_pspset (struct _dos_psp *);
FUNC _dos_pspset
        move.l	4(sp), -(sp)
        dc.w	0xff26
        addq.l	#4, sp
        rts

# void _dos_putchar (int);
FUNC _dos_putchar
        move.w	6(sp), -(sp)
        dc.w	0xff02
        addq.l	#2, sp
        rts

# int _dos_rassign (const char *);
FUNC _dos_rassign
        move.l	4(sp), -(sp)
        move.w	#4, -(sp)
        dc.w	0xff8f
        addq.l	#6, sp
        rts

# int _dos_read (int, char *, int);
FUNC _dos_read
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        dc.w	0xff3f
        lea	    10(sp), sp
        rts

# __dead void _dos_retshell (void);
FUNC _dos_retshell
	    dc.w	0xfff0

# int _dos_rmdir (const char *);
FUNC _dos_rmdir
        move.l	4(sp), -(sp)
        dc.w	0xff3a
        addq.l	#4, sp
        rts

# void *_dos_s_malloc (int, int);
FUNC _dos_s_malloc
        move.l	8(sp), -(sp)
        move.w	10(sp), -(sp)
        dc.w	0xffad
        addq.l	#6, sp
        rts

# void *_dos_s_malloc0 (int, int);
FUNC _dos_s_malloc0
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), d0
        or.w	#0x8000, d0
        move.w	d0, -(sp)
        dc.w	0xffad
        lea	    10(sp), sp
        rts

# int _dos_s_mfree (void *);
FUNC _dos_s_mfree
        move.l	4(sp), -(sp)
        dc.w	0xffae
        addq.l	#4, sp
        rts

# int _dos_s_process (int, int, int, int);
FUNC _dos_s_process
        movem.l	4(sp), d0-d1/a0-a1
        movem.l	d1/a0-a1, -(sp)
        move.w	d0, -(sp)
        dc.w	0xffaf
        lea	    14(sp), sp
        rts


# long _dos_seek (int, int, int);
FUNC _dos_seek
        move.w	14(sp), -(sp)
        move.l	10(sp), -(sp)
        move.w	12(sp), -(sp)
        dc.w	0xff42
        addq.l	#8, sp
        rts

# int _dos_send_pr (int, int, int, char *, long);
FUNC _dos_send_pr
        move.l	20(sp), -(sp)
        move.l	20(sp), -(sp)
        move.w	22(sp), -(sp)
        move.w	20(sp), -(sp)
        move.w	18(sp), -(sp)
        dc.w	0xfffd
        lea	    14(sp), sp
        rts

# int _dos_setblock (void *, int);
FUNC _dos_setblock
        move.l	8(sp), -(sp)
        move.l	8(sp), -(sp)
        dc.w	0xff4a
        addq.l	#8, sp
        rts

# int _dos_setdate (int);
FUNC _dos_setdate
        move.w	6(sp), -(sp)
        dc.w	0xff2b
        addq.l	#2, sp
        rts

# int _dos_setenv (const char *, const char *, const char *);
FUNC _dos_setenv
        movem.l	4(sp), d0-d1/a0
        movem.l	d0-d1/a0, -(sp)
        dc.w	0xff82
        lea	    12(sp), sp
        rts

# struct _dos_psp *_dos_setpdb (struct _dos_psp *);
FUNC _dos_setpdb
        move.l	4(sp), -(sp)
        dc.w	0xff80
        addq.l	#4, sp
        rts

# int _dos_settim2 (int);
FUNC _dos_settim2
        move.l	4(sp), -(sp)
        dc.w	0xff28
        addq.l	#4, sp
        rts

# int _dos_settime (int);
FUNC _dos_settime
        move.w	6(sp), -(sp)
        dc.w	0xff2d
        addq.l	#2, sp
        rts

# int _dos_sleep_pr (long);
FUNC _dos_sleep_pr
        move.l	4(sp), -(sp)
        dc.w	0xfffc
        addq.l	#4, sp
        rts

# int _dos_super (int);
FUNC _dos_super
        movea.l	(sp)+, a1
        dc.w	0xff20
        jmp	    (a1)

# void _dos_super_jsr (void (*)(void), struct _dos_dregs *, struct _dos_dregs *);
FUNC _dos_super_jsr
        movem.l	d2-d7/a2-a6, -(sp)
        move.l	48(sp), -(sp)
        movea.l	56(sp), a0	        /* inregs */
        movem.l	(a0), d0-d7/a0-a6
        dc.w	0xfff6
        move.l	a6, (sp)
        movea.l	60(sp), a6	        /* outregs */
        move.l	(sp)+, 56(a6)
        movem.l	d0-d7/a0-a5, (a6)
        movem.l	(sp)+, d2-d7/a2-a6
        rts

# int _dos_suspend_pr (int);
FUNC _dos_suspend_pr
        move.w	6(sp), -(sp)
        dc.w	0xfffb
        addq.l	#2, sp
        rts

# long _dos_time_pr (void);
FUNC _dos_time_pr
        dc.w	0xfffe
        rts

# int _dos_unlock (int, int, int);
FUNC _dos_unlock
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        move.w	#1, -(sp)
        dc.w	0xff8c
        lea	12(sp), sp
        rts

# void _dos_verify (int);
FUNC _dos_verify
        move.w	6(sp), -(sp)
        dc.w	0xff2e
        addq.l	#2, sp
        rts

# int _dos_verifyg (void);
FUNC _dos_verifyg
        dc.w	0xff84
        rts

# int __pure _dos_vernum (void);
FUNC _dos_vernum
    	dc.w	0xff30
    	rts

# int _dos_wait (void);
FUNC _dos_wait
        dc.w	0xff4d
        rts

# int _dos_write (int, const char *, int);
FUNC _dos_write
        move.l	12(sp), -(sp)
        move.l	12(sp), -(sp)
        move.w	14(sp), -(sp)
        dc.w	0xff40
        lea	10(sp), sp
        rts


# void _dos_k_insmod (int);
FUNC _dos_k_insmod
        move.w	6(sp), -(sp)
        move.w	#4, -(sp)
        dc.w	0xff24
        addq.l	#4, sp
        rts

# int _dos_k_keybit (int);
FUNC _dos_k_keybit
        move.w	6(sp), -(sp)
        move.w	#3, -(sp)
        dc.w	0xff24
        addq.l	#4, sp
        rts

# int _dos_k_keyinp (void);
FUNC _dos_k_keyinp
        clr.w	-(sp)
        dc.w	0xff24
        addq.l	#2, sp
        rts

# int _dos_k_keysns (void);
FUNC _dos_k_keysns
        move.w	#1, -(sp)
        dc.w	0xff24
        addq.l	#2, sp
        rts

# int _dos_k_sftsns (void);
FUNC _dos_k_sftsns
        move.w	#2, -(sp)
        dc.w	0xff24
        addq.l	#2, sp
        rts

# int _dos_kflushgc (void);
FUNC _dos_kflushgc
        move.w	#8, -(sp)
        dc.w	0xff0c
        addq.l	#2, sp
        rts

# int _dos_kflushgp (void);
FUNC _dos_kflushgp
        move.w	#1, -(sp)
        dc.w	0xff0c
        addq.l	#2, sp
        rts

# int _dos_kflushgs (struct _dos_inpptr *);
FUNC _dos_kflushgs
        move.l	4(sp), -(sp)
        move.w	#10, -(sp)
        dc.w	0xff0c
        addq.l	#6, sp
        rts

# int _dos_kflushin (void);
FUNC _dos_kflushin
        move.w	#7, -(sp)
        dc.w	0xff0c
        addq.l	#2, sp
        rts

# int _dos_kflushio (int);
FUNC _dos_kflushio
        move.w	6(sp), -(sp)
        move.w	#6, -(sp)
        dc.w	0xff0c
        addq.l	#4, sp
        rts
