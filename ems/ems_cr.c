/*
 * ems_cr.c
 * Richard Homan
 * 02/17/2024
 * Change register logic for Enemigo Monitor System
 */

#include "err.h"
#include "types.h"
#include "convert.h"
#include "serial.h"

// argv[1] = register num, argv[2] = value
int ems_cr(const char **argv, int argc)
{
	register int i, r;
	byte b;
	lword val;

	if (argv[1][2] != '\0' || // arg 1 isn't len 2
		argv[2][8] != '\0')   // arg 2 isn't len 8
		return EMS_BAD_ARG;

	val = 0;
	for (i = 0; i < 8; i+=2)
	{
		r = ahtob(&(argv[2][i]), &b);
		if (r != 0)
			return r;
		val = (val << 8) | (ubyte)b;
	}

	if (argv[1][0] == 'd')
	{
		switch(argv[1][1])
		{
		case '0':
			__asm__ ("move.l	%0,%/d0\n" :: "m" (val) : "cc");
			break;
		case '1':
			__asm__ ("move.l	%0,%/d1\n" :: "m" (val) : "cc");
			break;
		case'2':
			__asm__ ("move.l	%0,%/d2\n" :: "m" (val) : "cc");
			break;
		case'3':
			__asm__ ("move.l	%0,%/d3\n" :: "m" (val) : "cc");
			break;
		case '4':
			__asm__ ("move.l	%0,%/d4\n" :: "m" (val) : "cc");
			break;
		case '5':
			__asm__ ("move.l	%0,%/d5\n" :: "m" (val) : "cc");
			break;
		case '6':
			__asm__ ("move.l	%0,%/d6\n" :: "m" (val) : "cc");
			break;
		case '7':
			__asm__ ("move.l	%0,%/d7\n" :: "m" (val) : "cc");
			break;
		default:
			return -1;
		}
	}
	else if (argv[1][0] == 'a')
	{
		switch(argv[1][1])
		{
		case '0':
			__asm__ ("move.l	%0,%/a0\n" :: "m" (val) : "cc");
			break;
		case '1':
			__asm__ ("move.l	%0,%/a1\n" :: "m" (val) : "cc");
			break;
		case'2':
			__asm__ ("move.l	%0,%/a2\n" :: "m" (val) : "cc");
			break;
		case'3':
			__asm__ ("move.l	%0,%/a3\n" :: "m" (val) : "cc");
			break;
		case '4':
			__asm__ ("move.l	%0,%/a4\n" :: "m" (val) : "cc");
			break;
		case '5':
			__asm__ ("move.l	%0,%/a5\n" :: "m" (val) : "cc");
			break;
		default:
			return -1;
		}
	}
	else
		return EMS_BAD_ARG;
	return 0;
}
