#include "mars.h"
#include "string.h"

size_t strlen(const char *str) {
	const char *src = str;
	while(*src++);
	return src - str - 1;
}

size_t strnlen(const char *str, size_t maxlen) {
	const char *src;
	for(src = str; maxlen-- && *src != '\0'; ++src);
	return src - str;
}
