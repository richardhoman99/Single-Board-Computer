/*
 * main.c
 * Richard Homan
 * 03/22/2024
 * Entry point for DUART test
 */

#include "serial.h"

int main(void)
{
	serial_init();

	// while (!serial_isc())
	// 	serial_putc(serial_getc());

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}

void __access_error(void)
{
	const int d = 0x55;
	int *i;
	i = (int *)0x10000;
	*i = d;

	return;
}
