/*
 * lsrec.c
 * Richard Homan
 * 02/12/2024
 * Parser and loader of srec executables for Enemigo Monitor System
 */

#include "lsrec.h"
#include "convert.h"

static byte lsrec_parsing = 0;
static word s1_record_count;
static lword entry;
static lword dbeginaddr;
static lword dendaddr;
static lword err;
static word err_loc, err_len;

lword srec_gtype(char *); // get type
lword srec_gcount(char *); // get count
lword srec_gaddr(char *); // get address
lword srec_gdatab(char *, word); // gets one byte from data section

// returns -1 on already parsing
int lsrec_begin()
{
	if (lsrec_parsing != 0)
		return -1;

	lsrec_parsing = 1;
	s1_record_count = 0;
	dbeginaddr = 0xffffffff;
	dendaddr = 0x00000000;
	err = 0;
	return 0;
}

int lsrec_in(char *recstr, byte len)
{
	lword type, count, addr;
	register byte idx;
	lword calc_chksum, chksum;
	
	err = 0;
	if (len < 10) // absolute minimum length is 10
		return LSREC_ERR_NOT_SREC_FORMAT;

	if (entry != 0)
	{
		err_loc = 0;
		err_len = 2;
		err = LSREC_ERR_DATA_GIVEN_AFTER_ENTRY;
		return err;
	}

	type = srec_gtype(recstr);
	if (type == LSREC_ERR_NOT_SREC_FORMAT)
		return LSREC_ERR_NOT_SREC_FORMAT;
	// only support word addresses (2 bytes)
	switch (type)
	{
	case 0: return LSREC_SUCCESS; // ignore S0
	case 2:
	case 3:
	case 4:
	case 6:
	case 7:
	case 8:
		err_loc = 0;
		err_len = 2;
	default:
		break;
	}
	switch (type)
	{
	case 2: err = LSREC_ERR_UNSUPPORTED_TYPE_S2;
	case 3: err = LSREC_ERR_UNSUPPORTED_TYPE_S3;
	case 4: err = LSREC_ERR_UNSUPPORTED_TYPE_S4;
	case 6: err = LSREC_ERR_UNSUPPORTED_TYPE_S6;
	case 7: err = LSREC_ERR_UNSUPPORTED_TYPE_S7;
	case 8: err = LSREC_ERR_UNSUPPORTED_TYPE_S8;
	default:
		break;
	}
	if (err != 0)
		return err;

	count = srec_gcount(recstr);
	if (count < 0)
		return count; // actually returning the error
	if (count * 2 != len - 5)
	{
		err_loc = 2;
		err_len = 2;
		err = LSREC_ERR_LENGTH_NONEQUAL;
		return err;
	}

	if (type == 5) // check that the encountered records is what this record says
	{
		if (count != 3)
		{
			err_loc = 0;
			err_len = 2;
			err = LSREC_ERR_INVALID_FORMAT;
			return err;
		}

		lword n = srec_gaddr(recstr); // count is in addr location
		if (n < 0)
			return err;

		if (n != s1_record_count)
		{
			err_loc = 4;
			err_len = 4;
			err = LSREC_ERR_RECORD_COUNT_NONEQUAL;
			return err;
		}

		s1_record_count = 0;
		return LSREC_SUCCESS;
	}
	if (type == 9) // entry is specified
	{
		if (count != 3)
		{
			err_loc = 0;
			err_len = 2;
			err = LSREC_ERR_INVALID_FORMAT;
			return err;
		}

		lword e = srec_gaddr(recstr); // count is in addr location
		if (e < 0)
			return err;
		
		if (e < dbeginaddr || e > dendaddr)
		{
			err_loc = 4;
			err_len = 4;
			err = LSREC_ERR_ENTRY_OUT_OF_BOUNDS;
			return err;
		}

		entry = e;
		return LSREC_SUCCESS;
	}

	s1_record_count++;
	addr = srec_gaddr(recstr);
	if (addr < 0)
		return addr; // acturally returning error
	if (addr < 0x8000 || addr > 0xffff) // out of bounds
	{
		err_loc = 4;
		err_len = 4;
		err = LSREC_ERR_ADDRESS_OUT_OF_BOUNDS;
		return err;
	}
	if (addr + count - 2 - 1 > 0xfff) // subtract out address and checksum
	{
		err_loc = 2;
		err_len = 2;
		err = LSREC_ERR_LENGTH_EXTENDS_OUT_OF_BOUNDS;
		return err;
	}
	if (addr < dbeginaddr)
		dbeginaddr = addr;
	else if (addr > dendaddr)
		dendaddr = addr;

	calc_chksum = 0;
	for (idx = 0; idx < (byte)count-1; idx++)
	{
		byte *baddr;
		byte b;

		b = srec_gdatab(recstr, idx);
		calc_chksum += b;

		baddr = (byte *)((lword)addr + (lword)idx);
		*baddr = b;
	}

	calc_chksum = 0xff - (calc_chksum & 0xff);
	chksum = srec_gdatab(recstr, (byte)count-1);
	if (calc_chksum != chksum)
	{
		err_loc = len-2;
		err_len = 2;
		err = LSREC_ERR_INVALID_CHECKSUM;
		return err;
	}

	return LSREC_SUCCESS;
}

// returns -1 on not parsing
int lsrec_end(lword *entryptr)
{
	if (lsrec_parsing != 1)
		return -1;

	lsrec_parsing = 0;
	*entryptr = entry;
	return 0;
}

// returns descriptive error given an error
void lsrec_errstr(char *errstr, byte len)
{

}

lword srec_gtype(char *recstr)
{
	if ((recstr[0] != 'S') ||
		!(recstr[1] >= '0' && recstr[1] <= '9'))
	{
		err_loc = 0;
		err_len = 2;
		err = LSREC_ERR_NOT_SREC_FORMAT;
		return err;
	}

	return (recstr[1] - '0');
}

lword srec_gcount(char *recstr)
{
	word c;
	c = ahtob(&(recstr[2]));
	if (c == -1)
	{
		err_loc = 2;
		err_len = 2;
		err = LSREC_ERR_INVALID_HEX;
		return err;
	}
	return c;
}

lword srec_gaddr(char *recstr)
{
	word h, l;
	h = ahtob(&(recstr[4]));
	if (h == -1)
	{
		err_loc = 4;
		err_len = 4;
		err = LSREC_ERR_INVALID_HEX;
		return err;
	}
	l = ahtob(&(recstr[6]));
	if (l == -1)
	{
		err_loc = 4;
		err_len = 4;
		err = LSREC_ERR_INVALID_HEX;
		return err;
	}
	l = (h << 8) | l;
	return l;
}

lword srec_gdatab(char *recstr, word byte_num)
{
	const word b_idx = 2+2+4+(byte_num*2);
	word b;

	b = ahtob(&(recstr[b_idx]));
	if (b == -1)
	{
		err_loc = b_idx;
		err_len = 2;
		err = LSREC_ERR_INVALID_HEX;
		return err;
	}
	return b;
}
