/*
 * command.c
 * Richard Homan
 * 02/17/2024
 * Command determination for Enemigo Monitor System
 */

#include "command.h"
#include "types.h"
// #include "convert.h"
// #include "serial.h"

// 16 bins
// 10 = cr
// 15 = cm
// 9 = dr
// 14 = dm
// 3 = l
// 13 = r
// 7 = h
const command_func command_vec[16] =
{
	ems_cm,	// 00
	ems_dm,	// 01
	ems_r,	// 02
	invalid_command,	// 03
	invalid_command,	// 04
	ems_cr,	// 05
	ems_dr,	// 06
	invalid_command,	// 07
	ems_h,	// 08
	invalid_command,	// 09
	invalid_command,	// 10
	invalid_command,	// 11
	ems_l,	// 12
	invalid_command,	// 13
	invalid_command,	// 14
	invalid_command,	// 15
};

int invalid_command(const char **argv, int argc) { return EMS_INV_COMM; }

// kind of cheats. since (for this application) we don't care what happens
// to in, this function delimits the input by ' ' and then replaces the spaces
// with '\0'. this way we don't have to copy the strings and can use in
// as the storage for argv
int split_args(char *in, int len, char **argv, int *argc, int argm)
{
	register int i;
	register int next; // flag to indicate that next char is a new arg
	char c;

	*argc = 0;
	next = 1;
	for (i = 0; i < len; i++)
	{
		if (*argc > argm) // past arg max, don't parse anymore
			break;
		c = in[i];
		if (c == '\0') // found end early, break out
			break;
		if (c == ' ')
		{
			in[i] = '\0';
			next = 1;
		}
		else if (next)
		{
			argv[*argc] = &(in[i]); // set next argument
			(*argc)++;
			next = 0;
		}
	}
	// make sure that last arg is null terminated
	in[len-1] = '\0';

	return 0;
}

// performs the hashing function on the command name to get the command function
// pointer
command_func gcommand(const char *commname)
{
	char c;
	ubyte index;
	int i;
	command_func command;

	command = &invalid_command;
	c = commname[0];
	index = 0;
	i = 0;
	while (c != '\0')
	{
		index += c;
		i++;
		c = commname[i];
	}

	index = index % 16;

	command = command_vec[index];

	return command;
}
