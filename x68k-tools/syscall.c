#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <human68k/error.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>

#include "fds.h"

int chmod(const char *path, mode_t mode) {
    /* TODO : mode = mode2dos (mode) */
    int attr = _dos_chmod (path, mode);
    if(attr < 0) {
        /* TODO : errno = errcvt (attr); */
        errno = ENOENT;
        return -1;
    }
    return 0;
}

int close(int fd) {
    if(__fd_remove(fd) < 0) return -1;
    return _dos_close(fd);
}

static inline void run_dtors() {
    typedef void (*pfunc)();
    extern pfunc __dtor_list[];
    pfunc *p = &__dtor_list[1];
    while(*p) (*p++)();
}

void exit(int status) {
    /* TODO : atexit ! */
    run_dtors();
    /* Close opened file */
    __fd_exit_clean();
    _dos_exit2(status);
}
void _exit(int status) { exit(status); }

int fork(void) {
    errno = ENOSYS;
    return -1;
}

int fstat(int fd, struct stat *st) {
    if (fd < 3) {
        st->st_mode = S_IFCHR;
        st->st_blksize = 0;
        return 0;
    } else {
        return -1;
    }
}

int getpid(void) {
    errno = ENOSYS;
    return -1;
}

struct timeval;
struct timezone;

int gettimeofday(struct timeval *ptimeval, void *ptimezone) {
    (void) ptimeval;
    (void) ptimezone;
    errno = ENOSYS;
    return -1;
}

/* 1 = stdin
 * 2 = stdout
 * 3 = stderr
 * 4 = stdaux
 * 5 = stdprn
 */
int isatty(int file) {
    return file <= 5;
}

int kill(int pid, int sig) {
    (void) pid;
    (void) sig;
    errno = ENOSYS;
    return -1;
}

int link(char *existing, char *new) {
    (void) existing;
    (void) new;
    errno = ENOSYS;
    return -1;
}

off_t lseek(int fd, off_t offset, int whence) {
    return _dos_seek (fd, offset, whence);
}

int open(const char *pathname, int flags, ...) {
    int fd;
    if (flags & (O_CREAT | O_EXCL)) {
        fd = _dos_create(pathname, flags);
    } else {
        fd = _dos_open(pathname, flags & O_ACCMODE);
    }
    flags |= O_BINARY;
    if ((fd >= 0) && (__fd_assign (fd, pathname, flags) < 0)) {
        _dos_close (fd);
        return -1;
    }
    return fd;
}

int read(int fd, const void *buf, size_t nbyte) {
    return _dos_read (fd, buf, nbyte);
}

extern caddr_t _HSTA;
extern caddr_t _HEND;
extern struct dos_psp *_PSP;
extern caddr_t _HMAX;

static inline caddr_t sbrk_err() {
    errno = ENOMEM;
    return ((caddr_t) -1);
}

caddr_t sbrk(size_t nbytes) {
    if(_HEND + nbytes < _HSTA || _HEND + nbytes > _HMAX) {
        return sbrk_err();
    }
    if(_dos_setblock(_PSP, (int) (_HEND + nbytes - (int) _PSP)) < 0) {
        return sbrk_err();
    }
    caddr_t result = (caddr_t) _HEND;
    _HEND += nbytes;
    return result;
}

int unlink(char *name) {
    (void) name;
    errno = ENOSYS;
    return -1;
}

#define TXTBUFSIZE	2048

int write (int fd, const void *buf, size_t nbyte) {
    const char *bufptr = (const char *) buf;
    if (!__valid_fd (fd)) {
        errno = EBADF;
        return -1;
    }
    if (nbyte <= 0) return 0;

    /* TODO : Test for directory fd */
    int rc = 0;
    if(__fd_flags (fd) & O_BINARY) {
        rc = _dos_write (fd, bufptr, nbyte);
        if(rc < 0) {
            errno = __doserr2e (rc);
            return -1;
        } else if(rc != (int) nbyte) {
            errno = ENOSPC;
            return -1;
        }
    } else { /* O_TEXT */
        size_t bytes_in_buf;
        char txtbuf[TXTBUFSIZE];
        char *wp;
        while(bufptr < (const char *) buf + nbyte) {
            wp = txtbuf;
            bytes_in_buf = 0;
            while(bufptr < (const char *) buf + nbyte && wp < txtbuf + TXTBUFSIZE) {
                if(*bufptr == '\n') {
                    *wp++ = '\r';
                    bytes_in_buf++;
                }
                *wp++ = *bufptr++;
                bytes_in_buf++;
            }
            rc += _dos_write(fd, txtbuf, bytes_in_buf);
        }
    }
    return rc;
}
