#NO_APP
	.file	"serial.c"
	.text
	.align	2
	.globl	serial_init
	.type	serial_init, @function
serial_init:
	link.w %fp,#0
	move.l #131077,%a0
	move.b #48,(%a0)
	move.l #131077,%a0
	move.b #32,(%a0)
	move.l #131077,%a0
	move.b #1,(%a0)
	move.l #131081,%a0
	clr.b (%a0)
	move.l #131075,%a0
	move.b #-69,(%a0)
	move.l #131073,%a0
	move.b #19,(%a0)
	move.l #131073,%a0
	move.b #7,(%a0)
	move.l #131077,%a0
	move.b #5,(%a0)
	nop
	unlk %fp
	rts
	.size	serial_init, .-serial_init
	.align	2
	.globl	serial_puts
	.type	serial_puts, @function
serial_puts:
	link.w %fp,#-4
	move.l %d2,-(%sp)
	moveq #0,%d2
	jra .L4
.L7:
	move.l %d2,%d0
	move.l 8(%fp),%a0
	add.l %d0,%a0
	move.b (%a0),-1(%fp)
	jeq .L9
	move.b -1(%fp),%d0
	ext.w %d0
	move.w %d0,%a0
	move.l %a0,-(%sp)
	jsr serial_putc
	addq.l #4,%sp
	addq.l #1,%d2
.L4:
	cmp.l 12(%fp),%d2
	jlt .L7
	jra .L6
.L9:
	nop
.L6:
	nop
	move.l -8(%fp),%d2
	unlk %fp
	rts
	.size	serial_puts, .-serial_puts
	.align	2
	.globl	serial_putc
	.type	serial_putc, @function
serial_putc:
	link.w %fp,#-4
	move.l 8(%fp),%d0
	move.b %d0,%d0
	move.b %d0,-2(%fp)
	nop
.L11:
	move.l #131075,%a0
	move.b (%a0),%d0
	move.b %d0,%d0
	and.l #255,%d0
	moveq #4,%d1
	and.l %d1,%d0
	jeq .L11
	move.l #131079,%a0
	move.b -2(%fp),%d0
	move.b %d0,(%a0)
	nop
	unlk %fp
	rts
	.size	serial_putc, .-serial_putc
	.align	2
	.globl	serial_isc
	.type	serial_isc, @function
serial_isc:
	link.w %fp,#0
	move.l #131075,%a0
	move.b (%a0),%d0
	and.b #1,%d0
	unlk %fp
	rts
	.size	serial_isc, .-serial_isc
	.align	2
	.globl	serial_getc
	.type	serial_getc, @function
serial_getc:
	link.w %fp,#0
	move.l #131079,%a0
	move.b (%a0),%d0
	unlk %fp
	rts
	.size	serial_getc, .-serial_getc
	.ident	"GCC: (GNU) 13.2.0"
