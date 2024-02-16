/*
 * ems.ld
 * Richard Homan
 * 02/11/2024
 * Linker script for Enemigo Monitor System
 * Specifically for testing on EASy68K simulator
 */

ENTRY(main)

/*MEMORY
{
	rom	(rx)	:	ORIGIN = 0x0000, LENGTH = 0x8000
	ram	(rwx)	:	ORIGIN = 0x8000, LENGTH = 0x8000
} provided by host
*/

/* reset vector points to main */
/*PROVIDE(__reset = main); provided by host */
/* stack begins at bottom of ram */
/*PROVIDE(__stack = 0x8000 + 0x8000 - 1); provided by host */

/* 
 * text & data in ROM
 * stack in RAM
 */
SECTIONS
{
	.text 0x2000 : /* standard placement */
	{
		/**(.isv); provided by host */
		*(.text);
	}

	.data 0x4000 : /* standard sim placement */
	{
		*(.rodata);
		*(.data);
	}

	/* There shouldn't exist a bss section anyway but just in case */
	.bss (NOLOAD) :
	{
		*(.bss);
		*(COMMON);
	}
}
