/*
 * ems.ld
 * Richard Homan
 * 02/11/2024
 * Linker script for Enemigo Monitor System
 */

ENTRY(main)

MEMORY
{
	rom	(rx)	:	ORIGIN = 0x0000, LENGTH = 0x8000
	ram	(rwx)	:	ORIGIN = 0x8000, LENGTH = 0x8000
}

/* reset vector points to main */
PROVIDE(__reset = main);
/* stack begins at bottom of ram */
PROVIDE(__stack = 0x8000 + 0x8000 - 1);

/* 
 * text & data in ROM
 * stack in RAM
 */
SECTIONS
{
	.text :
	{
		*(.isv);
		. = ALIGN(0xff); /* incase isv is not defined, seek */
		*(.text);
	}> rom

	.data :
	{
		*(.data);
	}> ram AT> rom

	/* There shouldn't exist a bss section anyway but just in case */
	.bss (NOLOAD) :
	{
		*(.bss);
	}> ram
}
