/*
 * ems_l.c
 * Richard Homan
 * 02/17/2024
 * Load record logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"
#include "convert.h"
#include "lsrec.h"
#include "serial-sim.h"
#include "debug_prog.h"

// no arguments
int ems_l(const char **argv, int argc)
{
// 	char inchar;
	int r;

	r = lsrec_begin();
	if (r != 0)
		return -1;
// lprompt:
// 	inbuf_len = 0;
// 	serial_puts(cursor, 3);
// lwaitc:
// 	while (!serial_isc())
// 		__asm__ __volatile__ ("nop");
// 	inchar = serial_getc();
// 	if (inchar == 3) // ctrl c
// 	{
// 		serial_putc('\r');
// 		serial_putc('\n');
// 		return 0;
// 	}
// 	else if (inchar == 8)
// 	{
// 		if (inbuf_len != 0)
// 		{
// 			inbuf_len--;
// 			serial_puts(delete, 6);
// 		}
// 	}
// 	else if (inchar == '\r')
// 	{
// 		inbuf[inbuf_len] = 0;
// 		serial_puts(delete, 6);
// 		goto leval;
// 	}
// 	else
// 	{
// 		inbuf[inbuf_len] = inchar;
// 		inbuf_len++;
// 	}
// 	serial_puts(cursor, 3);
// 	goto lwaitc;

leval:
	// inbuf[inbuf_len] = 0;
	// r = lsrec_in(inbuf, inbuf_len);
	for (int i = 0; i < 16; i++)
	{
		r = lsrec_in(hwproglines[i], hwproglines_len[i]-1);
		if (r != 0)
		{
			serial_puts(errstr, STR_SIZEOF(errstr));
			btoah(r, inbuf);
			inbuf[2] = 0;
			serial_puts(inbuf, 2);
			serial_putc('\r');
			serial_putc('\n');
			return r;
		}
	}
	// goto lprompt;
getentry:
	r = lsrec_end(&exec_entry_ptr);
	if (r != 0)
	{
		has_exec = 0;
		return -1;
	}

	// btoah(((lword)exec_entry_ptr >>  0) & 0xff, &(inbuf[6]));
	// btoah(((lword)exec_entry_ptr >>  8) & 0xff, &(inbuf[4]));
	// btoah(((lword)exec_entry_ptr >> 16) & 0xff, &(inbuf[2]));
	// btoah(((lword)exec_entry_ptr >> 24) & 0xff, &(inbuf[0]));
	// inbuf[8] = 0;
	// serial_puts(inbuf, 8);
	// serial_putc('\r');
	// serial_putc('\n');

	has_exec = 1;
	return 0;
}
