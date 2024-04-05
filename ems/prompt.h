/*
 * prompt.h
 * Richard Homan
 * 04/03/2024
 * String input prompt routine for Enemigo Monitor System
 */

#ifndef PROMPT_H
#define PROMPT_H

// inbuf: buffer to put users string into
// size : size of input buffer
// escc : optional escape character ('\0' or 0 for none)
// ret  : the length of the buffer written or an error code
int user_prompt(char *inbuf,         int inbuf_size,
				const char *pmt_str, int pmt_str_len,
				char escc);

#endif
