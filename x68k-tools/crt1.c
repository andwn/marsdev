#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dos.h>
#include <iocs.h>

/* From crt0 */
extern char *_ENV0;
extern struct dos_comline *_cmdline;
extern struct dos_psp *_PSP;

/* User main */
extern int main (int, char **, char **);

/* Internal */
int 	__argc;
char **	__argv;
char **	environ;
struct iocs_time __ontime;

static void setup_environ(void) {
    int env_size = *(int *) _ENV0;
    int count = 0;
    /* Determine vector size */
    char *cp = _ENV0 + sizeof(int); /* Skip env size */
    for(int i = 0; i <= env_size; i++) {
        if(!(*cp++)) count++;
    }
    /* Vectorize env */
    environ = malloc(count * sizeof(char*));
    cp = _ENV0 + sizeof(int); /* Skip env size */
    for(int i = 0; i < count; i++) {
        env_size = strlen (cp) + 1;
        environ[i] = malloc(env_size);
        strcpy (environ[i], cp);
        cp += env_size;
    }
    environ[count] = 0;
}

static void setup_arguments (void) {
    /* TODO : Allow quoted arguments (ignoring inner space). */
    int count = 1;
    char *p = _cmdline->buffer;
    while(*p) {
        /* Skip spaces */
        while((*p) && (*p == ' ')) p++;
        if(*p) count++;
        /* To end of arg */
        while((*p) && (*p != ' ')) p++;
    }
    __argv = malloc((count + 1) * sizeof(char*));

    int len = _cmdline->len + strlen (_PSP->exe_path) + strlen (_PSP->exe_name) + 1;
    p = (char *) malloc (len);
    /* Set program name */
    strcpy (p, _PSP->exe_path);
    strcat (p, _PSP->exe_name);
    __argv[0] = p;
    p += strlen (p);
    *p++ = '\0';
    /* Copy original cmdline */
    strcpy(p, _cmdline->buffer);

    count = 1;
    while (*p) {
        /* All space to \0 */
        while ((*p) && (*p == ' ')) *p++ = '\0';
        if (*p) __argv[count++] = p;
        /* To end of arg */
        while ((*p) && (*p != ' ')) p++;
    }
    __argc = count;
    __argv[count] = 0;
}

static void run_ctors(void) {
    typedef void (*pfunc)();
    extern pfunc __ctor_list[];
    pfunc *p = &__ctor_list[1];
    while(*p) (*p++)();
}

__used void __crt1_startup(void *mcb) {
    (void) mcb;
    __ontime = _iocs_ontime();
    setup_environ();
    setup_arguments();
    run_ctors();
    errno = 0;
    exit(main(__argc, __argv, environ));
}
