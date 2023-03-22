#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fds.h"

fdent __fd_list[OPEN_MAX];

int __fd_assign(int fd, const char *filename, unsigned int flags) {
    if ((fd < 0) || (fd >= OPEN_MAX)) return -1;

    fdent *fdptr = &__fd_list[fd];

    memset (fdptr, 0, sizeof (fdent));

    fdptr->filename = strdup (filename);
    fdptr->flags = flags;

    return 0;
}

int __fd_remove(int fd) {
    fdent *fdptr = &__fd_list[fd];
    /* Unused fd */
    if(fdptr->filename == NULL) return -1;

    free(fdptr->filename);
    memset(fdptr, 0, sizeof (fdent));
    return 0;
}

void __fd_exit_clean(void) {
    for(int i = 5; i < OPEN_MAX; i++) close(i);
}

