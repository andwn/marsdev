#ifndef _TYPES_H_
#define _TYPES_H_

#define NULL 0

typedef unsigned long int size_t;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;

typedef signed char int8;
typedef signed short int int16;
typedef signed long int int32;

typedef signed short int s16;
typedef unsigned short int u16;

typedef volatile unsigned char vuint8;
typedef volatile unsigned short int vuint16;
typedef volatile unsigned long int vuint32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short int vu16;
typedef volatile unsigned long int vu32;

typedef volatile signed char vint8;
typedef volatile signed short int vint16;
typedef volatile signed long int vint32;

#define abs(n) ((n)<0?-(n):(n))

#endif /* _TYPES_H_ */
