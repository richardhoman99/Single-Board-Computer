#NO_APP
	.file	"main.c"
	.text
	.globl	str1
	.section	.rodata
	.type	str1, @object
	.size	str1, 13
str1:
	.string	"I like pie!!"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	link.w %fp,#0
	jsr serial_init
.L2:
	pea 13.w
	pea str1
	jsr serial_puts
	addq.l #8,%sp
	jra .L2
	.size	main, .-main
	.align	2
	.globl	__access_error
	.type	__access_error, @function
__access_error:
	link.w %fp,#-8
	move.l %a0,-(%sp)
	move.l %d0,-(%sp)
	moveq #85,%d0
	move.l %d0,-4(%fp)
	move.l #65536,-8(%fp)
	move.l -8(%fp),%a0
	move.l -4(%fp),(%a0)
	nop
	move.l (%sp)+,%d0
	move.l (%sp)+,%a0
	unlk %fp
	rte
	.size	__access_error, .-__access_error
	.ident	"GCC: (GNU) 13.2.0"
