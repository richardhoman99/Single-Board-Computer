/*
 * ems_dm.c
 * Richard Homan
 * 02/17/2024
 * Dump memory logic for Enemigo Monitor System
 */

#include "err.h"
#include "types.h"
#include "convert.h"
#include "strings.h"
#include "serial.h"

// argv[1] = address, argv[2] = n lines of 16 bytes
int ems_dm(const char **argv, int argc)
{
	char header[9];
	char sbyte[4];
	ulword addr;
	byte b, len;
	register int i, j, r;

	if (argv[1][6] != '\0' ||
		argv[2][2] != '\0')
		return EMS_BAD_ARG;


	addr = 0;
	for (i = 0; i < 6; i+=2)
	{
		r = ahtob(&(argv[1][i]), &b);
		if (r != 0)
			return r;
		addr = (addr << 8) | b;
	}

	r = ahtob(argv[2], &len);
	if (r != 0)
		return r;

	header[6] = ':';
	header[7] = ' ';
	header[8] = '\0';
	sbyte[2] = ' ';
	sbyte[3] = '\0';

	addr -= addr % 16; // align to 0x10
	for (i = 0; i < len; i++)
	{
		btoah((addr >> 16) & 0xff, &(header[0]));
		btoah((addr >>  8) & 0xff, &(header[2]));
		btoah((addr >>  0) & 0xff, &(header[4]));
		serial_puts(header, ARR_LEN(header));

		for (j = 0; j < 16; j++)
		{
			btoah(*(byte *)((ulword)addr), &(sbyte[0]));
			serial_puts(sbyte, ARR_LEN(sbyte));
			addr++;
		}

		serial_puts(nl_str, NL_STR_LEN);
	}

	return 0;
}

