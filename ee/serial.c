/*
 * serial.c
 * Richard Homan
 * 02/11/2024
 * Implementations for serial control
 */

#include "serial.h"

#ifndef SIM
#include "def_68681.h"

#define MR1A_VAL (ubyte)0x13
#define MR2A_VAL (ubyte)0x07
// #define MR2A_VAL (ubyte)0x47 // enable automatic echo
#define CSRA_VAL (ubyte)0xbb

#define CRA_VAL0 (ubyte)0x30 // reset transmitter
#define CRA_VAL1 (ubyte)0x20 // reset reciever
#define CRA_VAL2 (ubyte)0x01 // enable reciever
#define CRA_VAL3 (ubyte)0x05 // enable transmitter and reciever

#define ACR_VAL  (ubyte)0x00 // clock set select 1

inline
void serial_init()
{
	*CRA_PTR = CRA_VAL0;
	*CRA_PTR = CRA_VAL1;
	*CRA_PTR = CRA_VAL2;
	*ACR_PTR = ACR_VAL;
	*CSRA_PTR = CSRA_VAL;
	*MR1A_PTR = MR1A_VAL;
	*MR2A_PTR = MR2A_VAL;
	*CRA_PTR = CRA_VAL3;
	return;
}

void serial_puts(const char *in, int len)
{
	register int i;
	char c;

	for (i = 0; i < len; i++)
	{
		c = in[i];
		if (c == '\0') break;

		serial_putc(c);
	}

	return;
}

inline
void serial_putc(char c)
{
	while ((*SRA_PTR & 0x4) == 0) ;
	*TBA_PTR = (ubyte)c;
	return;
}

// inline
// byte serial_isc()
// {
// 	return (*SRA_PTR & 0x1);
// }

// inline
// char serial_getc()
// {
// 	return *(char *)RBA_PTR;
// }

#else
void serial_init()
{
	return;
}

// trap 15, d0=1, a1=string, d1=string len
void serial_puts(const char *in, int len)
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

#endif
