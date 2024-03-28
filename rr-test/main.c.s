#NO_APP
	.file	"main.c"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	link.w %fp,#-8
	move.l %d2,-(%sp)
	moveq #0,%d2
	jra .L2
.L3:
#APP
| 15 "main.c" 1
	nop
| 0 "" 2
#NO_APP
	addq.l #1,%d2
.L2:
	cmp.l #49999999,%d2
	jle .L3
	move.l #8388608,-4(%fp)
	move.l -4(%fp),%a0
	move.l (%a0),-8(%fp)
	addq.l #1,-8(%fp)
	move.l -4(%fp),%a0
	move.l -8(%fp),(%a0)
.L4:
#APP
| 24 "main.c" 1
	nop
| 0 "" 2
#NO_APP
	jra .L4
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.0"
