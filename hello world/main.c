/*
 * main.c
 * Richard Homan
 * 02/17/2024
 * Entry point for Hello, world! program
 */

#include "serial-sim.h"

#define ARR_LEN(v) sizeof(v)/sizeof(v[0])

const char hello_str[] = "VADIUM BLAYT";
const char nl_str[] = "\r\n";

int main(void)
{
	serial_puts(hello_str, ARR_LEN(hello_str));
	serial_puts(nl_str, ARR_LEN(nl_str));
	return 0;
}