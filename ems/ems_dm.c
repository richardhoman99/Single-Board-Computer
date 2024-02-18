/*
 * ems_dm.c
 * Richard Homan
 * 02/17/2024
 * Dump memory logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"
#include "convert.h"

// argv[0] = address, argv[1] = n lines of 16 bytes
int ems_dm(const char **argv, int argc)
{
	char *saddr, *slen;
	char header[7];
	char sbyte[4];
	word addr, len;
	register word i, j;

	saddr = argv[0];
	slen = argv[1];

	addr = 0;
	for (i = 0; i < 2; i++)
	{
		j = ahtob(&(saddr[i*2]));
		if (j == -1)
			return -1;
		addr = (addr << 8) | (j & 0xff);
	}

	len = ahtob(slen);
	if (len == -1)
		return -1;

	header[4] = ':';
	header[5] = ' ';
	header[6] = 0;
	sbyte[2] = ' ';
	sbyte[3] = 0;

	addr -= addr % 16;
	for (i = 0; i < len; i++)
	{
		btoah(addr >> 8, &(header[0]));
		btoah(addr & 0xff, &(header[2]));
		serial_puts(header, 7);

		for (j = 0; j < 16; j++)
		{
			btoah(*(byte *)((lword)addr & 0xffff), sbyte);
			serial_puts(sbyte, 4);
			addr++;
		}

		serial_putc('\r');
		serial_putc('\n');
	}

	return 0;
}

