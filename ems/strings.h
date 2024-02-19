/*
 * strings.h
 * Richard Homan
 * 02/18/2024
 * Common strings for Enemigo Monitor System
 */

#ifndef STRINGS_H
#define STRINGS_H

extern const char del_str[];// = " \b\b \b";
#define DEL_STR_LEN sizeof(" \b\b \b")/sizeof(char)
extern const char cur_str[];// = "_\b";
#define CUR_STR_LEN sizeof("_\b")/sizeof(char)
extern const char nl_str [];// = "\r\n";
#define NL_STR_LEN  sizeof("\r\n")/sizeof(char)
extern const char err_str[];// = "error ";
#define ERR_STR_LEN sizeof("error ")/sizeof(char)

#endif
