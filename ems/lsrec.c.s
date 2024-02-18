#NO_APP
	.file	"lsrec.c"
	.text
	.globl	lsrec_errstr_success
	.section	.rodata
	.type	lsrec_errstr_success, @object
	.size	lsrec_errstr_success, 5
lsrec_errstr_success:
	.string	"succ"
	.globl	lsrec_errstr_not_srec_format
	.type	lsrec_errstr_not_srec_format, @object
	.size	lsrec_errstr_not_srec_format, 16
lsrec_errstr_not_srec_format:
	.string	"not srec format"
	.globl	lsrec_errstr_unsupported_type_s2
	.type	lsrec_errstr_unsupported_type_s2, @object
	.size	lsrec_errstr_unsupported_type_s2, 3
lsrec_errstr_unsupported_type_s2:
	.string	"S2"
	.globl	lsrec_errstr_unsupported_type_s3
	.type	lsrec_errstr_unsupported_type_s3, @object
	.size	lsrec_errstr_unsupported_type_s3, 3
lsrec_errstr_unsupported_type_s3:
	.string	"S3"
	.globl	lsrec_errstr_unsupported_type_s4
	.type	lsrec_errstr_unsupported_type_s4, @object
	.size	lsrec_errstr_unsupported_type_s4, 3
lsrec_errstr_unsupported_type_s4:
	.string	"S4"
	.globl	lsrec_errstr_unsupported_type_s6
	.type	lsrec_errstr_unsupported_type_s6, @object
	.size	lsrec_errstr_unsupported_type_s6, 3
lsrec_errstr_unsupported_type_s6:
	.string	"S6"
	.globl	lsrec_errstr_unsupported_type_s7
	.type	lsrec_errstr_unsupported_type_s7, @object
	.size	lsrec_errstr_unsupported_type_s7, 3
lsrec_errstr_unsupported_type_s7:
	.string	"S7"
	.globl	lsrec_errstr_unsupported_type_s8
	.type	lsrec_errstr_unsupported_type_s8, @object
	.size	lsrec_errstr_unsupported_type_s8, 3
lsrec_errstr_unsupported_type_s8:
	.string	"S8"
	.globl	lsrec_errstr_address_out_of_bounds
	.type	lsrec_errstr_address_out_of_bounds, @object
	.size	lsrec_errstr_address_out_of_bounds, 29
lsrec_errstr_address_out_of_bounds:
	.string	"address out of memory bounds"
	.globl	lsrec_errstr_length_nonequal
	.type	lsrec_errstr_length_nonequal, @object
	.size	lsrec_errstr_length_nonequal, 34
lsrec_errstr_length_nonequal:
	.string	"count does not match actual count"
	.globl	lsrec_errstr_length_extends_out_of_bounds
	.type	lsrec_errstr_length_extends_out_of_bounds, @object
	.size	lsrec_errstr_length_extends_out_of_bounds, 43
lsrec_errstr_length_extends_out_of_bounds:
	.string	"address+count extends out of memory bounds"
	.globl	lsrec_errstr_invalid_checksum
	.type	lsrec_errstr_invalid_checksum, @object
	.size	lsrec_errstr_invalid_checksum, 17
lsrec_errstr_invalid_checksum:
	.string	"invalid checksum"
	.globl	lsrec_errstr_record_count_nonequal
	.type	lsrec_errstr_record_count_nonequal, @object
	.size	lsrec_errstr_record_count_nonequal, 51
lsrec_errstr_record_count_nonequal:
	.string	"count of given records does not equal actual given"
	.globl	lsrec_errstr_entry_out_of_bounds
	.type	lsrec_errstr_entry_out_of_bounds, @object
	.size	lsrec_errstr_entry_out_of_bounds, 50
lsrec_errstr_entry_out_of_bounds:
	.string	"entry point is not defined in given address space"
	.globl	lsrec_errstr_data_given_after_entry
	.type	lsrec_errstr_data_given_after_entry, @object
	.size	lsrec_errstr_data_given_after_entry, 43
lsrec_errstr_data_given_after_entry:
	.string	"data record given after entry point record"
	.globl	lsrec_errstr_invalid_format
	.type	lsrec_errstr_invalid_format, @object
	.size	lsrec_errstr_invalid_format, 49
lsrec_errstr_invalid_format:
	.string	"given record format does not match specification"
	.globl	lsrec_errstr_invalid_hex
	.type	lsrec_errstr_invalid_hex, @object
	.size	lsrec_errstr_invalid_hex, 17
