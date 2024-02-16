/*
 * lsrec_errstr.h
 * Richard Homan
 * 02/15/2024
 * SREC loader error strings for Enemigo Monitor System
 */

const char *lsrec_errstr_tab[] = 
{
	lsrec_errstr_success,
	lsrec_errstr_not_srec_format,
	lsrec_errstr_unsupported_type_s2,
	lsrec_errstr_unsupported_type_s3,
	lsrec_errstr_unsupported_type_s4,
	lsrec_errstr_unsupported_type_s6,
	lsrec_errstr_unsupported_type_s7,
	lsrec_errstr_unsupported_type_s8,
	lsrec_errstr_address_out_of_bounds,
	lsrec_errstr_length_nonequal,
	lsrec_errstr_length_extends_out_of_bounds,
	lsrec_errstr_invalid_checksum,
	lsrec_errstr_record_count_nonequal,
	lsrec_errstr_entry_out_of_bounds,
	lsrec_errstr_data_given_after_entry,
	lsrec_errstr_invalid_format,
	lsrec_errstr_invalid_hex
};

const char lsrec_errstr_success[] = 
"";
const char lsrec_errstr_not_srec_format[] = 
"not srec format";
const char lsrec_errstr_unsupported_type_s2[] = 
"S2";
const char lsrec_errstr_unsupported_type_s3[] = 
"S3";
const char lsrec_errstr_unsupported_type_s4[] = 
"S4";
const char lsrec_errstr_unsupported_type_s6[] = 
"S6";
const char lsrec_errstr_unsupported_type_s7[] = 
"S7";
const char lsrec_errstr_unsupported_type_s8[] = 
"S8";
const char lsrec_errstr_address_out_of_bounds[] = 
"address out of memory bounds";
const char lsrec_errstr_length_nonequal[] = 
"count does not match actual count";
const char lsrec_errstr_length_extends_out_of_bounds[] = 
"address+count extends out of memory bounds";
const char lsrec_errstr_invalid_checksum[] = 
"invalid checksum";
const char lsrec_errstr_record_count_nonequal[] = 
"count of given records does not equal actual given";
const char lsrec_errstr_entry_out_of_bounds[] = 
"entry point is not defined in given address space";
const char lsrec_errstr_data_given_after_entry[] = 
"data record given after entry point record";
const char lsrec_errstr_invalid_format[] = 
"given record format does not match specification";
const char lsrec_errstr_invalid_hex[] = 
"value is not hex";

const char lsrec_errstr_unsupported_type[] =
"unsupported type: ";
