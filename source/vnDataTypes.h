/* 'vnDataTypes.h' */

#ifndef _VNDATATYPES_H
#define _VNDATATYPES_H

typedef char              vnInt8;
typedef unsigned char     vnUInt8;
typedef short             vnInt16;
typedef unsigned short    vnUInt16;
typedef long              vnInt32;
typedef unsigned long     vnUInt32;
typedef int               vnInt;
typedef unsigned int      vnUInt;

typedef float             vnReal32;
typedef double            vnReal64;

enum vnBool32
{
	vnFalse = 0,
	vnTrue = 1,

	vnBool32_Force32 = 0xFFFFFFFF
};

#endif
