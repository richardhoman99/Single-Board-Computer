/*
 * main.c
 * Richard Homan
 * 02/11/2024
 * Entry point for Enemigo Monitor System
 */

#include "types.h"
#include "convert.h"
#include "lsrec.h"
#include "serial-sim.h"

#define STR_SIZEOF(v) sizeof(v)/sizeof(v[0])

const char prompt[] = "ems% _\b"; // len = 8
const char delete[] = " \b\b \b"; // len = 6
const char cursor[] = "_\b"; // len = 3

const char invalid[] = "unknown command\r\n"; // len = 17
const char badarg[] = "bad argument\r\n"; // len = 15
const char help[] = "\
\tmr [reg] [val]  : chaange register\r\n\
\tmm [loc] [val]  : change memory\r\n\
\tdr              : dump registers\r\n\
\tdm [loc] [len]  : dump memory\r\n\
\tl               : load srec\r\n\
\th               : display this message\r\n\0"; // len = 211
const char d0s[] = "d0: "; // len = 5
const char d1s[] = "d1: "; // len = 5
const char d2s[] = "d2: "; // len = 5
const char d3s[] = "d3: "; // len = 5
const char d4s[] = "d4: "; // len = 5
const char d5s[] = "d5: "; // len = 5
const char d6s[] = "d6: "; // len = 5
const char d7s[] = "d7: "; // len = 5
const char a0s[] = " a0: "; // len = 6
const char a1s[] = " a1: "; // len = 6
const char a2s[] = " a2: "; // len = 6
const char a3s[] = " a3: "; // len = 6
const char a4s[] = " a4: "; // len = 6
const char a5s[] = " a5: "; // len = 6
const char fps[] = " fp: "; // len = 6
const char sps[] = " sp: "; // len = 6
const char pcs[] = "pc: "; // len = 5
const char errstr[] = "error "; // len = 6

const char debug[] = "debug\r\n"; // len = 8
// serial_puts(debug, 8);

const char noexecloadedstr[] = "no executable loaded";
const char nlstr[] = "\r\n";

static byte has_exec = 0;
static int (*exec_entry_ptr)(void);

const char hwprogline0[] = 	"S11380004E5600004878000E4879000080C04EB9F2";
const char hwprogline1[] = "S113801000008030508F487800034879000080CEFB";
const char hwprogline2[] = "S11380204EB900008030508F70004E5E4E750000D7";
const char hwprogline3[] = "S11380304E56FFFC202E000C10001D40FFFE2F09A1";
const char hwprogline4[] = "S11380402F012F00226E0008222EFFFE103C00019B";
const char hwprogline5[] = "S11380504E4F201F221F225F4E714E5E4E754E56AC";
const char hwprogline6[] = "S1138060FFFC202E000810001D40FFFE2F012F00F2";
const char hwprogline7[] = "S1138070122EFFFE103C00064E4F201F221F4E7191";
const char hwprogline8[] = "S11380804E5E4E754E56FFFC2F012F00103C00072C";
const char hwprogline9[] = "S11380904E4F1D41FFFF201F221F102EFFFF4E5E7B";
const char hwprogline10[] = "S11380A04E754E56FFFC2F012F00103C00054E4F1D";
const char hwprogline11[] = "S11380B01D41FFFF201F221F102EFFFF4E5E4E7535";
const char hwprogline12[] = "S11380C048656C6C6F2C20776F726C6421000D0A0C";
const char hwprogline13[] = "S10480D000AB";
const char hwprogline14[] = "S10F80D40000000000000000000000009C";
const char hwprogline15[] = "S90380007C";

const char *hwproglines[] = 
{
	hwprogline0,
	hwprogline1,
	hwprogline2,
	hwprogline3,
	hwprogline4,
	hwprogline5,
	hwprogline6,
	hwprogline7,
	hwprogline8,
	hwprogline9,
	hwprogline10,
	hwprogline11,
	hwprogline12,
	hwprogline13,
	hwprogline14,
	hwprogline15
};

