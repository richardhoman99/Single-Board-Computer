/*
 * lsrec.c
 * Richard Homan
 * 02/12/2024
 * Parser and loader of srec executables for Enemigo Monitor System
 */

#include "lsrec.h"
#include "convert.h"

static uword drec_count;
static ubyte has_entry;
static ulword dbegin_addr;
static ulword dend_addr;
static lword err;

int srec_gtype(const char *, ubyte *); // get type
int srec_gcount(const char *, ubyte *); // get count
int srec_gaddr(const char *, uword *); // get address
int srec_gdatab(const char *, ubyte, ubyte *); // gets one byte from data section

void lsrec_init()
{
	drec_count = 0;
	dbegin_addr = LSREC_MAX_ADDR;
	dend_addr = LSREC_MIN_ADDR;
	has_entry = 0;
	err = 0;
}

int lsrec_in(const char *recstr, ubyte len, int (**entry_func)(void))
{
	register int i, r;
	ubyte type, count, calc_chksum, chksum;
	uword addr;
	
	err = 0;
	len -= 1;
	if (len < 10) // absolute minimum length is 10
		return LSREC_ERR_NOT_SREC_FORMAT;

	if (has_entry)  // entry should be the last value given, if we get any more
					// records, give an error
	{
		err = LSREC_ERR_DATA_GIVEN_AFTER_ENTRY;
		return err;
	}

	*entry_func = 0x0;

	// get type value
	r = srec_gtype(recstr, &type);
	if (r < 0)
	{
		err = r;
		return r;
	}

	switch (type) // don't support S2, S3, S4, S6, S7, S8
	{
	case 2: err = LSREC_ERR_UNSUPPORTED_TYPE_S2;
		err = LSREC_ERR_UNSUPPORTED_TYPE_S2;
		break;
	case 3: err = LSREC_ERR_UNSUPPORTED_TYPE_S3;
		err = LSREC_ERR_UNSUPPORTED_TYPE_S3;
		break;
	case 4: err = LSREC_ERR_UNSUPPORTED_TYPE_S4;
		err = LSREC_ERR_UNSUPPORTED_TYPE_S4;
		break;
	case 6: err = LSREC_ERR_UNSUPPORTED_TYPE_S6;
		err = LSREC_ERR_UNSUPPORTED_TYPE_S6;
		break;
	case 7: err = LSREC_ERR_UNSUPPORTED_TYPE_S7;
		err = LSREC_ERR_UNSUPPORTED_TYPE_S7;
		break;
	case 8: err = LSREC_ERR_UNSUPPORTED_TYPE_S8;
		err = LSREC_ERR_UNSUPPORTED_TYPE_S8;
		break;
	default:
		break;
	}
	if (err != 0)
		return err;

	// get count value
	r = srec_gcount(recstr, &count);
	if (r < 0)
	{
		err = r;
		return r;
	}

	if (count * 2 != len - 4) // check that actual length matches said count
	{
		err = LSREC_ERR_LENGTH_NONEQUAL;
		return err;
	}

	// get address value
	r = srec_gaddr(recstr, &addr);
	if (r != 0)
	{
		err = r;
		return r;
	}

	if (type == 5) // verify that we got the number of S1 records specified
				   // in S5
	{
		if (count != 3) // S5 record count should only be 3
		{
			err = LSREC_ERR_INVALID_FORMAT;
			return err;
		}

		if (addr != drec_count) // value is contained in address
		{
			err = LSREC_ERR_RECORD_COUNT_NONEQUAL;
			return err;
		}

		drec_count = 0;
		return LSREC_SUCCESS;
	}
	if (type == 9) // entry is specified
	{
		if (count != 3) // S9 record count should only be 3
		{
			err = LSREC_ERR_INVALID_FORMAT;
			return err;
		}
		
		if (addr < dbegin_addr || addr > dend_addr)
		{
			err = LSREC_ERR_ENTRY_OUT_OF_BOUNDS;
			return err;
		}

		// cast to ulword then to func pointer
		*entry_func = (int (*)(void))(ulword)addr;
		return LSREC_SUCCESS;
	}

	drec_count++; // if we got to this point, then we have a data record
	 // verify that the address isn't out of bounds
	if (addr < LSREC_MIN_ADDR || addr > LSREC_MAX_ADDR)
	{
		err = LSREC_ERR_ADDRESS_OUT_OF_BOUNDS;
		return err;
	}
	// subtract out address and checksum and verify that memory doesn't go out
	// of bounds
	if (addr + count - 2 - 1 > LSREC_MAX_ADDR)
	{
		err = LSREC_ERR_LENGTH_EXTENDS_OUT_OF_BOUNDS;
		return err;
	}
	// update min and max given values
	if (addr < dbegin_addr)
		dbegin_addr = addr;
	else if (addr > dend_addr)
		dend_addr = addr;

	// initialize calculated checksum
	calc_chksum = count +
				  (addr >> 8 & 0xff) + // add addr high
				  (addr & 0xff); // add addr low
	for (i = 0; i < count-2-1; i++)
	{
		ubyte *baddr;
		ubyte b;

		r = srec_gdatab(recstr, i, &b);
		if (r != 0)
		{
			err = r;
			return r;
		}
		calc_chksum += b;

		baddr = (ubyte *)((ulword)addr + (ulword)i);
		*baddr = b;
	}

	calc_chksum = 0xff - (calc_chksum & 0xff); // do final calculation
	r = srec_gdatab(recstr, count-3, &chksum);
	if (r != 0)
	{
		err = r;
		return r;
	}

	return LSREC_SUCCESS;
}

int srec_gtype(const char *recstr, ubyte *ret)
{
	if ((recstr[0] != 'S') ||
		!(recstr[1] >= '0' && recstr[1] <= '9'))
	{
		err = LSREC_ERR_NOT_SREC_FORMAT;
		return err;
	}

	*ret = (byte)(recstr[1] - '0');
	return 0;
}

int srec_gcount(const char *recstr, ubyte *ret)
{
	ubyte b;
	int r;

	r = ahtob(&(recstr[2]), &b);
	if (r != 0)
		return r;

	*ret = b;
	return 0;
}

int srec_gaddr(const char *recstr, uword *ret)
{
	ubyte b;
	uword addr;
	register int i, r;

	addr = 0;
	for (i = 4; i < 7; i+=2)
	{
		r = ahtob(&(recstr[i]), &b);
		if (r != 0)
			return r;
		addr = (addr << 8) | b;
	}

	*ret = addr;
	return 0;
}

int srec_gdatab(const char *recstr, ubyte byte_num, ubyte *ret)
{
	const ubyte b_idx = 2+2+4+(byte_num*2);
	ubyte b;
	register int r;

	r = ahtob(&(recstr[b_idx]), &b);
	if (r != 0)
		return r;

	*ret = b;
	return 0;
}
