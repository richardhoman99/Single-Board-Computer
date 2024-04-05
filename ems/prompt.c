/*
 * prompt.c
 * Richard Homan
 * 04/03/2024
 * String input prompt routine for Enemigo Monitor System
 */

#include "strings.h"
#include "serial.h"
#include "convert.h"

int user_prompt(char *inbuf,		 int inbuf_size,
				const char *pmt_str, int pmt_str_len,
				char escc)
{
	int inbuf_len;
	char inchar;

	inbuf_len = 0;
	serial_puts(pmt_str, pmt_str_len);
#ifdef SIM
	serial_puts(cur_str, CUR_STR_LEN);
#endif

waitc:
	while (!serial_isc()) // wait for next character
		__asm__ __volatile__ ("nop");

	inchar = serial_getc();
	if (inchar == escc)
	{
		serial_puts(nl_str, NL_STR_LEN);
		return 0;
	}
	if (inchar == '\r') // on return key
	{
		inbuf[inbuf_len++] = ' ';
		inbuf[inbuf_len]   = '\0'; // add null terminator
	#ifndef SIM
		serial_puts(nl_str, NL_STR_LEN);
	#endif
		inbuf[inbuf_len] = '\0'; // add null terminator
		return inbuf_len;
	}
	if (inchar == '\x7f' || inchar == '\b') // on delete or backspace key
	{
		if (inbuf_len > 0)
		{
			inbuf_len--;
			serial_puts(del_str, DEL_STR_LEN);
		}
	}
	else // any other input
	{
		if (inbuf_len < inbuf_size-1)	// buffer overflow protection
		{								// sub 1 because we add '\0' at end
			inbuf[inbuf_len] = inchar;
			inbuf_len++;
		#ifndef SIM
			serial_putc(inchar);
			// btoah(inchar, &(inbuf[0]));
			// inbuf[2] = '\0';
			// serial_puts(inbuf, 2);
			// inbuf_len = 0;
		#endif
		}
		else // prevent overflow
		{
		#ifdef SIM
			serial_putc(del_str, DEL_STR_LEN); // eat char off terminal
		#endif
		}
	}
#ifdef SIM
	serial_puts(cur_str, CUR_STR_LEN);
#endif
	goto waitc;
}