lsrec_errstr_invalid_hex:
	.string	"value is not hex"
	.globl	lsrec_errstr_tab
	.data
	.align	2
	.type	lsrec_errstr_tab, @object
	.size	lsrec_errstr_tab, 68
lsrec_errstr_tab:
	.long	lsrec_errstr_success
	.long	lsrec_errstr_not_srec_format
	.long	lsrec_errstr_unsupported_type_s2
	.long	lsrec_errstr_unsupported_type_s3
	.long	lsrec_errstr_unsupported_type_s4
	.long	lsrec_errstr_unsupported_type_s6
	.long	lsrec_errstr_unsupported_type_s7
	.long	lsrec_errstr_unsupported_type_s8
	.long	lsrec_errstr_address_out_of_bounds
	.long	lsrec_errstr_length_nonequal
	.long	lsrec_errstr_length_extends_out_of_bounds
	.long	lsrec_errstr_invalid_checksum
	.long	lsrec_errstr_record_count_nonequal
	.long	lsrec_errstr_entry_out_of_bounds
	.long	lsrec_errstr_data_given_after_entry
	.long	lsrec_errstr_invalid_format
	.long	lsrec_errstr_invalid_hex
	.globl	lsrec_errstr_unsupported_type
	.section	.rodata
	.type	lsrec_errstr_unsupported_type, @object
	.size	lsrec_errstr_unsupported_type, 17
lsrec_errstr_unsupported_type:
	.string	"unsupported type"
	.globl	lsrec_errstr_divider
	.type	lsrec_errstr_divider, @object
	.size	lsrec_errstr_divider, 3
lsrec_errstr_divider:
	.string	": "
	.local	s1_record_count
	.comm	s1_record_count,2,2
	.local	entry
	.comm	entry,4,2
	.local	dbeginaddr
	.comm	dbeginaddr,4,2
	.local	dendaddr
	.comm	dendaddr,4,2
	.local	err
	.comm	err,4,2
	.text
	.align	2
	.globl	lsrec_begin
	.type	lsrec_begin, @function
lsrec_begin:
	link.w %fp,#0
	clr.w s1_record_count
	moveq #-1,%d0
	move.l %d0,dbeginaddr
	clr.l dendaddr
	clr.l err
	moveq #0,%d0
	unlk %fp
	rts
	.size	lsrec_begin, .-lsrec_begin
	.align	2
	.globl	lsrec_in
	.type	lsrec_in, @function
lsrec_in:
	link.w %fp,#-4
	move.l 12(%fp),%d0
	move.b %d0,%d0
	move.b %d0,-2(%fp)
	moveq #-1,%d0
	unlk %fp
	rts
	.size	lsrec_in, .-lsrec_in
	.align	2
	.globl	lsrec_end
	.type	lsrec_end, @function
lsrec_end:
	link.w %fp,#0
	move.l entry,%d0
	move.l 8(%fp),%a0
	move.l %d0,(%a0)
	moveq #0,%d0
	unlk %fp
	rts
	.size	lsrec_end, .-lsrec_end
	.align	2
	.globl	lsrec_errstr
	.type	lsrec_errstr, @function
lsrec_errstr:
	link.w %fp,#-12
	move.l 12(%fp),%d0
	move.b %d0,%d0
	move.b %d0,-12(%fp)
	move.l 8(%fp),%a0
	clr.b (%a0)
	move.l err,%d0
	moveq #-17,%d1
	cmp.l %d0,%d1
	jgt .L12
	clr.b -1(%fp)
	move.l err,%d0
	addq.l #7,%d0
	moveq #5,%d1
	cmp.l %d0,%d1
	jcs .L13
	moveq #0,%d1
	move.b -12(%fp),%d1
	moveq #0,%d0
	move.b -1(%fp),%d0
	add.l 8(%fp),%d0
	move.l %d1,-(%sp)
	pea lsrec_errstr_unsupported_type
	move.l %d0,-(%sp)
	jsr strncpy
	lea (12,%sp),%sp
	move.b %d0,-1(%fp)
	moveq #0,%d1
	move.b -12(%fp),%d1
	moveq #0,%d0
	move.b -1(%fp),%d0
	add.l 8(%fp),%d0
	move.l %d1,-(%sp)
	pea lsrec_errstr_divider
	move.l %d0,-(%sp)
	jsr strncpy
	lea (12,%sp),%sp
	move.b %d0,-1(%fp)
	jra .L11
.L13:
	nop
