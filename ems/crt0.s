/*
 * crt0.s
 * Richard Homan
 * 02/11/2024
 * C runtime startup for Enemigo Monitor System
 */

	.text

	.extern __stack
	.extern __heap_end
	.weak __heap_end
	.extern __start1

	/* __reset should cause a HALT in a hosted executable and
	   fall into __start for an unhosted executable.  The user is
	   free to override this with their own declaration.  */
	.globl __reset
	.weak __reset
__reset: /* Reset? More like restart */

	.globl __start
__start:
	/* Initialize stack */
	move.l IMM(__stack), sp
	move.l IMM(0), fp
	move.l IMM(__heap_end), d1
#if HOSTED
	/* INIT_SIM syscall.  Allows changing sp & d1.  */
	move.l IMM(1),d0

	/* The semihosting sequence is 'nop; halt;sentinel' aligned to
	   a 4 byte boundary.  The sentinel is an ill formed instruction
	   (movec %sp,0).  The debugger will adjust the pc, so it is never
	    executed.  */
	.balignw 4,0x4e71
	nop
	halt
	.long 0x4e7bf000
#endif
	move.l d1,sp@-
	move.l fp,sp@-  /* Dummy return address */
	jmp __start1

