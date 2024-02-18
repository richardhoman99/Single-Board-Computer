/*
 * ems_h.c
 * Richard Homan
 * 02/17/2024
 * Help menu logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"

const char help_str0 = "cr [reg] [val] : change register";
const char help_str1 = "cm [loc] [val] : change memory";
const char help_str2 = "dr             : dump registers";
const char help_str3 = "dm [loc] [len] : dump memory";
const char help_str4 = "l              : load srecord executable";
const char help_str5 = "r              : run srecord executable";
const char help_str6 = "h              : display this message";

const char *help_str[]
{
	help_str0,
	help_str1,
	help_str2,
	help_str3,
	help_str4,
	help_str5,
	help_str6
};

const char *help_str_len[]
{
	STR_SIZEOF(help_str0),
	STR_SIZEOF(help_str1),
	STR_SIZEOF(help_str2),
	STR_SIZEOF(help_str3),
	STR_SIZEOF(help_str4),
	STR_SIZEOF(help_str5),
	STR_SIZEOF(help_str6)
};


// no arguments
int ems_h(const char **argv, int argc)
{

}
