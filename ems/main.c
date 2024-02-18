/*
 * main.c
 * Richard Homan
 * 02/11/2024
 * Entry point for Enemigo Monitor System
 */

#include "types.h"
#include "convert.h"
#include "serial-sim.h"
#include "command.h"

#define STR_SIZEOF(v) sizeof(v)/sizeof(v[0])
#define INBUF_LEN 64

const char inv_comm_str[] = "unknown command\r\n";
const char bad_arg_str[] = "bad argument\r\n";
const char d0_str[] = "d0: ";
const char d1_str[] = "d1: ";
const char d2_str[] = "d2: ";
const char d3_str[] = "d3: ";
const char d4_str[] = "d4: ";
const char d5_str[] = "d5: ";
const char d6_str[] = "d6: ";
const char d7_str[] = "d7: ";
const char a0_str[] = " a0: ";
const char a1_str[] = " a1: ";
const char a2_str[] = " a2: ";
const char a3_str[] = " a3: ";
const char a4_str[] = " a4: ";
const char a5_str[] = " a5: ";
const char fp_str[] = " fp: ";
const char sp_str[] = " sp: ";
const char err_str[] = "error ";
const char noexecload_str[] = "no executable loaded";

const char help_str0 = "cr [reg] [val] : change register";
const char help_str1 = "cm [loc] [val] : change memory";
const char help_str2 = "dr             : dump registers";
const char help_str3 = "dm [loc] [len] : dump memory";
const char help_str4 = "l              : load srecord executable";
const char help_str5 = "r              : run srecord executable";
const char help_str6 = "h              : display this message";

const char *help_str[]
{
	help_str0,
	help_str1,
	help_str2,
	help_str3,
	help_str4,
	help_str5,
	help_str6
};

const char *help_str_len[]
{
	STR_SIZEOF(help_str0),
	STR_SIZEOF(help_str1),
	STR_SIZEOF(help_str2),
	STR_SIZEOF(help_str3),
	STR_SIZEOF(help_str4),
	STR_SIZEOF(help_str5),
	STR_SIZEOF(help_str6)
};

const char pmt_str[] = "ems% _\b";
const char del_str[] = " \b\b \b";
const char cur_str[] = "_\b";
const char nl_str[] = "\r\n";

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

static char inbuf[INBUF_LEN];
static byte inbuf_len;
static byte has_exec;
static int (*exec_entry_ptr)(void);

int main(void)
{
	char inchar;

	has_exec = 0;

mpmt:
	inbuf_len = 0;
	serial_puts(pmt_str, STR_SIZEOF(pmt_str));

mwaitc:
	while (!serial_isc()) // wait for next character
		__asm__ __volatile__ ("nop");

	inchar = serial_getc();
	if (inchar == '\r') // on return key
	{
		inbuf[inbuf_len++] = ' ';
		inbuf[inbuf_len++] = '\0'; // add null terminator
		serial_puts(del_str, STR_SIZEOF(del_str));
		goto meval;
	}
	if (inchar == '\b') // on delete key
	{
		if (inbuf_len != 0)
		{
			inbuf_len--;
			serial_puts(del_str, STR_SIZEOF(del_str));
		}
	}
	else // any other input
	{
		if(inbuf_len >= INBUF_LEN-2) // buffer overflow protection
		{							 // sub 2 because we add ' ' and '\0' at end
			serial_puts(del_str, STR_SIZEOF(cur_str)); // eat char off terminal
		}
		else
		{
			inbuf[inbuf_len] = inchar;
			inbuf_len++;
		}
	}
	serial_puts(cur_str, STR_SIZEOF(cur_str));
	goto mwaitc;

meval:
	// parse by char in sequence
	if (inbuf[0] == 'c')
	{
		if (inbuf[1] == 'r')
		{
			if (inbuf[2] != ' ')
				goto prnt_inv_comm;
			handle(cr());
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

goto mpmt;
print_invalid:
	serial_puts(invalid, 17);
goto mpmt;
print_badarg:
	serial_puts(badarg, 15);
goto mpmt;

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}
