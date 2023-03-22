#ifndef _FDS_H
#define _FDS_H

#include <sys/cdefs.h>

typedef struct fdent fdent;

struct fdent {
  char * filename;
  unsigned int	flags;
};

extern fdent __fd_list[];

#define __valid_fd(fd)		(__fd_list[fd].filename == 0)
#define __fd_filename(fd)	(__fd_list[fd].filename)
#define __fd_flags(fd)		(__fd_list[fd].flags)

int	__fd_assign (int fd, const char *filename, unsigned int flags);
int	__fd_remove (int fd);
void __fd_exit_clean (void);

#endif /* _FDS_H */