ubyte hwproglines_len[] = 
{
	STR_SIZEOF(hwprogline0),
	STR_SIZEOF(hwprogline1),
	STR_SIZEOF(hwprogline2),
	STR_SIZEOF(hwprogline3),
	STR_SIZEOF(hwprogline4),
	STR_SIZEOF(hwprogline5),
	STR_SIZEOF(hwprogline6),
	STR_SIZEOF(hwprogline7),
	STR_SIZEOF(hwprogline8),
	STR_SIZEOF(hwprogline9),
	STR_SIZEOF(hwprogline10),
	STR_SIZEOF(hwprogline11),
	STR_SIZEOF(hwprogline12),
	STR_SIZEOF(hwprogline13),
	STR_SIZEOF(hwprogline14),
	STR_SIZEOF(hwprogline15)
};

char inbuf[256];
word inbuf_len;

byte cr();
byte cm();
byte dr();
byte dm();
byte l();
byte r();

int main(void)
{
	char inchar;

	has_exec = 0;
	
mprompt:
	inbuf_len = 0;
	serial_puts(prompt, 8);
mwaitc:
	while (!serial_isc())
		__asm__ __volatile__ ("nop");
	inchar = serial_getc();
	if (inchar == '\r')
	{
		inbuf[inbuf_len] = 0;
		serial_puts(delete, 6);
		goto meval;
	}
	if (inchar == 8)
	{
		if (inbuf_len != 0)
		{
			inbuf_len--;
			serial_puts(delete, 6);
		}
	}
	else
	{
		inbuf[inbuf_len] = inchar;
		inbuf_len++;
	}
	serial_puts(cursor, 3);
	goto mwaitc;

meval:
	if (inbuf[0] == 'c')
	{
		if (inbuf[1] == 'r')
		{
			if (inbuf[2] != ' ')
				goto print_invalid;
			if (inbuf_len != 14)
				goto print_badarg;
			if (cr())
				goto print_badarg;
		}
		else if (inbuf[1] == 'm')
		{
			if (inbuf[2] != ' ')
				goto print_invalid;
			if (inbuf_len != 10)
				goto print_badarg;
			cm();
		}
		else
		{
			goto print_invalid;
		}
	}
	else if (inbuf[0] == 'd')
	{
		if (inbuf[1] == 'r')
		{
			if (inbuf[2] != 0)
				goto print_invalid;
			if (inbuf_len != 2)
				goto print_invalid;
			dr();
		}
		else if (inbuf[1] == 'm')
		{
			if (inbuf[2] != ' ')
				goto print_invalid;
			if (inbuf_len != 10)
				goto print_badarg;
			dm();
		}
		else
		{
			goto print_invalid;
		}
	}
	else if (inbuf[0] == 'l')
	{
		if (inbuf[1] != 0)
			goto print_invalid;
		l();
	}
	else if (inbuf[0] == 'r')
	{
		if (inbuf[1] != 0)
			goto print_invalid;
		r();
	}
	else if (inbuf[0] == 'h')
	{
		serial_puts(help, 211);
	}
	else
	{
		goto print_invalid;
	}

goto mprompt;
print_invalid:
	serial_puts(invalid, 17);
goto mprompt;
print_badarg:
	serial_puts(badarg, 15);
goto mprompt;

	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}

