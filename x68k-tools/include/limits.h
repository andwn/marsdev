#ifndef _LIBC_LIMITS_H_
#define _LIBC_LIMITS_H_	1

#define MB_LEN_MAX    2

/* Number of bits in a `char'.  */
#define CHAR_BIT 8

/* Minimum and maximum values a `signed char' can hold.  */
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127

/* Maximum value an `unsigned char' can hold.  (Minimum is 0).  */
#define UCHAR_MAX 255

/* Minimum and maximum values a `char' can hold.  */
#define CHAR_MIN (-128)
#define CHAR_MAX 127

/* Minimum and maximum values a `signed short int' can hold.  */
#define SHRT_MIN (-32767-1)
#define SHRT_MAX 32767

/* Maximum value an `unsigned short int' can hold.  (Minimum is 0).  */
#define USHRT_MAX 65535

/* Minimum and maximum values a `signed int' can hold.  */
#ifndef __INT_MAX__
#define __INT_MAX__ 2147483647
#endif
#define INT_MIN (-INT_MAX-1)
#define INT_MAX __INT_MAX__

/* Maximum value an `unsigned int' can hold.  (Minimum is 0).  */
#define UINT_MAX (INT_MAX * 2U + 1)

/* Minimum and maximum values a `signed long int' can hold.
   (Same as `int').  */
#ifndef __LONG_MAX__
#define __LONG_MAX__ 2147483647L
#endif
#define LONG_MIN (-LONG_MAX-1)
#define LONG_MAX __LONG_MAX__

/* Maximum value an `unsigned long int' can hold.  (Minimum is 0).  */
#define ULONG_MAX (LONG_MAX * 2UL + 1)

#ifndef __LONG_LONG_MAX__
#define __LONG_LONG_MAX__ 9223372036854775807LL
#endif

#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/* Minimum and maximum values a `signed long long int' can hold.  */
#define LLONG_MIN (-LLONG_MAX-1)
#define LLONG_MAX __LONG_LONG_MAX__

/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0).  */
#define ULLONG_MAX (LLONG_MAX * 2ULL + 1)

#endif

#if defined (__GNU_LIBRARY__) ? defined (__USE_GNU) : !defined (__STRICT_ANSI__)

/* Minimum and maximum values a `signed long long int' can hold.  */
#define LONG_LONG_MIN (-LONG_LONG_MAX-1)
#define LONG_LONG_MAX __LONG_LONG_MAX__

/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0).  */
#define ULONG_LONG_MAX (LONG_LONG_MAX * 2ULL + 1)

#endif

#ifndef __STRICT_ANSI__

#define _POSIX_ARG_MAX		4096	/* max bytes for an exec function */
#define _POSIX_CHILD_MAX	6	/* max simultaneous processes */
#define _POSIX_LINK_MAX		1	/* max file link count */
#define _POSIX_MAX_CANON	255	/* max bytes in term canon input line */
#define _POSIX_MAX_INPUT	255	/* max bytes in terminal input */
#define _POSIX_NAME_MAX		22	/* max bytes in a file name */
#define _POSIX_NGROUPS_MAX	0	/* max supplemental group id's */
#define _POSIX_OPEN_MAX		12	/* max open files per process */
#define _POSIX_PATH_MAX		127	/* max bytes in pathname */
#define _POSIX_PIPE_BUF		512	/* max bytes for atomic pipe writes */

#define ARG_MAX			_POSIX_ARG_MAX
#define CHILD_MAX		_POSIX_CHILD_MAX
#define LINK_MAX		_POSIX_LINK_MAX
#define MAX_CANON		_POSIX_MAX_CANON
#define MAX_INPUT		_POSIX_MAX_INPUT
#define NAME_MAX		_POSIX_NAME_MAX
#define NGROUPS_MAX		_POSIX_NGROUPS_MAX
#ifndef OPEN_MAX
#define OPEN_MAX		_POSIX_OPEN_MAX
#endif
#define PATH_MAX		_POSIX_PATH_MAX
#define PIPE_BUF		_POSIX_PIPE_BUF

#endif	/* !__STRICT_ANSI__ */

#endif	 /* !_LIBC_LIMITS_H_ */

