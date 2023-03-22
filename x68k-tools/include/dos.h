#ifndef _DOS_H
#define _DOS_H

#include <sys/cdefs.h>

#define _DOS_IRDONLY	0x001
#define _DOS_IHIDDEN	0x002
#define _DOS_ISYS	    0x004
#define _DOS_IFVOL	    0x008
#define _DOS_IFDIR	    0x010
#define _DOS_IFREG	    0x020
#define _DOS_IFLNK	    0x060 /* IFLNK | IFREG */
#define _DOS_IEXEC	    0x080
#define _DOS_IFMT	    0x078

#define _DOS_ISVOL(m)	(((m) & _DOS_IFMT) == _DOS_IFVOL)
#define _DOS_ISDIR(m)	(((m) & _DOS_IFMT) == _DOS_IFDIR)
#define _DOS_ISREG(m)	(((m) & _DOS_IFMT) == _DOS_IFREG)
#define _DOS_ISLNK(m)	(((m) & _DOS_IFMT) == _DOS_IFLNK)

#define _DEV_STDIN	    0x0001
#define _DEV_STDOUT	    0x0002
#define _DEV_NUL	    0x0004
#define _DEV_CLOCK	    0x0008
#define _DEV_RAW	    0x0020
#define _DEV_IOCTRL	    0x4000
#define _DEV_CDEV	    0x8000

#define _DOSE_MAX       39

#define _DOSE_ILGFNC	-1
#define _DOSE_NOENT	    -2
#define _DOSE_NODIR	    -3
#define _DOSE_MFILE	    -4
#define _DOSE_ISDIR	    -5
#define _DOSE_BADF	    -6
#define _DOSE_BROKNMEM	-7
#define _DOSE_NOMEM	    -8
#define _DOSE_ILGMPTR	-9
#define _DOSE_ILGENV	-10
#define _DOSE_ILGFMT	-11
#define _DOSE_ILGARG	-12
#define _DOSE_ILGFNAME	-13
#define _DOSE_ILGPARM	-14
#define _DOSE_ILGDRV	-15
#define _DOSE_ISCURDIR	-16
#define _DOSE_CANTIOC	-17
#define _DOSE_NOMORE	-18
#define _DOSE_RDONLY	-19
#define _DOSE_EXISTDIR	-20
#define _DOSE_NOTEMPTY	-21
#define _DOSE_CANTREN	-22
#define _DOSE_DISKFULL	-23
#define _DOSE_DIRFULL	-24
#define _DOSE_CANTSEEK	-25
#define _DOSE_SUPER	    -26
#define _DOSE_DUPTHNAM	-27
#define _DOSE_CANTSEND	-28
#define _DOSE_THFULL	-29
#define _DOSE_LCKFULL	-32
#define _DOSE_LCKERR	-33
#define _DOSE_BUSYDRV	-34
#define _DOSE_SYMLOOP	-35
#define _DOSE_FEXIST	-36	/* doseml */ 
#define _DOSE_BUFOVER	-37	/* doseml */
#define _DOSE_NOSYS	    -38	/* doseml */
#define _DOSE_ALRDYEX	-39	/* doseml */
#define _DOSE_EXISTFILE	-80

#define _BREAKCK_OFF	0
#define _BREAKCK_ON	    1
#define _BREAKCK_KILL	2
#define _BREAKCK_CHECK	-1
#define _CTRL_C_OFF	    0x0100
#define _CTRL_C_ON	    0x0101
#define _CTRL_C_CHECK	0x01ff
#define _CTRL_N_OFF	    0x0200
#define _CTRL_N_ON	    0x0201
#define _CTRL_N_CHECK	0x02ff
#define _CTRL_P_ON	    0x0301
#define _CTRL_P_OFF	    0x0300
#define _CTRL_P_CHECK	0x03ff
#define _CTRL_Q_OFF	    0x0400
#define _CTRL_Q_ON	    0x0401
#define _CTRL_Q_CHECK	0x04ff
#define _CTRL_S_OFF	    0x0500
#define _CTRL_S_ON	    0x0501
#define _CTRL_S_CHECK	0x05ff

#ifndef __dosmode_t_defined__
#define __dosmode_t_defined__
typedef int dosmode_t;
#endif

struct dos_inpptr {
	unsigned char	max;
	unsigned char	length;
	char		buffer[256];
};

struct dos_nameckbuf {
	char	drive[2];
	char	path[65];
	char	name[19];
	char	ext[5];
};

