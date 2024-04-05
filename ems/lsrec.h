/*
 * lsrec.h
 * Richard Homan
 * 02/12/2024
 * Parser and loader of srec executables for Enemigo Monitor System
 */

#include "types.h"

#ifndef LSREC_H
#define LSREC_H

#define LSREC_MIN_ADDR	0x10000 // start of ram
#define LSREC_MAX_ADDR	0x20000 // start of duart

#define LSREC_SUCCESS 0
#define LSREC_ERR_NOT_SREC_FORMAT -101 // below minimum length, or doesn't start with 'S'
#define LSREC_ERR_UNSUPPORTED_TYPE_S1 -102
#define LSREC_ERR_UNSUPPORTED_TYPE_S3 -103
#define LSREC_ERR_UNSUPPORTED_TYPE_S4 -104
#define LSREC_ERR_UNSUPPORTED_TYPE_S5 -105
#define LSREC_ERR_UNSUPPORTED_TYPE_S7 -106
#define LSREC_ERR_UNSUPPORTED_TYPE_S9 -107
#define LSREC_ERR_ADDRESS_OUT_OF_BOUNDS -108 // valid address from 0x10000-0x20000
#define LSREC_ERR_LENGTH_NONEQUAL -109 // given srec len does not equal actual len
#define LSREC_ERR_LENGTH_EXTENDS_OUT_OF_BOUNDS -110
#define LSREC_ERR_INVALID_CHECKSUM -111 // checksum invalid
#define LSREC_ERR_RECORD_COUNT_NONEQUAL -112 // the count of S1, S2, and S3 records given in S5 is incongruent to recieved
#define LSREC_ERR_ENTRY_OUT_OF_BOUNDS -113 // entry point specified in S7, S8, or S9 is not defined in the address of the data
#define LSREC_ERR_DATA_GIVEN_AFTER_ENTRY -114 // S1, S2, S3 after S7, S8, S9
#define LSREC_ERR_INVALID_FORMAT -115 // if S5 len is not 3
#define LSREC_ERR_INVALID_HEX -116

// must be called before calling lsrec_in
void lsrec_init();
// line is null terminated, returns the entry function when it gets it
// recieving the entry function means the end of the srec
int lsrec_in(const char *recstr, ubyte len, int (**entry_func)(void));

#endif
