/*
 * main.c
 * Richard Homan
 * 02/17/2024
 * Entry point for Hello, world! program
 */

#include "serial-sim.h"

#define STR_SIZEOF(v) sizeof(v)/sizeof(v[0])

const char hellostr[] = "Hello, world!";
#define HELLOSTR_LEN STR_SIZEOF(hellostr)

const char nlstr[] = "\r\n";
#define NLSTR_LEN STR_SIZEOF(nlstr)

int main(void)
{
	serial_puts(hellostr, HELLOSTR_LEN);
	serial_puts(nlstr, NLSTR_LEN);
	return 0;
}