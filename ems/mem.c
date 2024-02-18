/*
 * mem.c
 * Richard Homan
 * 02/15/2024
 * Batch memory functions for Enemigo Monitor System
 */

#include "mem.h"

lword
strncpy (char *__restrict dst0,
	const char *__restrict src0,
	lword count)
{
	char *dscan;
	const char *sscan;
	lword r = count;

	dscan = dst0;
	sscan = src0;
	while (count > 0)
	{
		--count;
		if ((*dscan++ = *sscan++) == '\0')
			break;
	}
	r -= count;
	while (count-- > 0)
		*dscan++ = '\0';

	return r;
}

