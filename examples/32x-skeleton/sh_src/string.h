#ifndef __STRING_H__
#define __STRING_H__

#define isdigit(c)		((c) >= '0' && (c) <= '9')

size_t strlen(const char *str);
size_t strnlen(const char *str, size_t maxlen);

#endif
