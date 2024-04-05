/*
 * convert.c
 * Richard Homan
 * 02/11/2024
 * Numerical <-> ASCII conversion utility
 */

#include "convert.h"
#include "err.h"

// char to half, -1 for error
int ctoh(char i, byte *ret);
// half to char, -1 for error (never)
char htoc(byte i);

int ahtob(const char *in, byte *ret)
{
	byte a, b;
	int i, r;

	a = 0;
	for (i = 0; i < 2; i++)
	{
		r = ctoh(in[i], &b);
		if (r != 0)
			return r;
		a = (a << 4) | b;
	}

	*ret = a;
	return 0;
}

int btoah(byte in, char *ret)
{
	ubyte h, l;
	h = (in >> 4) & 0xf;
	l = in & 0xf;
	ret[0] = htoc(h);
	ret[1] = htoc(l);
	return 0;
}

inline int ctoh(char i, byte *ret)
{
	if (i >= '0' && i <= '9' ) // digit
	{
		*ret = i - '0';
		return 0;
	}
	else if (i >= 'A' && i <= 'F') // valid upper letter
	{
		*ret = i - 'A' + 0xa;
		return 0;
	}
	else if (i >= 'a' && i <= 'f') // valid lower letter
	{
		*ret = i - 'a' + 0xa;
		return 0;
	}

	return EMS_NOT_HEX;
}

inline char htoc(byte i)
{
	if (i < 0xa)
		return i + '0';
	return i + 'a' - 0xa;
}