union dos_fcb {
	struct {
		unsigned char	dupcnt;
		unsigned char	devattr;
		void		*deventry;
		char		nouse_1[8];
		unsigned char	openmode;
		char		nouse_2[21];
		char		name1[8];
		char		ext[3];
		char		nouse_3;
		char		name2[10];
		char		nouse_4[38];
	} __attribute__((packed)) chr;
	struct {
		unsigned char	dupcnt;
		unsigned	mode	: 1;
		unsigned	unknown : 2;
		unsigned	physdrv : 5;
		void		*deventry;
		unsigned int	fileptr;
		unsigned int	exclptr;
		unsigned char	openmode;
		unsigned char	entryidx;
		unsigned char	clustidx;
		char		nouse_2;
		unsigned short	acluster;
		unsigned int	asector;
		void		*iobuf;
		unsigned long	dirsec;
		unsigned int	fptrmax;
		char		name1[8];
		char		ext[3];
		unsigned char	attr;
		char		name2[10];
		unsigned short	time;
		unsigned short	date;
		unsigned short	fatno;
		unsigned long	size;
		char		nouse_4[28];
	} __attribute__((packed)) blk;
};

struct dos_indos {
	unsigned short	indosf;
	unsigned char	doscmd;
	unsigned char	fat_flg;
	unsigned short	retry_count;
	unsigned short	retry_time;
	unsigned short	verifyf;
	unsigned char	breakf;
	unsigned char	ctrlpf;
	unsigned char	reserved;
	unsigned char	wkcurdrv;
};

struct dos_mep {
	void	*prev_mp;
	void	*parent_mp;
	void	*block_end;
	void	*next_mp;
};

struct dos_psp {
	char		*env;
	void		*exit;
	void		*ctrlc;
	void		*errexit;
	struct dos_comline	*comline;
	unsigned char	handle[12];
	void		*bss;
	void		*heap;
	void		*stack;
	void		*usp;
	void		*ssp;
	unsigned short	sr;
	unsigned short	abort_sr;
	void		*abort_ssp;
	void		*trap10;
	void		*trap11;
	void		*trap12;
	void		*trap13;
	void		*trap14;
	unsigned int	osflg;
	unsigned char	reserve_1[28];
	char		exe_path[68];
	char		exe_name[24];
	char		reserve_2[36];
};

struct dos_comline {
	unsigned char	len;
	char		buffer[255];
};

struct dos_namestbuf {
	unsigned char	flg;
	unsigned char	drive;
	char		path[65];
	char		name1[8];
	char		ext[3];
	char		name2[10];
};

struct dos_freeinf {
	unsigned short	free;
	unsigned short	max;
	unsigned short	sec;
	unsigned short	byte;
};

struct dos_dpbptr {
	unsigned char	drive;
	unsigned char	unit;
	unsigned short	byte;
	unsigned char	sec;
	unsigned char	shift;
	unsigned short	fatsec;
	unsigned char	fatcount;
	unsigned char	fatlen;
	unsigned short	dircount;
	unsigned short	datasec;
	unsigned short	maxfat;
	unsigned short	dirsec;
	int		driver;
	unsigned char	ide;
	unsigned char	flg;
	struct dos_dpbptr *next;
	unsigned short	dirfat;
	char		dirbuf[64];
} __attribute__((packed));

struct dos_filbuf {
	unsigned char	searchatr;
	unsigned char	driveno;
	unsigned long	dirsec;
	unsigned short	dirlft;
	unsigned short	dirpos;
	char		filename[8];
	char		ext[3];
	unsigned char	atr;
	unsigned short	time;
	unsigned short	date;
	unsigned int	filelen;
	char		name[23];
} __attribute__((packed));

struct dos_exfilbuf {
	unsigned char	searchatr;
	unsigned char	driveno;
	unsigned long	dirsec;
	unsigned short	dirlft;
	unsigned short	dirpos;
	char		filename[8];
	char		ext[3];
	unsigned char	atr;
	unsigned short	time;
	unsigned short	date;
	unsigned int	filelen;
	char		name[23];
	char		drive[2];
	char		path[65];
	char		unused[21];
} __attribute__((packed));

struct dos_dregs {
	int	d0;
	int	d1;
	int	d2;
	int	d3;
	int	d4;
	int	d5;
	int	d6;
	int	d7;
	int	a0;
	int	a1;
	int	a2;
	int	a3;
	int	a4;
	int	a5;
	int	a6;
};

struct dos_prcctrl {
	long		length;
	unsigned char	*buf_ptr;
	unsigned short	command;
	unsigned short	your_id;
};

struct dos_prcptr {
	struct dos_prcptr *next_ptr;
	unsigned char	wait_flg;
	unsigned char	counter;
	unsigned char	max_counter;
	unsigned char	doscmd;
	unsigned int	psp_id;
	unsigned int	usp_reg;
	unsigned int	d_reg[8];
	unsigned int	a_reg[7];
	unsigned short	sr_reg;
	unsigned int	pc_reg;
	unsigned int	ssp_reg;
	unsigned short	indosf;
	unsigned int	indosp;
	struct dos_prcctrl *buf_ptr;
	unsigned char	name[16];
	long		wait_time;
} __attribute__((packed));