byte cr()
{
	char *sval;
	lword valh, vall;
	lword val;

	sval = &(inbuf[6]);
	valh = ahtob(sval);
	if (valh == -1)
		return -1;
	sval = &(inbuf[8]);
	vall = ahtob(sval);
	if (vall == -1)
		return -1;
	val = (valh << 8) | (vall & 0xff);
	sval = &(inbuf[10]);
	valh = ahtob(sval);
	if (valh == -1)
		return -1;
	sval = &(inbuf[12]);
	vall = ahtob(sval);
	if (vall == -1)
		return -1;
	val = (val << 16) | ((valh << 8) | (vall & 0xff));

	if (inbuf[3] == 'd')
	{
		switch(inbuf[4])
		{
		case '0':
			__asm__ ("move.l	%0,%/d0\n" :: "m" (val) : "cc");
			break;
		case '1':
			__asm__ ("move.l	%0,%/d1\n" :: "m" (val) : "cc");
			break;
		case'2':
			__asm__ ("move.l	%0,%/d2\n" :: "m" (val) : "cc");
			break;
		case'3':
			__asm__ ("move.l	%0,%/d3\n" :: "m" (val) : "cc");
			break;
		case '4':
			__asm__ ("move.l	%0,%/d4\n" :: "m" (val) : "cc");
			break;
		case '5':
			__asm__ ("move.l	%0,%/d5\n" :: "m" (val) : "cc");
			break;
		case '6':
			__asm__ ("move.l	%0,%/d6\n" :: "m" (val) : "cc");
			break;
		case '7':
			__asm__ ("move.l	%0,%/d7\n" :: "m" (val) : "cc");
			break;
		default:
			return -1;
		}
	}
	else if (inbuf[3] == 'a')
	{
		switch(inbuf[4])
		{
		case '0':
			__asm__ ("move.l	%0,%/a0\n" :: "rm" (val) : "cc");
			break;
		case '1':
			__asm__ ("move.l	%0,%/a1\n" :: "rm" (val) : "cc");
			break;
		case'2':
			__asm__ ("move.l	%0,%/a2\n" :: "rm" (val) : "cc");
			break;
		case'3':
			__asm__ ("move.l	%0,%/a3\n" :: "rm" (val) : "cc");
			break;
		case '4':
			__asm__ ("move.l	%0,%/a4\n" :: "rm" (val) : "cc");
			break;
		case '5':
			__asm__ ("move.l	%0,%/a5\n" :: "rm" (val) : "cc");
			break;
		default:
			return -1;
		}
	}
	else
		return -1;
	return 0;
}

byte cm()
{
	char *saddr, *sval;
	word addr, val;
	register word i, j;

	saddr = &(inbuf[3]);
	sval = &(inbuf[8]);

	addr = 0;
	val = 0;
	for (i = 0; i < 2; i++)
	{
		j = ahtob(&(saddr[i*2]));
		if (j == -1)
			return -1;
		addr = (addr << 8) | (j & 0xff);
	}

	val = ahtob(sval);
	if (val == -1)
		return -1;

	*(byte *)((lword)addr & 0xffff) = val;

	return 0;
}

#define CONCAT_(a,b) a##b
#define CONCAT(a, b) CONCAT_(a,b)

