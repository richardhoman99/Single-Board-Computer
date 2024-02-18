/*
 * lsrec.h
 * Richard Homan
 * 02/12/2024
 * Parser and loader of srec executables for Enemigo Monitor System
 */

#include "types.h"

#ifndef LSREC_H
#define LSREC_H

#define LSREC_SUCCESS 0
#define LSREC_ERR_NOT_SREC_FORMAT -1 // below minimum length, or doesn't start with 'S'
#define LSREC_ERR_UNSUPPORTED_TYPE_S2 -2
#define LSREC_ERR_UNSUPPORTED_TYPE_S3 -3
#define LSREC_ERR_UNSUPPORTED_TYPE_S4 -4
#define LSREC_ERR_UNSUPPORTED_TYPE_S6 -5
#define LSREC_ERR_UNSUPPORTED_TYPE_S7 -6
#define LSREC_ERR_UNSUPPORTED_TYPE_S8 -7
#define LSREC_ERR_ADDRESS_OUT_OF_BOUNDS -8 // valid address from 0x8000-0xffff
#define LSREC_ERR_LENGTH_NONEQUAL -9 // given srec len does not equal actual len
#define LSREC_ERR_LENGTH_EXTENDS_OUT_OF_BOUNDS -10
#define LSREC_ERR_INVALID_CHECKSUM -11 // checksum invalid
#define LSREC_ERR_RECORD_COUNT_NONEQUAL -12 // the count of S1, S2, and S3 records given in S5 is incongruent to recieved
#define LSREC_ERR_ENTRY_OUT_OF_BOUNDS -13 // entry point specified in S7, S8, or S9 is not defined in the address of the data
#define LSREC_ERR_DATA_GIVEN_AFTER_ENTRY -14 // S1, S2, S3 after S7, S8, S9
#define LSREC_ERR_INVALID_FORMAT -15 // if S5 len is not 3
#define LSREC_ERR_INVALID_HEX -16

int lsrec_begin();
// line is null terminated, last char is end of checksum byte
int lsrec_in(char *line, ubyte len);
int lsrec_end(lword *entryptr);

#endif
