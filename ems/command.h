/*
 * command.h
 * Richard Homan
 * 02/17/2024
 * Command determination for Enemigo Monitor System
 */

#include "command_err.h"

#ifndef COMMAND_H
#define COMMAND_H

typedef int (*)(const char **argv, int argc) command_func;

int ems_cr(const char **argv, int argc);
int ems_cm(const char **argv, int argc);
int ems_dr(const char **argv, int argc);
int ems_dm(const char **argv, int argc);
int ems_l (const char **argv, int argc);
int ems_r (const char **argv, int argc);
int ems_h (const char **argv, int argc);

int invalid_command(const char **argv, int argc) { return EMS_INV_COMM; }

// 16 bins
// 10 = cr
// 15 = cm
// 9 = dr
// 14 = dm
// 3 = l
// 13 = r
// 7 = h
const command_func[16] =
{
	invalid_command,	// 00
	invalid_command,	// 01
	invalid_command,	// 02
	ems_l,				// 03
	invalid_command,	// 04
	invalid_command,	// 05
	invalid_command,	// 06
	ems_h,				// 07
	invalid_command,	// 08
	ems_dr,				// 09
	ems_cr,				// 10
	invalid_command,	// 11
	invalid_command,	// 12
	ems_r,				// 13
	ems_dm,				// 14
	ems_cm,				// 15
};

#endif
