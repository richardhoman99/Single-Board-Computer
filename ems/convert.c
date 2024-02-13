/*
 * convert.c
 * Richard Homan
 * 02/11/2024
 * Numerical <-> ASCII conversion utility
 */

#include "convert.h"

// char to half, -1 for error
byte ctoh(char i);
// half to char, -1 for error (never)
char htoc(ubyte i);

word ahtob(char *in)
{
	word h, l;
	h = ctoh(in[0]);
	if (h == -1)
		return -1;
	l = ctoh(in[1]);
	if (l == -1)
		return -1;
	return (h << 4) | l;
}

void btoah(byte in, char *ret)
{
	ubyte h, l;
	h = (in >> 4) & 0xf;
	l = in & 0xf;
	ret[0] = htoc(h);
	ret[1] = htoc(l);
}

inline byte ctoh(char i)
{
	if (i >= '0' && i <= '9' ) // digit
	{
		return i - '0';
	}
	else if (i >= 'A' && i <= 'F') // valid upper letter
	{
		return i - 'A' + 0xa;
	}
	else if (i >= 'a' && i <= 'f') // valid lower letter
	{
		return i - 'a' + 0xa;
	}

	return -1;
}

inline char htoc(ubyte i)
{
	if (i < 0xa)
		return i + '0';
	return i + 'a' - 0xa;
}
