#NO_APP
	.file	"command.c"
	.text
	.globl	command_vec
	.section	.rodata
	.align	2
	.type	command_vec, @object
	.size	command_vec, 64
command_vec:
	.long	ems_cm
	.long	ems_dm
	.long	ems_r
	.long	invalid_command
	.long	invalid_command
	.long	ems_cr
	.long	ems_dr
	.long	invalid_command
	.long	ems_h
	.long	invalid_command
	.long	invalid_command
	.long	invalid_command
	.long	ems_l
	.long	invalid_command
	.long	invalid_command
	.long	invalid_command
	.text
	.align	2
	.globl	invalid_command
	.type	invalid_command, @function
invalid_command:
	link.w %fp,#0
	moveq #-1,%d0
	unlk %fp
	rts
	.size	invalid_command, .-invalid_command
	.align	2
	.globl	split_args
	.type	split_args, @function
split_args:
	link.w %fp,#-4
	move.l %d3,-(%sp)
	move.l %d2,-(%sp)
	move.l 20(%fp),%a0
	clr.l (%a0)
	moveq #1,%d3
	moveq #0,%d2
	jra .L4
.L10:
	move.l 20(%fp),%a0
	move.l (%a0),%d0
	cmp.l 24(%fp),%d0
	jgt .L12
	move.l %d2,%d0
	move.l 8(%fp),%a0
	add.l %d0,%a0
	move.b (%a0),-1(%fp)
	jeq .L13
	cmp.b #32,-1(%fp)
	jne .L8
	move.l %d2,%d0
	move.l 8(%fp),%a0
	add.l %d0,%a0
	clr.b (%a0)
	moveq #1,%d3
	jra .L9
.L8:
	tst.l %d3
	jeq .L9
	move.l %d2,%d0
	move.l 20(%fp),%a0
	move.l (%a0),%d1
	add.l %d1,%d1
	add.l %d1,%d1
	move.l 16(%fp),%a0
	add.l %d1,%a0
	add.l 8(%fp),%d0
	move.l %d0,(%a0)
	move.l 20(%fp),%a0
	move.l (%a0),%d0
	addq.l #1,%d0
	move.l 20(%fp),%a0
	move.l %d0,(%a0)
	moveq #0,%d3
.L9:
	addq.l #1,%d2
.L4:
	cmp.l 12(%fp),%d2
	jlt .L10
	jra .L6
.L12:
	nop
	jra .L6
.L13:
	nop
.L6:
	move.l 12(%fp),%d0
	subq.l #1,%d0
	move.l 8(%fp),%a0
	add.l %d0,%a0
	clr.b (%a0)
	moveq #0,%d0
	move.l (%sp)+,%d2
	move.l (%sp)+,%d3
	unlk %fp
	rts
	.size	split_args, .-split_args
	.align	2
	.globl	gcommand
	.type	gcommand, @function
gcommand:
	link.w %fp,#-12
	move.l #invalid_command,-10(%fp)
	move.l 8(%fp),%a0
	move.b (%a0),-1(%fp)
	clr.b -2(%fp)
	clr.l -6(%fp)
	jra .L15
.L16:
	move.b -1(%fp),%d0
	add.b %d0,-2(%fp)
	addq.l #1,-6(%fp)
	move.l -6(%fp),%d0
	move.l 8(%fp),%a0
	add.l %d0,%a0
	move.b (%a0),-1(%fp)
.L15:
	tst.b -1(%fp)
	jne .L16
	and.b #15,-2(%fp)
	moveq #0,%d0
	move.b -2(%fp),%d0
	add.l %d0,%d0
	move.l %d0,%a1
	add.l %d0,%a1
	lea command_vec,%a0
	move.l (%a1,%a0.l),-10(%fp)
	move.l -10(%fp),%d0
	unlk %fp
	rts
	.size	gcommand, .-gcommand
	.ident	"GCC: (GNU) 13.2.0"
