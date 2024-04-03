/*
 * ems_h.c
 * Richard Homan
 * 02/17/2024
 * Help menu logic for Enemigo Monitor System
 */

#include "types.h"
#include "strings.h"
#include "serial.h"

const char help_str0[] = "cr [reg] [val] : change register";
const char help_str1[] = "cm [loc] [val] : change memory";
const char help_str2[] = "dr             : dump registers";
const char help_str3[] = "dm [loc] [len] : dump memory";
const char help_str4[] = "l              : load srecord executable";
const char help_str5[] = "r              : run srecord executable";
const char help_str6[] = "h              : display this message";

const char * const help_str[] =
{
	help_str0,
	help_str1,
	help_str2,
	help_str3,
	help_str4,
	help_str5,
	help_str6
};

const int help_str_len[] =
{
	ARR_LEN(help_str0),
	ARR_LEN(help_str1),
	ARR_LEN(help_str2),
	ARR_LEN(help_str3),
	ARR_LEN(help_str4),
	ARR_LEN(help_str5),
	ARR_LEN(help_str6)
};

// no arguments
int ems_h(const char **argv, int argc)
{
	register int i;
	for (i = 0; i < ARR_LEN(help_str); i++)
	{
		serial_puts((const char *)help_str[i], (ubyte)help_str_len[i]);
		serial_puts(nl_str, NL_STR_LEN);
	}

	return 0;
}