.L11:
	move.l err,%d0
	neg.l %d0
	move.l %d0,-6(%fp)
	move.l -6(%fp),%d0
	add.l %d0,%d0
	move.l %d0,%a1
	add.l %d0,%a1
	lea lsrec_errstr_tab,%a0
	move.l (%a1,%a0.l),-10(%fp)
	moveq #0,%d0
	move.b -12(%fp),%d0
	move.l %d0,-(%sp)
	move.l -10(%fp),-(%sp)
	move.l 8(%fp),-(%sp)
	jsr strncpy
	lea (12,%sp),%sp
	move.b %d0,-1(%fp)
	jra .L7
.L12:
	nop
.L7:
	unlk %fp
	rts
	.size	lsrec_errstr, .-lsrec_errstr
	.align	2
	.globl	srec_gtype
	.type	srec_gtype, @function
srec_gtype:
	link.w %fp,#0
	move.l 8(%fp),%a0
	move.b (%a0),%d0
	cmp.b #83,%d0
	jne .L15
	move.l 8(%fp),%a0
	addq.l #1,%a0
	move.b (%a0),%d0
	cmp.b #47,%d0
	jle .L15
	move.l 8(%fp),%a0
	addq.l #1,%a0
	move.b (%a0),%d0
	cmp.b #57,%d0
	jle .L16
.L15:
	moveq #-1,%d0
	move.l %d0,err
	move.l err,%a0
	jra .L17
.L16:
	move.l 8(%fp),%a0
	addq.l #1,%a0
	move.b (%a0),%d0
	ext.w %d0
	move.w %d0,%a0
	lea (-48,%a0),%a0
.L17:
	move.l %a0,%d0
	unlk %fp
	rts
	.size	srec_gtype, .-srec_gtype
	.align	2
	.globl	srec_gcount
	.type	srec_gcount, @function
srec_gcount:
	link.w %fp,#-4
	move.l 8(%fp),%d0
	addq.l #2,%d0
	move.l %d0,-(%sp)
	jsr ahtob
	addq.l #4,%sp
	move.w %d0,-2(%fp)
	cmp.w #-1,-2(%fp)
	jne .L19
	moveq #-17,%d0
	move.l %d0,err
	move.l err,%a0
	jra .L20
.L19:
	move.w -2(%fp),%a0
.L20:
	move.l %a0,%d0
	unlk %fp
	rts
	.size	srec_gcount, .-srec_gcount
	.align	2
	.globl	srec_gaddr
	.type	srec_gaddr, @function
srec_gaddr:
	link.w %fp,#-4
	move.l 8(%fp),%d0
	addq.l #4,%d0
	move.l %d0,-(%sp)
	jsr ahtob
	addq.l #4,%sp
	move.w %d0,-2(%fp)
	cmp.w #-1,-2(%fp)
	jne .L22
	moveq #-17,%d0
	move.l %d0,err
	move.l err,%a0
	jra .L23
.L22:
	move.l 8(%fp),%d0
	addq.l #6,%d0
	move.l %d0,-(%sp)
	jsr ahtob
	addq.l #4,%sp
	move.w %d0,-4(%fp)
	cmp.w #-1,-4(%fp)
	jne .L24
	moveq #-17,%d0
	move.l %d0,err
	move.l err,%a0
	jra .L23
.L24:
	move.w -2(%fp),%d0
	lsl.w #8,%d0
	or.w %d0,-4(%fp)
	move.w -4(%fp),%a0
.L23:
	move.l %a0,%d0
	unlk %fp
	rts
	.size	srec_gaddr, .-srec_gaddr
	.align	2
	.globl	srec_gdatab
	.type	srec_gdatab, @function
srec_gdatab:
	link.w %fp,#-8
	move.l 12(%fp),%d0
	move.w %d0,%d0
	move.w %d0,-6(%fp)
	move.w -6(%fp),%a0
	move.l %a0,%d0
	addq.l #4,%d0
	move.l %d0,%d0
	add.w %d0,%d0
	move.w %d0,-2(%fp)
	move.w -2(%fp),%a0
	move.l 8(%fp),%d0
	add.l %a0,%d0
	move.l %d0,-(%sp)
	jsr ahtob
	addq.l #4,%sp
	move.w %d0,-4(%fp)
	cmp.w #-1,-4(%fp)
	jne .L26
	moveq #-17,%d0
	move.l %d0,err
	move.l err,%a0
	jra .L27
.L26:
	move.w -4(%fp),%a0
.L27:
	move.l %a0,%d0
	unlk %fp
	rts
	.size	srec_gdatab, .-srec_gdatab
	.ident	"GCC: (GNU) 13.2.0"
