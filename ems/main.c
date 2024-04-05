/*
 * main.c
 * Richard Homan
 * 02/11/2024
 * Entry point for Enemigo Monitor System
 */

#include "types.h"
#include "convert.h"
#include "command.h"
#include "exec.h"
#include "serial.h"
#include "prompt.h"
#include "strings.h"

#define REVISION "0.02"

#define INBUF_SIZE 16
#define ARG_MAX 3

const char welcome_str[] =
"Enemigo Monitor System\r\n\
r" REVISION " @ " __TIME__ " " __DATE__ "\r\n\
Designed by Richard Homan\r\n";

const char parse_err_str[]  = "error parsing arguments";
const char inv_comm_str[]   = "unknown command";
const char bad_arg_str[]    = "bad argument";
const char noexecload_str[] = "no executable loaded";

const char pmt_str[] = "ems% ";

static char inbuf[INBUF_SIZE];
static char *argv[ARG_MAX];

byte has_exec;
int (*exec_entry_ptr)(void);

int main(void)
{
	int r;
	int inbuf_len;
	int argc;
	command_func command;

	has_exec = 0;
	exec_entry_ptr = 0x0;
	serial_init();

	serial_puts(welcome_str, ARR_LEN(welcome_str));

mpmt:
	inbuf_len = user_prompt(inbuf, INBUF_SIZE, pmt_str, ARR_LEN(pmt_str), 0);

	r = split_args(inbuf, inbuf_len, argv, &argc, ARG_MAX);
	if (r != 0) // inform about error and return to prompt
	{
		serial_puts(parse_err_str, ARR_LEN(parse_err_str));
		serial_puts(nl_str, NL_STR_LEN);
		goto mpmt;
	}

	if (inbuf_len > 0)
	{
		command = gcommand(argv[0]);
		// serial_puts(argv[0], INBUF_SIZE);
		// goto mpmt;

		r = command((const char **)argv, argc);
	}
	else
		r = EMS_INV_COMM;

	switch (r)
	{
	case 0:
		break;
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
		serial_puts(err_str, ERR_STR_LEN);
		btoah((byte)(r & 0xff), &(inbuf[0]));
		serial_puts(inbuf, 2);
		break;
	}
	if (r != 0)
		serial_puts(nl_str, NL_STR_LEN);

	goto mpmt; // never exit

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}

__attribute__ ((interrupt_handler))
void __access_error(void)
{
	serial_putc('~');

	while (1) // infinite loop trap
		__asm__ __volatile__ ("nop");
}
