#ifndef	_SYS_FCNTL_H
#define _SYS_FCNTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>

#define	_FOPEN		(-1)	/* from sys/file.h, kernel use only */
#define	_FREAD		0x001	/* read enabled */
#define	_FWRITE		0x002	/* write enabled */

#define _FCREAT		0x004	/* open with file create */
#define _FEXCL		0x008	/* error on open if file exists */
#define _FTRUNC		0x010	/* open with truncation */
#define _FTEXT		0x020	/* for compatibility with MSDOS */
#define _FBINARY	0x040	/* for compatibility with MSDOS */
#define	_FAPPEND	0x080	/* append (writes guaranteed at the end) */
/* These doesn't exist under human68K */
#define _FSYNC		0x100	/* do all writes synchronously */
#define _FNOCTTY	0x200	/* don't assign a ctty on thhis open */
#define _FNONBLOCK	0x400	/* non blocking I/O (POSIX style) */
#define _FNDELAY	_FNONBLOCK	/* non blocking I/O (4.2 style) */

#define	O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)

/* Opening flags for human68k */
#define	O_RDONLY	0x000
#define	O_WRONLY	0x001
#define	O_RDWR		0x002
#define	O_APPEND	_FAPPEND
#define	O_CREAT		_FCREAT
#define	O_TRUNC		_FTRUNC
#define	O_EXCL		_FEXCL
#define O_SYNC		_FSYNC
#define	O_NDELAY	_FNDELAY
#define	O_NONBLOCK	_FNONBLOCK
#define	O_NOCTTY	_FNOCTTY
#define O_TEXT		_FTEXT
#define O_BINARY	_FBINARY

#ifndef	_POSIX_SOURCE

/*
 * Flags that work for fcntl(fd, F_SETFL, FXXXX)
 */
#define	FAPPEND		_FAPPEND
#define	FSYNC		_FSYNC
#define	FNDELAY		_FNDELAY

/*
 * Flags that are disallowed for fcntl's (FCNTLCANT);
 * used for opens, internal state, or locking.
 */
#define	FREAD		_FREAD
#define	FWRITE		_FWRITE

/*
 * The rest of the flags, used only for opens
 */
#define	FOPEN		_FOPEN
#define	FCREAT		_FCREAT
#define	FTRUNC		_FTRUNC
#define	FEXCL		_FEXCL
#define	FNOCTTY		_FNOCTTY
#define FTEXT		_FTEXT
#define FBINARY		_FBINARY

#endif	/* !_POSIX_SOURCE */

/* XXX close on exec request; must match UF_EXCLOSE in user.h */
#define	FD_CLOEXEC	1	/* posix */

/* fcntl(2) requests */
#define	F_DUPFD		0	/* Duplicate fildes */
#define	F_GETFD		1	/* Get fildes flags (close on exec) */
#define	F_SETFD		2	/* Set fildes flags (close on exec) */
#define	F_GETFL		3	/* Get file flags */
#define	F_SETFL		4	/* Set file flags */
#ifndef	_POSIX_SOURCE
#define	F_GETOWN 	5	/* Get owner - for ASYNC */
#define	F_SETOWN 	6	/* Set owner - for ASYNC */
#endif	/* !_POSIX_SOURCE */
#define	F_GETLK  	7	/* Get record-locking information */
#define	F_SETLK  	8	/* Set or Clear a record-lock (Non-Blocking) */
#define	F_SETLKW 	9	/* Set or Clear a record-lock (Blocking) */
#ifndef	_POSIX_SOURCE
#define	F_RGETLK 	10	/* Test a remote lock to see if it is blocked */
#define	F_RSETLK 	11	/* Set or unlock a remote lock */
#define	F_CNVT 		12	/* Convert a fhandle to an open fd */
#define	F_RSETLKW 	13	/* Set or Clear remote record-lock(Blocking) */
#endif	/* !_POSIX_SOURCE */

/* fcntl(2) flags (l_type field of flock structure) */
#define	F_RDLCK		1	/* read lock */
#define	F_WRLCK		2	/* write lock */
#define	F_UNLCK		3	/* remove lock(s) */
#ifndef	_POSIX_SOURCE
#define	F_UNLKSYS	4	/* remove remote locks for a given system */
#endif	/* !_POSIX_SOURCE */

/* file segment locking set data type - information passed to system by user */
struct flock {
  short	l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
  short	l_whence;	/* flag to choose starting offset */
  long	l_start;	/* relative offset, in bytes */
  long	l_len;		/* length, in bytes; 0 means lock to EOF */
  short	l_pid;		/* returned with F_GETLK */
  short	l_xxx;		/* reserved for future use */
};

#ifndef	_POSIX_SOURCE
/* extended file segment locking set data type */
struct eflock {
  short	l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
  short	l_whence;	/* flag to choose starting offset */
  long	l_start;	/* relative offset, in bytes */
  long	l_len;		/* length, in bytes; 0 means lock to EOF */
  short	l_pid;		/* returned with F_GETLK */
  short	l_xxx;		/* reserved for future use */
  long	l_rpid;		/* Remote process id wanting this lock */
  long	l_rsys;		/* Remote system id wanting this lock */
};
#endif	/* !_POSIX_SOURCE */


#include <sys/types.h>
#include <sys/stat.h>		/* sigh. for the mode bits for open/creat */

extern int open /*_PARAMS*/ (const char *, int, ...);
extern int creat /*_PARAMS*/ (const char *, mode_t);
extern int fcntl /*_PARAMS*/ (int, int, ...);

/* Provide _<systemcall> prototypes for functions provided by some versions
   of newlib.  */
#ifdef _COMPILING_NEWLIB
extern int _open /*_PARAMS*/ (const char *, int, ...);
extern int _fcntl /*_PARAMS*/ (int, int, ...);
#ifdef __LARGE64_FILES
extern int _open64 /*_PARAMS*/ (const char *, int, ...);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif	/* !_SYS_FCNTL_H */

