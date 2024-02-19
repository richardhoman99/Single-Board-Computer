/*
 * main.c
 * Richard Homan
 * 02/11/2024
 * Entry point for Enemigo Monitor System
 */

#include "types.h"
#include "convert.h"
#include "serial-sim.h"
#include "command.h"
#include "exec.h"

#define INBUF_LEN 16
#define ARG_MAX 3

const char welcome_str[] = "Enemigo Monitor System";

const char parse_err_str[] = "error parsing arguments";
const char inv_comm_str[] = "unknown command";
const char bad_arg_str[] = "bad argument";
const char noexecload_str[] = "no executable loaded";

const char pmt_str[] = "ems% ";

const char del_str[] = " \b\b \b";
const char cur_str[] = "_\b";
const char nl_str [] = "\r\n";
const char err_str[] = "error ";

static char inbuf[INBUF_LEN];
static int inbuf_len;
static char *argv[ARG_MAX];
static int argc;

byte has_exec;
int (*exec_entry_ptr)(void);

int main(void)
{
	char inchar;
	int r;
	command_func command;

	has_exec = 0;

mpmt:
	inbuf_len = 0;
	serial_puts(pmt_str, ARR_LEN(pmt_str));
	serial_puts(cur_str, ARR_LEN(cur_str));

mwaitc:
	while (!serial_isc()) // wait for next character
		__asm__ __volatile__ ("nop");

	inchar = serial_getc();
	if (inchar == '\r') // on return key
	{
		inbuf[inbuf_len++] = ' ';
		inbuf[inbuf_len++] = '\0'; // add null terminator
		serial_puts(del_str, ARR_LEN(del_str));
		goto meval;
	}
	if (inchar == '\b') // on delete key
	{
		if (inbuf_len != 0)
		{
			inbuf_len--;
			serial_puts(del_str, ARR_LEN(del_str));
		}
	}
	else // any other input
	{
		if(inbuf_len >= INBUF_LEN-1) // buffer overflow protection
		{							 // sub 2 because we add '\0' at end
			serial_puts(del_str, ARR_LEN(cur_str)); // eat char off terminal
		}
		else
		{
			inbuf[inbuf_len] = inchar;
			inbuf_len++;
		}
	}
	serial_puts(cur_str, ARR_LEN(cur_str));
	goto mwaitc;

meval:
	r = split_args(inbuf, inbuf_len, argv, &argc, ARG_MAX);
	if (r != 0) // inform about error and return to prompt
	{
		serial_puts(parse_err_str, ARR_LEN(parse_err_str));
		serial_puts(nl_str, ARR_LEN(nl_str));
		goto mpmt;
	}
	command = gcommand(argv[0]);
	// serial_puts(argv[0], INBUF_LEN);
	// goto mpmt;

	r = command((const char **)argv, argc);
	switch (r)
	{
	case EMS_INV_COMM:
		serial_puts(inv_comm_str, ARR_LEN(inv_comm_str));
		break;
	case EMS_BAD_ARG:
		serial_puts(bad_arg_str, ARR_LEN(bad_arg_str));
		break;
	case EMS_NO_EXEC:
		serial_puts(noexecload_str, ARR_LEN(noexecload_str));
		break;
	default:
		break;
	}
	if (r != 0)
		serial_puts(nl_str, ARR_LEN(nl_str));

	goto mpmt;

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}
