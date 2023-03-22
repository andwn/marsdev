#ifndef _HUMAN68K_ERROR_H
#define _HUMAN68K_ERROR_H

#include <sys/cdefs.h>

/* These are Human68K error codes */
#define NO_ERROR			        0
#define ERROR_INVALID_FUNCTION		1
#define ERROR_FILE_NOT_FOUND		2
#define ERROR_PATH_NOT_FOUND		3
#define ERROR_TOO_MANY_OPEN_FILES	4
#define ERROR_ACCESS_DENIED		    5
#define ERROR_INVALID_HANDLE		6
#define ERROR_ARENA_TRASHED		    7
#define ERROR_NOT_ENOUGH_MEMORY		8
#define ERROR_INVALID_BLOCK		    9
#define ERROR_BAD_ENVIRONMENT		10
#define ERROR_BAD_FORMAT		    11
#define ERROR_INVALID_ACCESS		12
#define ERROR_BAD_PATHNAME		    13
#define ERROR_INVALID_PARAMETER		14
#define ERROR_INVALID_DRIVE		    15
#define ERROR_CURRENT_DIRECTORY		16
#define ERROR_INVALID_CATEGORY		17	/* Device is not IOCTL capable */
#define ERROR_NO_MORE_FILES		    18
#define ERROR_WRITE_PROTECT		    19
#define ERROR_ALREADY_EXISTS		20	/* Directory exists */
#define ERROR_DIR_NOT_EMPTY		    21
#define ERROR_CANNOT_RENAME		    22
#define ERROR_DISK_FULL			    23
#define ERROR_DIRECTORY_FULL		24
#define ERROR_SEEK			        25
#define ERROR_MULTIPLE_SUPERVISOR	26
#define ERROR_THREAD_NAME_EXIST		27
#define ERROR_NO_SIGNAL_SENT		28
#define ERROR_THREAD_FULL		    29
/* 30,31 Reserved */
#define ERROR_SHARING_BUFFER_EXCEEDED   32
#define ERROR_LOCK_VIOLATION		33
#define ERROR_WRONG_DISK		    34
#define ERROR_SYMBOLIC_LINK_LOOP	35
#define ERROR_FILE_EXISTS		    36
#define ERROR_BUFFER_OVERFLOW		37
#define ERROR_NOT_SUPPORTED		    38

extern int __doserrno;

int	__doserr2e (int error);

#endif /* _HUMAN68K_ERROR_H */

