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

const char debug_prog_line00[] = "S00A000065652E7372656350";
const char debug_prog_line01[] = "S2140100004E5600004878000E4879000101304EB97E";
const char debug_prog_line02[] = "S21401001000010088508F4878000348790001013EAE";
const char debug_prog_line03[] = "S2140100204EB900010088508F70004E5E4E7500007C";
const char debug_prog_line04[] = "S2140100304E560000207C0002000510BC0030207CDB";
const char debug_prog_line05[] = "S2140100400002000510BC0020207C0002000510BC48";
const char debug_prog_line06[] = "S2140100500001207C000200094210207C00020003FF";
const char debug_prog_line07[] = "S21401006010BCFFBB207C0002000110BC0013207CEA";
const char debug_prog_line08[] = "S2140100700002000110BC0007207C0002000510BC35";
const char debug_prog_line09[] = "S21401008000054E714E5E4E754E56FFFC2F027400F3";
const char debug_prog_line10[] = "S21401009060202002206E0008D1C01D50FFFF671AA5";
const char debug_prog_line11[] = "S2140100A0102EFFFF488030402F084EBA001A588F96";
const char debug_prog_line12[] = "S2140100B05282B4AE000C6DDA60024E714E71242E7F";
const char debug_prog_line13[] = "S2140100C0FFF84E5E4E754E56FFFC202E00081000BF";
const char debug_prog_line14[] = "S2140100D01D40FFFE4E71207C000200031010100030";
const char debug_prog_line15[] = "S2140100E00280000000FF7204C08167EA207C0002E3";
const char debug_prog_line16[] = "S2140100F00007102EFFFE10804E714E5E4E754E5656";
const char debug_prog_line17[] = "S2140101000000207C000200031010020000014E5E79";
const char debug_prog_line18[] = "S2140101104E754E560000207C0002000710104E5E01";
const char debug_prog_line19[] = "S2060101204E7514";
const char debug_prog_line20[] = "S214010122000000000000000000000000000048651A";
const char debug_prog_line21[] = "S2130101326C6C6F2C20576F726C6421000D0A00E5";
const char debug_prog_line22[] = "S210010144000000000000000000000000A9";
const char debug_prog_line23[] = "S804010000FA";

const char * const debug_prog[] = 
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
	debug_prog_line13,
	debug_prog_line14,
	debug_prog_line15,
	debug_prog_line16,
	debug_prog_line17,
	debug_prog_line18,
	debug_prog_line19,
	debug_prog_line20,
	debug_prog_line21,
	debug_prog_line22,
	debug_prog_line23
};

const ubyte debug_prog_l[] = 
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
	ARR_LEN(debug_prog_line13),
	ARR_LEN(debug_prog_line14),
	ARR_LEN(debug_prog_line15),
	ARR_LEN(debug_prog_line16),
	ARR_LEN(debug_prog_line17),
	ARR_LEN(debug_prog_line18),
	ARR_LEN(debug_prog_line19),
	ARR_LEN(debug_prog_line20),
	ARR_LEN(debug_prog_line21),
	ARR_LEN(debug_prog_line22),
	ARR_LEN(debug_prog_line23)
};

#endif
