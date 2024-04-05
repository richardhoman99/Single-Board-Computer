/*
 * ems_l.c
 * Richard Homan
 * 02/17/2024
 * Load record logic for Enemigo Monitor System
 */

#include "err.h"
#include "convert.h"
#include "strings.h"
#include "exec.h"
#include "lsrec.h"
#include "serial.h"
#include "prompt.h"
// #include "debug_prog.h"

#define INBUF_SIZE 64
static char inbuf[INBUF_SIZE];

// no arguments
int ems_l(const char **argv, int argc)
{
	int r, inbuf_len;

	lsrec_init();

	has_exec = 0;
	exec_entry_ptr = 0x0;
	// keep accepting input until entry addr is given
	while (exec_entry_ptr == 0x0)
	{
		// no prompt string, cancel on ^C
		inbuf_len = user_prompt(inbuf, INBUF_SIZE, 0x0, 0, '\x03');
		if (inbuf_len == 0)
			return 0;

		inbuf_len--;
		r = lsrec_in(inbuf, inbuf_len, &(exec_entry_ptr));
		
		if (r != 0)
			return r;
	}

	has_exec = 1;
	// print out entry address, reuse inbuf as output
	btoah(((lword)exec_entry_ptr >>  0) & 0xff, &(inbuf[6]));
	btoah(((lword)exec_entry_ptr >>  8) & 0xff, &(inbuf[4]));
	btoah(((lword)exec_entry_ptr >> 16) & 0xff, &(inbuf[2]));
	btoah(((lword)exec_entry_ptr >> 24) & 0xff, &(inbuf[0]));
	inbuf[8] = '\0';
	serial_puts(inbuf, 8);
	serial_puts(nl_str, NL_STR_LEN);


	// for (int i = 0; i < ARR_LEN(debug_prog_l); i++)
	// {
	// 	r = lsrec_in(debug_prog[i], debug_prog_l[i], &(exec_entry_ptr));
	// 	if (r != 0)
	// 	{
	// 		serial_puts(err_str, ERR_STR_LEN);
	// 		btoah(r, inbuf);
	// 		inbuf[2] = '\0';
	// 		serial_puts(inbuf, 2);
	// 		serial_puts(nl_str, NL_STR_LEN);
	// 		return r;
	// 	}

	// 	if (exec_entry_ptr != 0x0)
	// 	{
	// 		has_exec = 1;
	// 		return 0; // found entry, exit out of loader
	// 	}
	// }

	return 0;
}
