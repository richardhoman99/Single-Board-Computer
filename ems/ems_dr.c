/*
 * ems_dr.c
 * Richard Homan
 * 02/17/2024
 * Dump registers logic for Enemigo Monitor System
 */

#include "command_err.h"
#include "types.h"

#define CONCAT_(a,b) a##b
#define CONCAT(a, b) CONCAT_(a,b)

#define CONVERTANDPRINTDOUBLE(r0, r1) \
	__asm__ ("move.l	%/"#r0",%0\n" :"=m" (val) :: "cc");\
	for (i = 3; i >= 0; i--)\
	{\
		btoah(val&0xff, &(out[i*2]));\
		val= val>>8;\
	}\
	out[8] = 0;\
	serial_puts(CONCAT(r0,s), 5);\
	serial_puts(out, 9);\
	__asm__ ("move.l	%/"#r1",%0\n" :"=m" (val) :: "cc");\
	for (i = 3; i >= 0; i--)\
	{\
		btoah(val&0xff, &(out[i*2]));\
		val= val>>8;\
	}\
	out[8] = '\r';\
	out[9] = '\n';\
	out[10] = 0;\
	serial_puts(CONCAT(r1,s), 6);\
	serial_puts(out, 11);

// no arguments
int ems_dr(const char **argv, int argc)
{
	lword val;
	char out[11];
	register byte i;

	CONVERTANDPRINTDOUBLE(d0, a0);
	CONVERTANDPRINTDOUBLE(d1, a1);
	CONVERTANDPRINTDOUBLE(d2, a2);
	CONVERTANDPRINTDOUBLE(d3, a3);
	CONVERTANDPRINTDOUBLE(d4, a4);
	CONVERTANDPRINTDOUBLE(d5, a5);
	CONVERTANDPRINTDOUBLE(d6, fp);
	CONVERTANDPRINTDOUBLE(d7, sp);

	return 0;
}
