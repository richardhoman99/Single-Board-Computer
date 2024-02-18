/*
 * ee.ld
 * Richard Homan
 * 02/17/2024
 * Linker script for Enemigo Executable
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
		. = 0x400; /* incase isv is not defined, seek */
		*(.text);
	}> ram

	.rodata :
	{
		. = ALIGN(0x10); /* easy to read alignment */
		*(.rodata);
	}> ram

	.data :
	{
		. = ALIGN(0x10); /* easy to read alignment */
		*(.data);
	}> ram

	/* There shouldn't exist a bss section anyway but just in case */
	.bss (NOLOAD) :
	{
		. = ALIGN(0x10); /* easy to read alignment */
		*(.bss);
	}> ram
}
