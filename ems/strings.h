/*
 * strings.h
 * Richard Homan
 * 02/18/2024
 * Common strings for Enemigo Monitor System
 */

#ifndef STRINGS_H
#define STRINGS_H

#define REVISION "0.02"

#define ARR_LEN(a) sizeof(a)/sizeof(a[0])

extern const char welcome_str[];
extern const int  WELCOME_STR_LEN;

extern const char nl_str[];
extern const int  NL_STR_LEN;

extern const char err_str[];
extern const int  ERR_STR_LEN;

extern const char del_str[];
extern const int  DEL_STR_LEN;

#ifdef SIM
extern const char cur_str[];
extern const int  CUR_STR_LEN;
#endif

#endif
