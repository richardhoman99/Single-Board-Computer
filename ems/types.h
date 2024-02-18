/*
 * types.h
 * Richard Homan
 * 02/11/2024
 * Refer to units as byte, word, and longword for m68k language
 */

#ifndef TYPES_H
#define TYPES_H

typedef char byte;
typedef short word;
typedef int lword;

typedef unsigned char ubyte;
typedef unsigned short uword;
typedef unsigned int ulword;

#define ARR_LEN(a) sizeof(a)/sizeof(a[0])

#endif
