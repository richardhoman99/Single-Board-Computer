/*
 * ems_dr.c
 * Richard Homan
 * 02/17/2024
 * Dump registers logic for Enemigo Monitor System
 */

#include "types.h"
#include "convert.h"
#include "serial.h"

const char d0_str[] = "d0";
const char d1_str[] = "d1";
const char d2_str[] = "d2";
const char d3_str[] = "d3";
const char d4_str[] = "d4";
const char d5_str[] = "d5";
const char d6_str[] = "d6";
const char d7_str[] = "d7";
const char a0_str[] = "a0";
const char a1_str[] = "a1";
const char a2_str[] = "a2";
const char a3_str[] = "a3";
const char a4_str[] = "a4";
const char a5_str[] = "a5";
const char fp_str[] = "fp";
const char sp_str[] = "sp";

const char *reg_str[] =
{
	d0_str,	a0_str,
	d1_str,	a1_str,
	d2_str,	a2_str,
	d3_str,	a3_str,
	d4_str,	a4_str,
	d5_str,	a5_str,
	d6_str,	fp_str,
	d7_str,	sp_str
};

#define GET_REG(r, o) __asm__ ("move.l	%/"#r",%0\n" :"=m" (o) :: "cc");

// no arguments
int ems_dr(const char **argv, int argc)
{
	lword v[16];
	char out[28];
	register int i, j;

	GET_REG(d0, v[ 0]);	GET_REG(a0, v[ 1]);
	GET_REG(d1, v[ 2]);	GET_REG(a1, v[ 3]);
	GET_REG(d2, v[ 4]);	GET_REG(a2, v[ 5]);
	GET_REG(d3, v[ 6]);	GET_REG(a3, v[ 7]);
	GET_REG(d4, v[ 8]);	GET_REG(a4, v[ 9]);
	GET_REG(d5, v[10]);	GET_REG(a5, v[11]);
	GET_REG(d6, v[12]);	GET_REG(fp, v[13]);
	GET_REG(d7, v[14]);	GET_REG(sp, v[15]);

	out[2] = ':';
	out[3] = ' ';
	out[12] = ' ';
	out[15] = ':';
	out[16] = ' ';
	out[25] = '\r';
	out[26] = '\n';
	out[27] = '\0';
	for (i = 0; i < 16; )
	{
		// set reg names to out string
		out[0] = reg_str[i][0];
		out[1] = reg_str[i][1];
		out[13] = reg_str[i+1][0];
		out[14] = reg_str[i+1][1];

		for (j = 6; j >= 0; j-=2)
		{
			btoah(v[i] & 0xff, &(out[j+4]));
			v[i] = v[i] >> 8;
		}
		i++;
		for (j = 6; j >= 0; j-=2)
		{
			btoah(v[i] & 0xff, &(out[j+17]));
			v[i] = v[i] >> 8;
		}
		i++;

		serial_puts(out, ARR_LEN(out));
	}

	return 0;
}
