/*
 * debug_prog.h
 * Richard Homan
 * 02/17/2024
 * Debug program to feed into the srec loader because simulator doesn't support
 * copy/paste.
 */

#include "types.h"

#ifndef DEBUG_PROG_H
#define DEBUG_PROG_H

const char debug_prog_line00[] = "S11380004E5600004878000D4879000080C04EB9F3";
const char debug_prog_line01[] = "S113801000008030508F487800034879000080CDFC";
const char debug_prog_line02[] = "S11380204EB900008030508F70004E5E4E750000D7";
const char debug_prog_line03[] = "S11380304E56FFFC202E000C10001D40FFFE2F09A1";
const char debug_prog_line04[] = "S11380402F012F00226E0008222EFFFE103C00019B";
const char debug_prog_line05[] = "S11380504E4F201F221F225F4E714E5E4E754E56AC";
const char debug_prog_line06[] = "S1138060FFFC202E000810001D40FFFE2F012F00F2";
const char debug_prog_line07[] = "S1138070122EFFFE103C00064E4F201F221F4E7191";
const char debug_prog_line08[] = "S11380804E5E4E754E56FFFC2F012F00103C00072C";
const char debug_prog_line09[] = "S11380904E4F1D41FFFF201F221F102EFFFF4E5E7B";
const char debug_prog_line10[] = "S11380A04E754E56FFFC2F012F00103C00054E4F1D";
const char debug_prog_line11[] = "S11380B01D41FFFF201F221F102EFFFF4E5E4E7535";
const char debug_prog_line12[] = "S11380C056414449554D20424C415954000D0A0033";
const char debug_prog_line13[] = "S90380007C";

const char *debug_prog[] = 
{
	debug_prog_line00,
	debug_prog_line01,
	debug_prog_line02,
	debug_prog_line03,
	debug_prog_line04,
	debug_prog_line05,
	debug_prog_line06,
	debug_prog_line07,
	debug_prog_line08,
	debug_prog_line09,
	debug_prog_line10,
	debug_prog_line11,
	debug_prog_line12,
	debug_prog_line13
};

ubyte debug_prog_l[] = 
{
	ARR_LEN(debug_prog_line00),
	ARR_LEN(debug_prog_line01),
	ARR_LEN(debug_prog_line02),
	ARR_LEN(debug_prog_line03),
	ARR_LEN(debug_prog_line04),
	ARR_LEN(debug_prog_line05),
	ARR_LEN(debug_prog_line06),
	ARR_LEN(debug_prog_line07),
	ARR_LEN(debug_prog_line08),
	ARR_LEN(debug_prog_line09),
	ARR_LEN(debug_prog_line10),
	ARR_LEN(debug_prog_line11),
	ARR_LEN(debug_prog_line12),
	ARR_LEN(debug_prog_line13)
};

#endif
