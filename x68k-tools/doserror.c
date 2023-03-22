#include <errno.h>
#include <human68k/error.h>

/*
 * Convert Human68K DOS errors to libdos error
 */

static const char errmap[] = {
    0, ENOENT, ENOENT, ENOENT, EMFILE, EISDIR, EBADF, EFAULT,		/* 00-07 */
    ENOMEM, EFAULT, EFAULT, ENOEXEC, EINVAL, ENOENT, EINVAL, EXDEV,	/* 08-15 */
    ENOTEMPTY, EPERM, ENOENT, EACCES, EEXIST, ENOTEMPTY, EPERM, ENOSPC,	/* 16-23 */
    ENOSPC, ESPIPE, EPERM, ETXTBSY, EIO, EPERM, ENOSYS, ENOSYS,		/* 24-31 */
    ENFILE, ENOLCK, EACCES, ELOOP, EEXIST, ERANGE, ENOSYS, EEXIST		/* 32-39 */
};

/* Save the error for future use (get an associated string error) */
int __doserrno;

int __doserr2e (int error) {
    __doserrno = error;
    if ((error >= 0) && (error <= sizeof(errmap))) return errmap[error];
    return EINVAL;
}
