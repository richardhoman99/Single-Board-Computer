/*
 * ems_r.c
 * Richard Homan
 * 02/17/2024
 * Run executable logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"
#include "serial-sim.h"

// no arguments
int ems_r(const char **argv, int argc)
{
	if (!has_exec)
	{
		serial_puts(noexecloadedstr, STR_SIZEOF(noexecloadedstr));
		serial_puts(nlstr, STR_SIZEOF(nlstr));
		return -1;
	}
	return exec_entry_ptr();
}
