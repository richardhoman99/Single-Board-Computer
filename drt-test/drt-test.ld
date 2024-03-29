/*
 * drt-test.ld
 * Richard Homan
 * 03/29/2024
 * Linker script for DUART test program
 */

ENTRY(main)

MEMORY
{
	rom	(rx)	:	ORIGIN = 0x00000, LENGTH = 0x10000
	ram	(rwx)	:	ORIGIN = 0x10000, LENGTH = 0x10000
}

/* reset vector points to main */
PROVIDE(__reset = main);
/* stack begins at bottom of ram */
PROVIDE(__stack = 0x10000 + 0x10000);

PROVIDE(DUART_PTR = 0x20000);

/* 
 * text & data in ROM
 * stack in RAM
 */
SECTIONS
{
	.text :
	{
		*(.isv);
		FILL(0xFF)
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
