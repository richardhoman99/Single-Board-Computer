/*
 * ems_l.c
 * Richard Homan
 * 02/17/2024
 * Load record logic for Enemigo Monitor System
 */

#include "err.h"
#include "types.h"
#include "convert.h"
#include "strings.h"
#include "exec.h"
#include "lsrec.h"
#include "serial-sim.h"
#include "debug_prog.h"

#define INBUF_LEN 64
static char inbuf[INBUF_LEN];
static int inbuf_len;

// no arguments
int ems_l(const char **argv, int argc)
{
// 	char inchar;
	int r;

	lsrec_init();
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
	for (int i = 0; i < ARR_LEN(debug_prog_l); i++)
	{
		r = lsrec_in(debug_prog[i], debug_prog_l[i], &(exec_entry_ptr));
		if (r != 0)
		{
			serial_puts(err_str, ERR_STR_LEN);
			btoah(r, inbuf);
			inbuf[2] = '\0';
			serial_puts(inbuf, 2);
			serial_puts(nl_str, NL_STR_LEN);
			return r;
		}

		if (exec_entry_ptr != 0x0)
		{
			has_exec = 1;
			return 0; // found entry, exit out of loader
		}
	}
	// goto lprompt;

	// btoah(((lword)exec_entry_ptr >>  0) & 0xff, &(inbuf[6]));
	// btoah(((lword)exec_entry_ptr >>  8) & 0xff, &(inbuf[4]));
	// btoah(((lword)exec_entry_ptr >> 16) & 0xff, &(inbuf[2]));
	// btoah(((lword)exec_entry_ptr >> 24) & 0xff, &(inbuf[0]));
	// inbuf[8] = 0;
	// serial_puts(inbuf, 8);
	// serial_putc('\r');
	// serial_putc('\n');

	return 0;
}
