/*
 * convert.h
 * Richard Homan
 * 02/11/2024
 * Numerical <-> ASCII conversion utility
 */

#include "types.h"

// ascii hex to byte (-1 on error)
int ahtob(const char *in, ubyte *ret);
// word to ascii hex
int btoah(byte in, char *ret);
