/*
 * main.c
 * Richard Homan
 * 03/22/2024
 * Entry point for DUART test
 */

#include "types.h"
#include "serial.h"
#include "convert.h"

#define ARRLEN(s) sizeof(s)/sizeof(s[0])

const char str1[] = "I like pie!!";
// const char str2[] = "Bob";
// const char str3[] = "Microprocessor System Design";

// const char *str_ptrs[] = { str1, str2, str3 };
// const int   str_lens[] = { ARRLEN(str1), ARRLEN(str2), ARRLEN(str3) };

char inbuf[8];

int main(void)
{
	register int i,r;
	// char c;

	serial_init();

	// r = btoah((int)str1 & 0xff, &(inbuf[6]));
	// r = btoah(((int)str1 >> 8) & 0xff, &(inbuf[4]));
	// r = btoah(((int)str1 >> 16) & 0xff, &(inbuf[2]));
	// r = btoah(((int)str1 >> 24) & 0xff, &(inbuf[0]));
	// inbuf[8] = '\n';
	// inbuf[9] = '\0';

	// for (i = 0; i < 9; i++)
	// {
	// 	serial_putc(inbuf[i]);
	// }

	serial_puts(str1, ARRLEN(str1));

	// i = 0;
	// while (1)
	// {
	// 	for (register int j = 0; j < 10000; j++) ; // delay

	// 	for (i = 0; i < ARRLEN(str1); i++)
	// 	{
	// 		c = str1[i];
	// 		if (c != '\0') break;

	// 		serial_putc(c);
	// 	}
	// 	// for (register int j = 0; j < 500000; j++) ; // delay

	// 	// serial_puts(str_ptrs[i], (ubyte)str_lens[i]);
	// 	// i = (i+1) % 3;
	// 	// i++;
	// 	// if (i >= 3) i = 0;
	// }

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}

__attribute__ ((interrupt_handler))
void __access_error(void)
{
	const int d = 0x55;
	int *i;
	i = (int *)0x10000;
	*i = d;

	return;
}