extern void _dos_allclose (void);
extern int	_dos_bindno (const char *, const char *);
extern int	_dos_breakck (int);
extern int	_dos_c_cls_al (void);
extern int	_dos_c_cls_ed (void);
extern int	_dos_c_cls_st (void);
extern int	_dos_c_color (int);
extern int	_dos_c_curoff (void);
extern int	_dos_c_curon (void);
extern int	_dos_c_del (int);
extern int	_dos_c_down (int);
extern int	_dos_c_down_s (void);
extern int	_dos_c_era_al (void);
extern int	_dos_c_era_ed (void);
extern int	_dos_c_era_st (void);
extern int	_dos_c_fnkmod (int);
extern int	_dos_c_ins (int);
extern int	_dos_c_left (int);
extern int	_dos_c_locate (int, int);
extern int	_dos_c_print (const char *);
extern int	_dos_c_putc (int);
extern int	_dos_c_right (int);
extern int	_dos_c_up (int);
extern int	_dos_c_up_s (void);
extern int	_dos_c_width (int);
extern int	_dos_c_window (int, int);
extern void	_dos_change_pr (void);
extern int	_dos_chdir (const char *);
extern int	_dos_chgdrv (int);
extern dosmode_t	_dos_chmod (const char *, dosmode_t);
extern int	_dos_cinsns (void);
extern int	_dos_close (int);
extern int	_dos_cominp (void);
extern int	_dos_common_ck (const char *);
extern int	_dos_common_del (const char *);
extern int	_dos_common_fre (const char *, int, int, int);
extern int	_dos_common_lk (const char *, int, int, int);
extern int	_dos_common_rd (const char *, int, char *, int);
extern int	_dos_common_wt (const char *, int, const char *, int);
extern void	_dos_comout (int);
extern int	_dos_consns (void);
extern int	_dos_coutsns (void);
extern int	_dos_create (const char *, dosmode_t);
extern void	_dos_ctlabort (void) __attribute__((noreturn));
extern int	_dos_curdir (int, char *);
extern int	_dos_curdrv (void);
extern int	_dos_delete (const char *);
extern void	_dos_diskred (void *, int, int, int);
extern void	_dos_diskred2 (void *, int, int, int);
extern void	_dos_diskwrt (const void *, int, int, int);
extern void	_dos_diskwrt2 (const void *, int, int, int);
extern int	_dos_drvctrl (int, int);
extern void	_dos_drvxchg (int, int);
extern int	_dos_dskfre (int, struct dos_freeinf *);
extern int	_dos_dup (int);
extern int	_dos_dup0 (int, int);
extern int	_dos_dup2 (int, int);
extern void	_dos_errabort (void) __attribute__((noreturn));
extern int	_dos_exec2 (int, const char *, const char *, const char *);
extern int	_dos_execonly (void *);
extern int	_dos_exfiles (struct dos_exfilbuf *, const char *, int);
extern void	_dos_exit (void) __attribute__((noreturn));
extern void	_dos_exit2 (int) __attribute__((noreturn));
extern int	_dos_exnfiles (struct dos_exfilbuf *);
extern int	_dos_fatchk (const char *, unsigned short *);
extern int	_dos_fatchk2 (const char *, unsigned short *, int);
extern void	_dos_fflush (void);
extern int	_dos_fflush_set (int);
extern int	_dos_fgetc (int);
extern int	_dos_fgets (struct dos_inpptr *, int);
extern int	_dos_filedate (int, int);
extern int	_dos_files (struct dos_filbuf *, const char *, int);
extern void	_dos_fnckeygt (int, char *);
extern void	_dos_fnckeyst (int, const char *);
extern void	_dos_fputc (int, int);
extern void	_dos_fputs (const char *, int);
extern union dos_fcb *	_dos_get_fcb_adr (unsigned int);
extern int	_dos_get_pr (int, struct dos_prcptr *);
extern int	_dos_getassign (const char *, char *);
extern int	_dos_getc (void);
extern int	_dos_getchar (void);
extern int	_dos_getdate (void);
extern int	_dos_getdpb (int, struct dos_dpbptr *);
extern int	_dos_getenv (const char *, const char *, char *);
extern struct dos_psp *	_dos_getpdb (void);
extern int	_dos_gets (struct dos_inpptr *);
extern int	_dos_getss (struct dos_inpptr *);
extern int	_dos_gettim2 (void);
extern int	_dos_gettime (void);
extern void	_dos_hendspic (int);
extern int	_dos_hendspio (void);
extern int	_dos_hendspip (int, const char *);
extern int	_dos_hendspir (int, const char *);
extern void	_dos_hendspmc (void);
extern int	_dos_hendspmo (void);
extern int	_dos_hendspmp (int, const char *);
extern int	_dos_hendspmr (int, const char *);
extern void	_dos_hendspsc (void);
extern int	_dos_hendspso (void);
extern int	_dos_hendspsp (int, const char *);
extern int	_dos_hendspsr (int, const char *);
extern struct dos_indos *	_dos_indosflg (void);
extern int	_dos_inkey (void);
extern int	_dos_inpout (int);
extern void *	_dos_intvcg (int);
extern void *	_dos_intvcs (int, void *);
extern int	_dos_ioctrldvctl (int, int, char *);
extern int	_dos_ioctrldvgt (int);
extern int	_dos_ioctrlfdctl (int, int, char *);
extern int	_dos_ioctrlfdgt (int);
extern int	_dos_ioctrlgt (int);
extern int	_dos_ioctrlis (int);
extern int	_dos_ioctrlos (int);
extern int	_dos_ioctrlrd (int, char *, int);
extern int	_dos_ioctrlrh (int, char *, int);
extern int	_dos_ioctrlrtset (int, int);
extern int	_dos_ioctrlst (int, int);
extern int	_dos_ioctrlwd (int, const char *, int);
extern int	_dos_ioctrlwh (int, const char *, int);
extern void	_dos_k_insmod (int);
extern int	_dos_k_keybit (int);
extern int	_dos_k_keyinp (void);
extern int	_dos_k_keysns (void);
extern int	_dos_k_sftsns (void);
extern void	_dos_keeppr (int, int) __attribute__((noreturn));
extern int	_dos_keysns (void);
extern int	_dos_kflushgc (void);
extern int	_dos_kflushgp (void);
extern int	_dos_kflushgs (struct dos_inpptr *);
extern int	_dos_kflushin (void);
extern int	_dos_kflushio (int);
extern int	_dos_kill_pr (void);
extern int	_dos_load (const char *, const struct dos_comline *, const char *);
extern int	_dos_loadexec (const char *, const struct dos_comline *, const char *);
extern int	_dos_loadonly (const char *, const void *, const void *);
extern int	_dos_lock (int, int, int);
extern int	_dos_makeassign (const char *, const char *, int);
extern int	_dos_maketmp (const char *, int);
extern void *	_dos_malloc (int);
extern void *	_dos_malloc0 (int, int, int);
extern void *	_dos_malloc2 (int, int);
extern int	_dos_memcpy (void *, void *, int);
extern int	_dos_mfree (void *);
extern int	_dos_mkdir (const char *);
extern int	_dos_move (const char *, const char *);
extern int	_dos_nameck (const char *, struct dos_nameckbuf *);
extern int	_dos_namests (const char *, struct dos_namestbuf *);
extern int	_dos_newfile (const char *, dosmode_t);
extern int	_dos_nfiles (struct dos_filbuf *);
extern int	_dos_open (const char *, int);
extern int	_dos_open_pr (const char *, int, int, int, int, int, struct dos_prcctrl *, long);
extern void *	_dos_os_patch (unsigned int, void *);
extern int	_dos_pathchk (const char *, const struct dos_comline *, const char *);
extern void	_dos_print (const char *);
extern void	_dos_prnout (int);
extern int	_dos_prnsns (void);
extern void	_dos_pspset (struct dos_psp *);
extern void	_dos_putchar (int);
extern int	_dos_rassign (const char *);
extern int	_dos_read (int, const char *, int);
extern void	_dos_retshell (void) __attribute__((noreturn));
extern int	_dos_rmdir (const char *);
extern void *	_dos_s_malloc (int, int);
extern void *	_dos_s_malloc0 (int, int);
extern int	_dos_s_mfree (void *);
extern int	_dos_s_process (int, int, int, int);
extern long	_dos_seek (int, int, int);
extern int	_dos_send_pr (int, int, int, char *, long);
extern int	_dos_setblock (void *, int);
extern int	_dos_setdate (int);
extern int	_dos_setenv (const char *,const char *, const char *);
extern struct dos_psp *	_dos_setpdb (struct dos_psp *);
extern int	_dos_settim2 (int);
extern int	_dos_settime (int);
extern int	_dos_sleep_pr (long);
extern int	_dos_super (int);
extern void	_dos_super_jsr (void (*)(void), struct dos_dregs *, struct dos_dregs *);
extern int	_dos_suspend_pr (int);
extern long	_dos_time_pr (void);
extern int	_dos_unlock (int, int, int);
extern void	_dos_verify (int);
extern int	_dos_verifyg (void);
extern int	_dos_vernum (void) __attribute__((pure));
extern int	_dos_wait (void);
extern int	_dos_write (int, const char *, int);

#endif /* _DOS_H */
