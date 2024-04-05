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

// const char debug_prog_line00[] = "S2140101004E5600004878000E4879000101C04EB9ED";
// const char debug_prog_line01[] = "S2140101100001013A508F487800034879000101CE6A";
// const char debug_prog_line02[] = "S2140101204EB90001013A508F70004E5E4E750000C8";
// const char debug_prog_line03[] = "S2140101304E5600004E714E5E4E754E5600002F090B";
// const char debug_prog_line04[] = "S2140101402F012F00226E0008222E000C103C000109";
// const char debug_prog_line05[] = "S2140101504E4F201F221F225F4E714E5E4E754E5629";
// const char debug_prog_line06[] = "S214010160FFFC202E000810001D40FFFE2F012F006F";
// const char debug_prog_line07[] = "S214010170122EFFFE103C00064E4F201F221F4E710E";
// const char debug_prog_line08[] = "S2140101804E5E4E754E56FFFC2F012F00103C0007A9";
// const char debug_prog_line09[] = "S2140101904E4F1D41FFFF201F221F102EFFFF4E5EF8";
// const char debug_prog_line10[] = "S2140101A04E754E56FFFC2F012F00103C00054E4F9A";
// const char debug_prog_line11[] = "S2140101B01D41FFFF201F221F102EFFFF4E5E4E75B2";
// const char debug_prog_line12[] = "S2140101C048656C6C6F2C20576F726C6421000D0AA9";
// const char debug_prog_line13[] = "S2050101D00028";
// const char debug_prog_line14[] = "S2100101D400000000000000000000000019";
// const char debug_prog_line15[] = "S804010100F9";

const char debug_prog_line00[] = "S2140101004E5600004878000E4879000102304EB97C";
const char debug_prog_line01[] = "S21401011000010188508F4878000348790001023EAB";
const char debug_prog_line02[] = "S2140101204EB900010188508F70004E5E4E7500007A";
const char debug_prog_line03[] = "S2140101304E560000207C0002000510BC0030207CDA";
const char debug_prog_line04[] = "S2140101400002000510BC0020207C0002000510BC47";
const char debug_prog_line05[] = "S2140101500001207C000200094210207C00020003FE";
const char debug_prog_line06[] = "S21401016010BCFFBB207C0002000110BC0013207CE9";
const char debug_prog_line07[] = "S2140101700002000110BC0007207C0002000510BC34";
const char debug_prog_line08[] = "S21401018000054E714E5E4E754E56FFFC2F027400F2";
const char debug_prog_line09[] = "S21401019060202002206E0008D1C01D50FFFF671AA4";
const char debug_prog_line10[] = "S2140101A0102EFFFF488030402F084EBA001A588F95";
const char debug_prog_line11[] = "S2140101B05282B4AE000C6DDA60024E714E71242E7E";
const char debug_prog_line12[] = "S2140101C0FFF84E5E4E754E56FFFC202E00081000BE";
const char debug_prog_line13[] = "S2140101D01D40FFFE4E71207C00020003101010002F";
const char debug_prog_line14[] = "S2140101E00280000000FF7204C08167EA207C0002E2";
const char debug_prog_line15[] = "S2140101F00007102EFFFE10804E714E5E4E754E5655";
const char debug_prog_line16[] = "S2140102000000207C000200031010020000014E5E78";
const char debug_prog_line17[] = "S2140102104E754E560000207C0002000710104E5E00";
const char debug_prog_line18[] = "S2060102204E7513";
const char debug_prog_line19[] = "S2140102220000000000000000000000000000486519";
const char debug_prog_line20[] = "S2130102326C6C6F2C20576F726C6421000D0A00E4";
const char debug_prog_line21[] = "S210010244000000000000000000000000A8";
const char debug_prog_line22[] = "S804010100F9";

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
	debug_prog_line22
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
	ARR_LEN(debug_prog_line22)
};

#endif
