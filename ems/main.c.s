#NO_APP
	.file	"main.c"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	link.w %fp,#-12
	moveq #5,%d0
	move.l %d0,-4(%fp)
	moveq #8,%d0
	move.l %d0,-8(%fp)
	move.l -8(%fp),-(%sp)
	move.l -4(%fp),-(%sp)
	jsr add
	addq.l #8,%sp
	move.l %d0,-12(%fp)
	moveq #0,%d0
	unlk %fp
	rts
	.size	main, .-main
	.align	2
	.globl	add
	.type	add, @function
add:
	link.w %fp,#-4
	move.l 8(%fp),%d0
	add.l 12(%fp),%d0
	move.l %d0,-4(%fp)
	move.l -4(%fp),%d0
	unlk %fp
	rts
	.size	add, .-add
	.ident	"GCC: (GNU) 13.2.0"
