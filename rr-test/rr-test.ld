/*
 * rr-test.ld
 * Richard Homan
 * 03/22/2024
 * Linker script for ROM/RAM test program
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
	}> rom

	.rodata :
	{
		. = ALIGN(0x10); /* easy to read alignment */
		*(.rodata);
	}> rom

	.data :
	{
		. = ALIGN(0x10); /* easy to read alignment */
		*(.data);
	}> ram AT> rom

	/* There shouldn't exist a bss section anyway but just in case */
	.bss (NOLOAD) :
	{
		. = ALIGN(0x10); /* easy to read alignment */
		*(.bss);
	}> ram
}
