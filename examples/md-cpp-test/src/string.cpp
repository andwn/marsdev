#include "string.hpp"

uint16 intToHex(uint32 value, char *str, uint16 minsize) {
    char data[10];
    char *src = &data[10];
    uint32 res = value;
    int16 left = (minsize > 8) ? 8 : minsize;
    uint16 cnt = 0;
    while (res) {
        char c = res & 0xF;
        if (c >= 10) c += ('A' - 10);
        else c += '0';
        *--src = c;
        cnt++;
        left--;
        res >>= 4;
    }
    while (left > 0) {
        *--src = '0';
        cnt++;
        left--;
    }
    char *dst = str;
    while(cnt--) *dst++ = *src++;
    *dst = 0;
    return dst - str;
}

void memcpy(void *dst, const void *src, uint32 sz) {
    uint32 dst_addr = (uint32) dst;
    uint32 src_addr = (uint32) src;

    uint8  *dst8  = (uint8 *) dst;
    uint16 *dst16 = (uint16*) dst;
    uint32 *dst32 = (uint32*) dst;

    const uint8  *src8  = (uint8 *) src;
    const uint16 *src16 = (uint16*) src;
    const uint32 *src32 = (uint32*) src;

    if((dst_addr & 1) || (src_addr & 1)) {
        // Unaligned
        while(sz--) *dst8++ = *src8++;
    } else {
        // Aligned
        if(sz & 1) dst8[sz-1] = src8[sz-1];
        sz >>= 1;
        if(sz & 1) dst16[sz-1] = src16[sz-1];
        sz >>= 1;
        while(sz--) *dst32++ = *src32++;
    }
}
