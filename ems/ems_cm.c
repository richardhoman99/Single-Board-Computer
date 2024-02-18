/*
 * ems_cm.c
 * Richard Homan
 * 02/17/2024
 * Change memory logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"
#include "convert.h"

// argv[0] = addres, argv[1] = value
int ems_cm(const char **argv, int argc)
{
	char *saddr, *sval;
	word addr, val;
	register word i, j;

	saddr = argv[0];
	sval = argv[1];

	addr = 0;
	val = 0;
	for (i = 0; i < 2; i++)
	{
		j = ahtob(&(saddr[i*2]));
		if (j == -1)
			return -1;
		addr = (addr << 8) | (j & 0xff);
	}

	val = ahtob(sval);
	if (val == -1)
		return -1;

	*(byte *)((lword)addr & 0xffff) = val;

	return 0;
}
