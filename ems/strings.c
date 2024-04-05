/*
 * strings.c
 * Richard Homan
 * 04/03/2024
 * Common strings for Enemigo Monitor System
 */

#include "strings.h"

const char nl_str[]   = "\r\n";
const int  NL_STR_LEN = ARR_LEN(nl_str);

const char err_str[]   = "error ";
const int  ERR_STR_LEN = ARR_LEN(err_str);

#ifdef SIM
const char cur_str[]   = "_\b";
const int  CUR_STR_LEN = ARR_LEN(cur_str);

const char del_str[]   = " \b \b\b";
const int  DEL_STR_LEN = ARR_LEN(del_str);
#endif
