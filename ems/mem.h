/*
 * mem.h
 * Richard Homan
 * 02/15/2024
 * Batch memory functions for Enemigo Monitor System
 */

#include "types.h"

#ifndef MEM_H
#define MEM_H

#define STRLEN(s) (sizeof(s)/sizeof(s[0]))

// returns new length of string
lword strncpy(char *dest, const char *src, lword n);

#endif
