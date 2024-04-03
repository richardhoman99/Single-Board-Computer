/*
 * ems_cm.c
 * Richard Homan
 * 02/17/2024
 * Change memory logic for Enemigo Monitor System
 */

#include "err.h"
#include "types.h"
#include "convert.h"

// argv[1] = address, argv[2] = value
int ems_cm(const char **argv, int argc)
{
	word addr;
	ubyte b, val;
	register int i, r;

	if (argv[1][6] != '\0' || // address not len 6
		argv[2][2] != '\0')   // value not len 2
		return EMS_BAD_ARG;

	addr = 0;
	val = 0;
	for (i = 0; i < 6; i+=2)
	{
		r = ahtob(&(argv[1][i]), &b);
		if (r != 0)
			return r;
		addr = (addr << 8) | b;
	}

	r = ahtob(argv[2], &b);
	if (r != 0)
		return r;
	val = b;

	*(byte *)((lword)addr & 0xffff) = val;

	return 0;
}
