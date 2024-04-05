/*
 * ems_r.c
 * Richard Homan
 * 02/17/2024
 * Run executable logic for Enemigo Monitor System
 */

#include "err.h"
#include "types.h"
#include "convert.h"
#include "strings.h"
#include "exec.h"
#include "serial.h"

const char exit_code_str[] = "exit status: ";

// no arguments
int ems_r(const char **argv, int argc)
{
	char n[9];
	register int i, r;

	if (!has_exec)
		return EMS_NO_EXEC;

	r = exec_entry_ptr(); // run program
	for (i = 6; i >= 0; i-=2)
	{
		btoah(r & 0xff, &(n[i]));
		r = r >> 8;
	}
	n[9] = '\0';
	serial_puts(exit_code_str, ARR_LEN(exit_code_str));
	serial_puts(n, 8);
	serial_puts(nl_str, NL_STR_LEN);

	return 0;
}
