#include "types.h"
#include "string.h"

static const char hexchars[] = "0123456789ABCDEF";

size_t strlen(const char *str) {
	const char *src = str;
	while(*src++);
	return (src - str) - 1;
}

size_t strnlen(const char *str, size_t maxlen) {
	const char *src;
	for(src = str; maxlen-- && *src != '\0'; ++src);
	return src - str;
}

static size_t skip_atoi(const char **s) {
	size_t i = 0;
	while(isdigit(**s)) {
		i = (i * 10) + *((*s)++) - '0';
	}
	return i;
}

size_t vsprintf(char *buf, const char *fmt, va_list args) {
	char tmp_buffer[12];
	char *str;
	for (str = buf; *fmt; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
		int field_width = -1;
		int precision = -1;
		size_t longint = 0;
		size_t zero_pad = 0;
		size_t left_align = 0;
		char sign = 0;
		char *s;
		
		// Process the flags
		for(;;) {
			++fmt;          // this also skips first '%'
			switch (*fmt) {
				case '-':
					left_align = 1;
					continue;
				case '+':
					sign = '+';
					continue;
				case ' ':
					if (sign != '+') sign = ' ';
					continue;
				case '0':
					zero_pad = 1;
					continue;
			}
			break;
		}
		
		// Process field width and precision
		field_width = precision = -1;
		if (isdigit(*fmt)) {
			field_width = skip_atoi(&fmt);
		} else if (*fmt == '*') {
			++fmt;
			// it's the next argument
			field_width = va_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				left_align = 1;
			}
		}
		
		if (*fmt == '.') {
			++fmt;
			if (isdigit(*fmt)) {
				precision = skip_atoi(&fmt);
			} else if (*fmt == '*') {
				++fmt;
				// it's the next argument
				precision = va_arg(args, int);
			}
			if (precision < 0) {
				precision = 0;
			}
		}
		
		if (*fmt == 'h') ++fmt;
		if ((*fmt == 'l') || (*fmt == 'L')) {
			longint = 1;
			++fmt;
		}
		if (left_align) {
			zero_pad = 0;
		}
		switch (*fmt) {
			case 'c': {
				if (!left_align) {
					while (--field_width > 0) {
						*str++ = ' ';
					}
				}
				*str++ = (char) va_arg(args, int);
				while (--field_width > 0) {
					*str++ = ' ';
				}
				continue;
			}
			case 's': {
				s = va_arg(args, char*);
				if (!s) {
					s = "<NULL>";
				}
				size_t len = strnlen(s, precision);
				if (!left_align) {
					while (len < field_width--) {
						*str++ = ' ';
					}
				}
				for (size_t i = 0; i < len; ++i) {
					*str++ = *s++;
				}
				while (len < field_width--) {
					*str++ = ' ';
				}
				continue;
			}
			
			case 'p':
				longint = 1;
				if (field_width == -1) {
					field_width = 2 * sizeof(void *);
					zero_pad = 1;
				} /* fallthrough */
			case 'x':
			case 'X': {
				s = &tmp_buffer[12];
				*--s = 0;
				uint32 num = longint ? va_arg(args, uint32) : va_arg(args, uint16);
				if (!num) {
					*--s = '0';
				}
				while (num) {
					*--s = hexchars[num & 0xF];
					num >>= 4;
				}
				sign = 0;
				break;
			}
			case 'n': {
				int *ip = va_arg(args, int * );
				*ip = (str - buf);
				continue;
			}
			case 'u': {
				s = &tmp_buffer[12];
				*--s = 0;
				uint32 num = longint ? va_arg(args, uint32) : va_arg(args, uint16);
				if (!num) {
					*--s = '0';
				}
				while (num) {
					*--s = (num % 10) + 0x30;
					num /= 10;
				}
				sign = 0;
				break;
			}
			case 'd':
			case 'i': {
				s = &tmp_buffer[12];
				*--s = 0;
				int num = longint ? va_arg(args, int) : va_arg(args, int16);
				if (!num) {
					*--s = '0';
				}
				if (num < 0) {
					sign = '-';
					while (num) {
						*--s = 0x30 - (num % 10);
						num /= 10;
					}
				} else {
					while (num) {
						*--s = (num % 10) + 0x30;
						num /= 10;
					}
				}
				break;
			}
			default: continue;
		}
		
		size_t len = strnlen(s, precision);
		if (sign) {
			*str++ = sign;
			field_width--;
		}
		if (!left_align) {
			if (zero_pad) {
				while(len < field_width--)
					*str++ = '0';
			} else {
				while(len < field_width--)
					*str++ = ' ';
			}
		}
		for (size_t i = 0; i < len; ++i) {
			*str++ = *s++;
		}
		while(len < field_width--) {
			*str++ = ' ';
		}
	}
	
	*str = '\0';
	return str - buf;
}

size_t sprintf(char *buffer, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	size_t i = vsprintf(buffer, fmt, args);
	va_end(args);
	return i;
}
