/*
 * convert.h
 * Richard Homan
 * 02/11/2024
 * Numerical <-> ASCII conversion utility
 */

#include "types.h"

// ascii hex to byte (-1 on error)
word ahtob(char *in);
// word to ascii hex
void btoah(byte in, char *ret);
