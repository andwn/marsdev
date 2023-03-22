#ifndef _IOCS_H
#define _IOCS_H

#include <sys/cdefs.h>
#include <sys/types.h>

typedef unsigned int iocs_color_t;

struct iocs_boxptr {
  short	x1;
  short	y1;
  short	x2;
  short	y2;
  iocs_color_t	color;
  unsigned short	linestyle;
};

struct iocs_circleptr {
  short		x;
  short		y;
  unsigned short	radius;
  iocs_color_t		color;
  short		start;
  short		end;
  unsigned short	ratio;
};

struct iocs_fillptr {
  short	x1;
  short	y1;
  short	x2;
  short	y2;
  iocs_color_t	color;
};

struct iocs_fntbuf {
  short		xl;
  short		yl;
  unsigned char	buffer[72];
};

struct iocs_getptr {
  short	x1;
  short	y1;
  short	x2;
  short	y2;
  void	*	buf_start;
  void	*	buf_end;
};

struct iocs_lineptr {
  short		x1;
  short		y1;
  short		x2;
  short		y2;
  iocs_color_t		color;
  unsigned short	linestyle;
};

struct iocs_paintptr {
  short	x;
  short	y;
  iocs_color_t	color;
  void		*buf_start;
  void		*buf_end;
} __attribute__((packed));

struct iocs_pointptr {
  short	x;
  short	y;
  iocs_color_t	color;
};

struct iocs_psetptr {
  short	x;
  short	y;
  iocs_color_t	color;
};

struct iocs_putptr {
  short	x1;
  short	y1;
  short	x2;
  short	y2;
  const void	*buf_start;
  const void	*buf_end;
};

struct iocs_symbolptr {
  short		x1;
  short		y1;
  unsigned char	*string_address;
  unsigned char	mag_x;
  unsigned char	mag_y;
  iocs_color_t		color;
  unsigned char	font_type;
  unsigned char	angle;
} __attribute__((packed));

struct iocs_regs {
  int	d0;
  int	d1;
  int	d2;
  int	d3;
  int	d4;
  int	d5;
  int	d6;
  int	d7;
  int	a1;
  int	a2;
  int	a3;
  int	a4;
  int	a5;
  int	a6;
};

struct iocs_time {
  int	sec;
  int	day;
};

struct iocs_chain {
  void		*addr;
  unsigned short	len;
} __attribute__((packed));

struct iocs_chain2 {
  void			*addr;
  unsigned short	len;
  const struct iocs_chain2 *next;
} __attribute__((packed));

struct iocs_clipxy {
  short	xs;
  short	ys;
  short	xe;
  short	ye;
};

struct iocs_patst {
  short	offsetx;
  short	offsety;
  short	shadow[16];
  short	pattern[16];
};

struct iocs_tboxptr {
  unsigned short	vram_page;
  short		x;
  short		y;
  short		x1;
  short		y1;
  unsigned short	line_style;
};

struct iocs_txfillptr {
  unsigned short	vram_page;
  short		x;
  short		y;
  short		x1;
  short		y1;
  unsigned short	fill_patn;
};

struct iocs_trevptr {
  unsigned short	vram_page;
  short		x;
  short		y;
  short		x1;
  short		y1;
};

struct iocs_xlineptr {
  unsigned short	vram_page;
  short		x;
  short		y;
  short		x1;
  unsigned short	line_style;
};

struct iocs_ylineptr {
  unsigned short	vram_page;
  short		x;
  short		y;
  short		y1;
  unsigned short	line_style;
};

struct iocs_tlineptr {
  unsigned short	vram_page;
  short		x;
  short		y;
  short		x1;
  short		y1;
  unsigned short	line_style;
};

/*
 * for SCSI calls
 */

struct iocs_readcap {
  unsigned long	block;
  unsigned long	size;
};

struct iocs_inquiry {
  unsigned char	unit;
  unsigned char	info;
  unsigned char	ver;
  unsigned char	reserve;
  unsigned char	size;
  unsigned char	buff[0];	/* actually longer */
};

