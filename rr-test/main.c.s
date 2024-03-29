#NO_APP
	.file	"main.c"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	link.w %fp,#0
	move.l %a2,-(%sp)
	move.l %d2,-(%sp)
	moveq #0,%d2
	jra .L2
.L3:
#APP
| 13 "main.c" 1
	nop
| 0 "" 2
#NO_APP
	addq.l #1,%d2
.L2:
	cmp.l #3999999,%d2
	jle .L3
	move.l #196608,%a2
	move.l (%a2),%d2
	addq.l #1,%d2
	move.l %d2,(%a2)
.L4:
#APP
| 22 "main.c" 1
	nop
| 0 "" 2
#NO_APP
	jra .L4
	.size	main, .-main
	.align	2
	.globl	__access_error
	.type	__access_error, @function
__access_error:
	link.w %fp,#-4
	move.l %a2,-(%sp)
	moveq #85,%d0
	move.l %d0,-4(%fp)
	move.l #65536,%a2
	move.l -4(%fp),(%a2)
	nop
	move.l (%sp)+,%a2
	unlk %fp
	rts
	.size	__access_error, .-__access_error
	.ident	"GCC: (GNU) 13.2.0"
