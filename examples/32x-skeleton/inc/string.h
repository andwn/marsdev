#ifndef __STRING_H__
#define __STRING_H__

#define isdigit(c)      ((c) >= '0' && (c) <= '9')

typedef void *__gnuc_va_list;
typedef __gnuc_va_list va_list;

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define va_start(AP, LASTARG)                                           \
 (AP = ((__gnuc_va_list) __builtin_next_arg (LASTARG)))

#define va_end(AP)      ((void)0)

#define va_arg(AP, TYPE)                                                \
 (AP = (__gnuc_va_list) ((char *) (AP) + __va_rounded_size (TYPE)),     \
  *((TYPE *) (void *) ((char *) (AP)                                    \
                       - ((sizeof (TYPE) < __va_rounded_size (char)     \
                           ? sizeof (TYPE) : __va_rounded_size (TYPE))))))

size_t strlen(const char *str);
size_t strnlen(const char *str, size_t maxlen);
size_t vsprintf(char *buf, const char *fmt, va_list args);
size_t sprintf(char *buffer,const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));

#endif
