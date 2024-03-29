/*
 * serial.c
 * Richard Homan
 * 02/11/2024
 * Implementations for serial control
 */

#include "serial.h"

#ifndef SIM

extern ubyte *DUART_PTR;
#define MR1A_PTR (ubyte *)(&DUART_PTR + 0x0)
#define MR2A_PTR (ubyte *)MR1A_PTR
#define SRA_PTR  (ubyte *)(&DUART_PTR + 0x1)
#define CSRA_PTR (ubyte *)SRA_PTR
#define CRA_PTR  (ubyte *)(&DUART_PTR + 0x2)
#define RBA_PTR  (ubyte *)(&DUART_PTR + 0x3)
#define TBA_PTR  (ubyte *)RBA_PTR
#define IPCR_PTR (ubyte *)(&DUART_PTR + 0x4)
#define ACR_PTR  (ubyte *)IPCR_PTR
#define ISR_PTR  (ubyte *)(&DUART_PTR + 0x5)
#define IMR_PTR  (ubyte *)ISR_PTR
#define CUR_PTR  (ubyte *)(&DUART_PTR + 0x6)
#define CTUR_PTR (ubyte *)CUR_PTR
#define CLR_PTR  (ubyte *)(&DUART_PTR + 0x7)
#define CTLR_PTR (ubyte *)CLR_PTR
#define MR1B_PTR (ubyte *)(&DUART_PTR + 0x8)
#define MR2B_PTR (ubyte *)MR1B_PTR;
#define SRB_PTR  (ubyte *)(&DUART_PTR + 0x9)
#define CSRB_PTR (ubyte *)SRB_PTR
#define CRB_PTR  (ubyte *)(&DUART_PTR + 0xa)
#define RBB_PTR  (ubyte *)(&DUART_PTR + 0xb)
#define TBB_PTR  (ubyte *)RBB_PTR
#define IVR_PTR  (ubyte *)(&DUART_PTR + 0xc)
#define IPR_PTR  (ubyte *)(&DUART_PTR + 0xd)
#define OPCR_PTR (ubyte *)IPR_PTR
#define OPRS_PTR (ubyte *)(&DUART_PTR + 0xe)
#define OPRC_PTR (ubyte *)(&DUART_PTR + 0xf)

#define MR1A_VAL (ubyte)0x13
// #define MR2A_VAL (ubyte)0x07
#define MR2A_VAL (ubyte)0x47 // enable automatic echo
#define CSRA_VAL (ubyte)0xbb

#define CRA_VAL0 (ubyte)0x30 // reset transmitter
#define CRA_VAL1 (ubyte)0x20 // reset reciever
#define CRA_VAL2 (ubyte)0x01 // enable reciever
#define CRA_VAL3 (ubyte)0x05 // enable transmitter and reciever

#define ACR_VAL  (ubyte)0x00 // clock set select 1

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

void serial_puts(const char *in, ubyte len)
{
	// TODO
	return;
}

void serial_putc(char c)
{
	// TODO
	return;
}

byte serial_isc()
{
	return (*SRA_PTR & 0x01) == 0;
}

char serial_getc()
{
	return *RBA_PTR;
}

#else
void serial_init()
{
	return;
}

// trap 15, d0=1, a1=string, d1=string len
void serial_puts(const char *in, ubyte len)
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
