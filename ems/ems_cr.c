/*
 * ems_cr.c
 * Richard Homan
 * 02/17/2024
 * Change register logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"
#include "convert.h"

// argv[0] = register num, argv[1] = value
int ems_cr(const char **argv, int argc)
{
	char *sval;
	lword valh, vall;
	lword val;

	sval = &(argv[1][0]);
	valh = ahtob(sval);
	if (valh == -1)
		return EMS_INV_BADARG;
	sval = &(argv[1][2]);
	vall = ahtob(sval);
	if (vall == -1)
		return EMS_INV_BADARG;
	val = (valh << 8) | (vall & 0xff);
	sval = &(argv[1][4]);
	valh = ahtob(sval);
	if (valh == -1)
		return EMS_INV_BADARG;
	sval = &(argv[1][6]);
	vall = ahtob(sval);
	if (vall == -1)
		return EMS_INV_BADARG;
	val = (val << 16) | ((valh << 8) | (vall & 0xff));

	if (argv[0][0] == 'd')
	{
		switch(argv[0][1])
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
	else if (argv[0][0] == 'a')
	{
		switch(argv[0][1])
		{
		case '0':
			__asm__ ("move.l	%0,%/a0\n" :: "rm" (val) : "cc");
			break;
		case '1':
			__asm__ ("move.l	%0,%/a1\n" :: "rm" (val) : "cc");
			break;
		case'2':
			__asm__ ("move.l	%0,%/a2\n" :: "rm" (val) : "cc");
			break;
		case'3':
			__asm__ ("move.l	%0,%/a3\n" :: "rm" (val) : "cc");
			break;
		case '4':
			__asm__ ("move.l	%0,%/a4\n" :: "rm" (val) : "cc");
			break;
		case '5':
			__asm__ ("move.l	%0,%/a5\n" :: "rm" (val) : "cc");
			break;
		default:
			return -1;
		}
	}
	else
		return EMS_INV_BADARG;
	return 0;
}