#define CONVERTANDPRINTDOUBLE(r0, r1) \
	__asm__ ("move.l	%/"#r0",%0\n" :"=m" (val) :: "cc");\
	for (i = 3; i >= 0; i--)\
	{\
		btoah(val&0xff, &(out[i*2]));\
		val= val>>8;\
	}\
	out[8] = 0;\
	serial_puts(CONCAT(r0,s), 5);\
	serial_puts(out, 9);\
	__asm__ ("move.l	%/"#r1",%0\n" :"=m" (val) :: "cc");\
	for (i = 3; i >= 0; i--)\
	{\
		btoah(val&0xff, &(out[i*2]));\
		val= val>>8;\
	}\
	out[8] = '\r';\
	out[9] = '\n';\
	out[10] = 0;\
	serial_puts(CONCAT(r1,s), 6);\
	serial_puts(out, 11);

#define CONVERTANDPRINT(r0) \
	__asm__ ("move.l	%/"#r0",%0\n" :"=m" (val) :: "cc");\
	for (i = 3; i >= 0; i--)\
	{\
		btoah(val&0xff, &(out[i*2]));\
		val= val>>8;\
	}\
	out[8] = '\r';\
	out[9] = '\n';\
	out[10] = 0;\
	serial_puts(CONCAT(r0,s), 5);\
	serial_puts(out, 11);

byte dr()
{
	lword val;
	char out[11];
	register byte i;

	CONVERTANDPRINTDOUBLE(d0, a0);
	CONVERTANDPRINTDOUBLE(d1, a1);
	CONVERTANDPRINTDOUBLE(d2, a2);
	CONVERTANDPRINTDOUBLE(d3, a3);
	CONVERTANDPRINTDOUBLE(d4, a4);
	CONVERTANDPRINTDOUBLE(d5, a5);
	CONVERTANDPRINTDOUBLE(d6, fp);
	CONVERTANDPRINTDOUBLE(d7, sp);
	// CONVERTANDPRINT(pc);

	return 0;
}

byte dm()
{
	char *saddr, *slen;
	char header[7];
	char sbyte[4];
	word addr, len;
	register word i, j;

	saddr = &(inbuf[3]);
	slen = &(inbuf[8]);

	addr = 0;
	for (i = 0; i < 2; i++)
	{
		j = ahtob(&(saddr[i*2]));
		if (j == -1)
			return -1;
		addr = (addr << 8) | (j & 0xff);
	}

	len = ahtob(slen);
	if (len == -1)
		return -1;

	header[4] = ':';
	header[5] = ' ';
	header[6] = 0;
	sbyte[2] = ' ';
	sbyte[3] = 0;

	addr -= addr % 16;
	for (i = 0; i < len; i++)
	{
		btoah(addr >> 8, &(header[0]));
		btoah(addr & 0xff, &(header[2]));
		serial_puts(header, 7);

		for (j = 0; j < 16; j++)
		{
			btoah(*(byte *)((lword)addr & 0xffff), sbyte);
			serial_puts(sbyte, 4);
			addr++;
		}

		serial_putc('\r');
		serial_putc('\n');
	}

	return 0;
}

byte l()
{
// 	char inchar;
	int r;

	r = lsrec_begin();
	if (r != 0)
		return -1;
// lprompt:
// 	inbuf_len = 0;
// 	serial_puts(cursor, 3);
// lwaitc:
// 	while (!serial_isc())
// 		__asm__ __volatile__ ("nop");
// 	inchar = serial_getc();
// 	if (inchar == 3) // ctrl c
// 	{
// 		serial_putc('\r');
// 		serial_putc('\n');
// 		return 0;
// 	}
// 	else if (inchar == 8)
// 	{
// 		if (inbuf_len != 0)
// 		{
// 			inbuf_len--;
// 			serial_puts(delete, 6);
// 		}
// 	}
// 	else if (inchar == '\r')
// 	{
// 		inbuf[inbuf_len] = 0;
// 		serial_puts(delete, 6);
// 		goto leval;
// 	}
// 	else
// 	{
// 		inbuf[inbuf_len] = inchar;
// 		inbuf_len++;
// 	}
// 	serial_puts(cursor, 3);
// 	goto lwaitc;

leval:
	// inbuf[inbuf_len] = 0;
	// r = lsrec_in(inbuf, inbuf_len);
	for (int i = 0; i < 16; i++)
	{
		r = lsrec_in(hwproglines[i], hwproglines_len[i]-1);
		if (r != 0)
		{
			serial_puts(errstr, STR_SIZEOF(errstr));
			btoah(r, inbuf);
			inbuf[2] = 0;
			serial_puts(inbuf, 2);
			serial_putc('\r');
			serial_putc('\n');
			return r;
		}
	}
	// goto lprompt;
getentry:
	r = lsrec_end(&exec_entry_ptr);
	if (r != 0)
	{
		has_exec = 0;
		return -1;
	}

	// btoah(((lword)exec_entry_ptr >>  0) & 0xff, &(inbuf[6]));
	// btoah(((lword)exec_entry_ptr >>  8) & 0xff, &(inbuf[4]));
	// btoah(((lword)exec_entry_ptr >> 16) & 0xff, &(inbuf[2]));
	// btoah(((lword)exec_entry_ptr >> 24) & 0xff, &(inbuf[0]));
	// inbuf[8] = 0;
	// serial_puts(inbuf, 8);
	// serial_putc('\r');
	// serial_putc('\n');

	has_exec = 1;
	return 0;
}

byte r()
{
	if (!has_exec)
	{
		serial_puts(noexecloadedstr, STR_SIZEOF(noexecloadedstr));
		serial_puts(nlstr, STR_SIZEOF(nlstr));
		return -1;
	}
	return exec_entry_ptr();
}
