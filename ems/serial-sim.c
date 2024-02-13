/*
 * serial-sim.c
 * Richard Homan
 * 02/11/2024
 * Implementations for serial control with SIM68k
 */

#include "serial-sim.h"

// trap 15, d0=1, a1=string, d1=string len
void serial_puts(const char *in, byte len)
{
	__asm__ __volatile__ ("move.l	%/a1,-(%/sp)\n" // save registers
						  "move.l	%/d1,-(%/sp)\n"
						  "move.l	%/d0,-(%/sp)\n"
						  "move.l	%0,%/a1\n" // address of string to a1
						  "move.l	%1,%/d1\n" // len to d1
						  "move.b	#1,%/d0\n" // task 1
						  "trap		#15\n"   // trap 15: SIM tasks
						  "move.l	(%/sp)+,%/d0\n" // restore registers
						  "move.l	(%/sp)+,%/d1\n"
						  "move.l	(%/sp)+,%/a1\n"
						  :: "rm" (in), "rm" (len) : "cc", "memory");
	return;
}

// trap 15, d0=6, d1=c
void serial_putc(char c)
{
	__asm__ __volatile__ ("move.l	%/d1,-(%/sp)\n" // save registers
						  "move.l	%/d0,-(%/sp)\n"
						  "move.b	%0,%/d1\n" // load c
						  "move.b	#6,%/d0\n" // task 6
						  "trap		#15\n"   // trap 15: SIM tasks
						  "move.l	(%/sp)+,%/d0\n" // restore registers
						  "move.l	(%/sp)+,%/d1\n"
						  :: "rm" (c) : "cc", "memory");
	return;
}

// trap 15, d0=7, d1.b = return
byte serial_isc()
{
	byte r;
	__asm__ __volatile__ ("move.l	%/d1,-(%/sp)\n" // save registers
						  "move.l	%/d0,-(%/sp)\n"
						  "move.b	#7,%/d0\n" // task 7
						  "trap		#15\n"   // trap 15: SIM tasks
						  "move.b	%/d1,%0\n" // get return value
						  "move.l	(%/sp)+,%/d0\n" // restore registers
						  "move.l	(%/sp)+,%/d1\n"
						  : "=m" (r) :: "cc", "memory");
	return r;
}

// trap 15, d0=5, d1.b = return
char serial_getc()
{
	char r;
	__asm__ __volatile__ ("move.l	%/d1,-(%/sp)\n" // save registers
						  "move.l	%/d0,-(%/sp)\n"
						  "move.b	#5,%/d0\n" // task 5
						  "trap		#15\n"   // trap 15: SIM tasks
						  "move.b	%/d1,%0\n" // get return value
						  "move.l	(%/sp)+,%/d0\n" // restore registers
						  "move.l	(%/sp)+,%/d1\n"
						  : "=m" (r) :: "cc", "memory");
	return r;
}
