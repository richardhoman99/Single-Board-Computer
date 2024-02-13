#NO_APP
	.file	"serial-sim.c"
	.text
	.align	2
	.globl	prints
	.type	prints, @function
prints:
	link.w %fp,#0
#APP
| 13 "serial-sim.c" 1
	move.l	%a1,-(%sp)
move.l	%d1,-(%sp)
move.l	%d0,-(%sp)
move.l	8(%fp),%a1
move.l	12(%fp),%d1
move.b	#1,%d0
trap		#15
move.l	(%sp)+,%d0
move.l	(%sp)+,%d1
move.l	(%sp)+,%a1

| 0 "" 2
#NO_APP
	nop
	unlk %fp
	rts
	.size	prints, .-prints
	.align	2
	.globl	isc
	.type	isc, @function
isc:
	link.w %fp,#-4
#APP
| 31 "serial-sim.c" 1
	move.l	%d0,-(%sp)
move.b	#7,%d0
trap		#15
move.b	%d1,-1(%fp)
move.l	(%sp)+,%d0
move.l	(%sp)+,%d1

| 0 "" 2
#NO_APP
	move.b -1(%fp),%d0
	ext.w %d0
	move.w %d0,%a0
	move.l %a0,%d0
	unlk %fp
	rts
	.size	isc, .-isc
	.align	2
	.globl	getc
	.type	getc, @function
getc:
	link.w %fp,#0
	clr.b %d0
	unlk %fp
	rts
	.size	getc, .-getc
	.ident	"GCC: (GNU) 13.2.0"