extern int	_iocs_trap15 (struct iocs_regs *, struct iocs_regs *);
extern void	_iocs_abortjob (void) __attribute__((noreturn));
extern void	_iocs_abortrst (void);
extern void	_iocs_adpcmain (const struct iocs_chain *, int, int);
extern void	_iocs_adpcmaot (const struct iocs_chain *, int, int);
extern void	_iocs_adpcminp (void *, int, int);
extern void	_iocs_adpcmlin (const struct iocs_chain2 *, int);
extern void	_iocs_adpcmlot (const struct iocs_chain2 *, int);
extern void	_iocs_adpcmmod (int);
extern void	_iocs_adpcmout (const void *, int, int);
extern int	_iocs_adpcmsns (void);
extern int	_iocs_akconv (int, int) __attribute__((const));
extern int	_iocs_alarmget (int *, int *, int *);
extern int	_iocs_alarmmod (int);
extern int	_iocs_alarmset (int, int, int);
extern int	_iocs_apage (int);
extern int	_iocs_b_assign (int, int, int, const void *);
extern int	_iocs_b_badfmt (int, int, int);
extern int	_iocs_b_bpeek (const void *);
extern void	_iocs_b_bpoke (void *, int);
extern void	_iocs_b_clr_al (void);
extern void	_iocs_b_clr_ed (void);
extern void	_iocs_b_clr_st (void);
extern int	_iocs_b_color (int);
extern int	_iocs_b_consol (int, int, int, int);
extern void	_iocs_b_curdef (void *); /*1.3/iocs.x*/
extern void	_iocs_b_curmod (int); /*1.3/iocs.x*/
extern void	_iocs_b_curoff (void);
extern void	_iocs_b_curon (void);
extern void	_iocs_b_curpat (int); /* 1.3 & iocs.x */
extern void	_iocs_b_curpat1 (void); /* 1.3 & iocs.x */
extern void	_iocs_b_del (int);
extern void	_iocs_b_down (int);
extern void	_iocs_b_down_s (void);
extern int	_iocs_b_drvchk (int, int);
extern int	_iocs_b_drvsns (int);
extern int	_iocs_b_dskini (int, const void *, int);
extern int	_iocs_b_eject (int);
extern void	_iocs_b_era_al (void);
extern void	_iocs_b_era_ed (void);
extern void	_iocs_b_era_st (void);
extern int	_iocs_b_format (int, int, int, const void *);
extern void	_iocs_b_ins (int);
extern void *	_iocs_b_intvcs (int vector, void *addr);
extern int	_iocs_b_keyinp (void);
extern int	_iocs_b_keysns (void);
extern void	_iocs_b_left (int);
extern int	_iocs_b_locate (int, int);
extern int	_iocs_b_lpeek (const void *);
extern void	_iocs_b_lpoke (void *, int);
extern void	_iocs_b_memset (void *, const void *, int);
extern void	_iocs_b_memstr (const void *, void *, int);
extern int	_iocs_b_print (const char *);
extern int	_iocs_b_putc (int);
extern int	_iocs_b_putmes (int, int, int, int, const char *);
extern int	_iocs_b_read (int, int, int, void *);
extern int	_iocs_b_readdi (int, int, int, void *);
extern int	_iocs_b_readdl (int, int, int, void *);
extern int	_iocs_b_readid (int, int, void *);
extern int	_iocs_b_recali (int);
extern void	_iocs_b_right (int);
extern void	_iocs_b_scroll (int); /* 1.3 & iocs.x */
extern int	_iocs_b_seek (int, int);
extern int	_iocs_b_sftsns (void);
extern int	_iocs_b_super (int);
extern void	_iocs_b_up (int);
extern void	_iocs_b_up_s (void);
extern int	_iocs_b_verify (int, int, int, const void *);
extern int	_iocs_b_wpeek (const void *);
extern void	_iocs_b_wpoke (void *, int);
extern int	_iocs_b_write (int, int, int, const void *);
extern int	_iocs_b_writed (int, int, int, const void *);
extern int	_iocs_bgctrlgt (int);
extern int	_iocs_bgctrlst (int, int, int);
extern int	_iocs_bgscrlgt (int, int *, int *);
extern int	_iocs_bgscrlst (int, int, int);
extern int	_iocs_bgtextcl (int, int);
extern int	_iocs_bgtextgt (int, int, int);
extern int	_iocs_bgtextst (int, int, int, int);
extern int	_iocs_bindatebcd (int);
extern int	_iocs_bindateget (void);
extern void	_iocs_bindateset (int);
extern int	_iocs_bitsns (int);
extern int	_iocs_bootinf (void) __attribute__((const));
extern int	_iocs_box (const struct iocs_boxptr *);
extern int	_iocs_cache_md (int); /* 1.3 only */
extern int	_iocs_cache_st (void); /* 1.3 only */
extern int	_iocs_circle (const struct iocs_circleptr *);
extern void	_iocs_clipput (int, int, const struct iocs_fntbuf *, const struct iocs_clipxy *);
extern int	_iocs_contrast (int);
extern int	_iocs_crtcras (const void *, int);
extern int	_iocs_crtmod (int);
extern int	_iocs_dakjob (char *);
extern int	_iocs_dateasc (int, char *);
extern int	_iocs_datebin (int);
extern int	_iocs_datecnv (const char *);
extern void	_iocs_dayasc (int, char *);
extern int	_iocs_defchr (int, int, const void *);
extern void	_iocs_densns (void);
extern int	_iocs_dmamode (void);
extern void	_iocs_dmamov_a (const struct iocs_chain *, void *, int, int);
extern void	_iocs_dmamov_l (const struct iocs_chain2 *, void *, int);
extern void	_iocs_dmamove (void *, void *, int, int);
extern int	_iocs_drawmode (int); /* 1.3 & iocs.x */
extern int	_iocs_fill (const struct iocs_fillptr *);
extern int	_iocs_fntget (int, int, struct iocs_fntbuf *);
extern void	_iocs_g_clr_on (void);
extern int	_iocs_getgrm (struct iocs_getptr *);
extern int	_iocs_gpalet (int, int);
extern int	_iocs_hanjob (char *);
extern int	_iocs_home (int, int, int);
extern int	_iocs_hsvtorgb (int, int, int) __attribute__((const));
extern int	_iocs_hsyncst (const void *);
extern int	_iocs_init_prn (int, int);
extern int	_iocs_inp232c (void);
extern void	_iocs_iplerr (void) __attribute__((noreturn));
extern int	_iocs_isns232c (void);
extern int	_iocs_jissft (int) __attribute__((const));
extern int	_iocs_joyget (int);
extern void	_iocs_ledmod (int, int);
extern int	_iocs_line (const struct iocs_lineptr *);
extern int	_iocs_lof232c (void);
extern int	_iocs_mpu_stat (void); /* 1.3 only */
extern int	_iocs_ms_curgt (void);
extern void	_iocs_ms_curof (void);
extern void	_iocs_ms_curon (void);
extern int	_iocs_ms_curst (int, int);
extern int	_iocs_ms_getdt (void);
extern void	_iocs_ms_init (void);
extern int	_iocs_ms_limit (int, int, int, int);
extern int	_iocs_ms_offtm (int, int);
extern int	_iocs_ms_ontm (int, int);
extern void	_iocs_ms_patst (int, const struct iocs_patst *);
extern void	_iocs_ms_sel (int);
extern void	_iocs_ms_sel2 (const short *);
extern int	_iocs_ms_stat (void);
extern struct iocs_time	_iocs_ontime (void);
extern int	_iocs_opmintst (const void *);
extern void	_iocs_opmset (int, int);
extern int	_iocs_opmsns (void);
extern void	_iocs_os_curof (void);
extern void	_iocs_os_curon (void);
extern int	_iocs_osns232c (void);
extern void	_iocs_out232c (int);
extern void	_iocs_outlpt (int);
extern void	_iocs_outprn (int);
extern int	_iocs_paint (struct iocs_paintptr *);
extern int	_iocs_point (const struct iocs_pointptr *);
extern int	_iocs_prnintst (const void *);
extern int	_iocs_pset (const struct iocs_psetptr *);
extern int	_iocs_putgrm (const struct iocs_putptr *);
extern int	_iocs_rmacnv (int, char *, char *);
extern int	_iocs_romver (void) __attribute__((const));
extern int	_iocs_s_cmdout (int, void *);
extern int	_iocs_s_datain (int, void *);
extern int	_iocs_s_dataout (int, void *);
extern int	_iocs_s_format (int, int);
extern int	_iocs_s_inquiry (int, int, struct iocs_inquiry *);
extern int	_iocs_s_msgin (void *);
extern int	_iocs_s_msgout (void *);
extern int	_iocs_s_pamedium (int, int);
extern int	_iocs_s_phase (void);
extern int	_iocs_s_read (int, int, int, int, void *);
extern int	_iocs_s_readcap (int, struct iocs_readcap *);
extern int	_iocs_s_readext (int, int, int, int, void *);
extern int	_iocs_s_reassign (int, int, void *);
extern int	_iocs_s_request (int, int, void *);
extern void	_iocs_s_reset (void);
extern int	_iocs_s_rezerounit (int);
extern int	_iocs_s_seek (int, int);
extern int	_iocs_s_select (int);
extern int	_iocs_s_startstop (int, int);
extern int	_iocs_s_stsin (void *);
extern int	_iocs_s_testunit (int);
extern int	_iocs_s_write (int, int, int, int, void *);
extern int	_iocs_s_writeext (int, int, int, int, void *);
extern void	_iocs_scroll (int, int, int);
extern int	_iocs_set232c (int);
extern int	_iocs_sftjis (int) __attribute__((const));
extern int	_iocs_skey_mod (int, int, int);
extern void	_iocs_skeyset (int);
extern int	_iocs_snsprn (void);
extern int	_iocs_sp_cgclr (int);
extern int	_iocs_sp_defcg (int, int, const void *);
extern int	_iocs_sp_gtpcg (int, int, void *);
extern int	_iocs_sp_init (void);
extern void	_iocs_sp_off (void);
extern int	_iocs_sp_on (void);
extern int	_iocs_sp_reggt (int, int *, int *, int *, int *);
extern int	_iocs_sp_regst (int, int, int, int, int, int);
extern int	_iocs_spalet (int, int, int);
extern int	_iocs_symbol (const struct iocs_symbolptr *);
extern void	_iocs_tcolor (int);
extern void	_iocs_textget (int, int, struct iocs_fntbuf *);
extern void	_iocs_textput (int, int, const struct iocs_fntbuf *);
extern int	_iocs_tgusemd (int, int);
extern int	_iocs_timeasc (int, char *);
extern int	_iocs_timebcd (int);
extern int	_iocs_timebin (int);
extern int	_iocs_timecnv (const char *);
extern int	_iocs_timeget (void);
extern int	_iocs_timerdst (const void *, int, int);
extern void	_iocs_timeset (int);
extern int	_iocs_tpalet (int, int);
extern int	_iocs_tpalet2 (int, int);
extern void	_iocs_tvctrl (int);
extern void	_iocs_txbox (const struct iocs_tboxptr *);
extern void	_iocs_txfill (const struct iocs_txfillptr *);
extern void	_iocs_txline (struct iocs_tlineptr); /* 1.3 & iocs.x */
extern void	_iocs_txrascpy (int, int, int);
extern void	_iocs_txrev (const struct iocs_trevptr *);
extern void	_iocs_txxline (const struct iocs_xlineptr *);
extern void	_iocs_txyline (const struct iocs_ylineptr *);
extern int	_iocs_vdispst (const void *, int, int);
extern int	_iocs_vpage (int);
extern int	_iocs_window (int, int, int, int);
extern int	_iocs_wipe (void);

#endif /* _IOCS_H */
