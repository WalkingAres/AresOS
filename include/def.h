#ifndef DEF_H
#define DEF_H

#ifndef NULL
#define NULL ((void *)0)
#endif


/* Represents true-or-false values */
//typedef int bool;

/* Explicitly-sized versions of integer types */
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

#define size_t uint32_t;

#endif