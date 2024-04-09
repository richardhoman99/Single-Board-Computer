/*
 * main.c
 * Richard Homan
 * 02/17/2024
 * Entry point for x20 game
 */

#include "types.h"
#include "convert.h"
#include "serial.h"

#define ARR_LEN(v) sizeof(v)/sizeof(v[0])

const ubyte random_insertion[8] = { 1, 2, 1, 1, 2, 1, 1, 1}

const char clr_screen_str[] = "\033[2J";
const char row_divider_str[] = "+--+--+--+";
const char nl_str[] = "\r\n";
const char blank_str[] = "  ";

ubyte board_values[3][3];

void draw();
void init_values();
void clear_screen();

void move_left();
void move_right();
void move_up();
void move_down();

void move_ascending(int transpose);
void move_decending(int transpose);
ubyte *value_ptr(int r, int c, int t); // 1 for transpose row and column

int zeros();

int main(void)
{
	char c;

	init_values();

poll_user:
	draw();
	while (!serial_isc()) ;
	c = serial_getc();



	switch (c)
	{
	case 'i':
		move_up();
		break;
	case 'k':
		move_down();
		break;
	case 'j':
		move_left();
		break;
	case 'l':
		move_right();
		break;
	default:
		break;
	}

	goto poll_user;

	while (1)
		asm __volatile__ ("nop");
	return 0;
}

void draw()
{
	register int i, j;
	char obuf[3];
	ubyte b;

	obuf[2] = '\0';
	clear_screen();
	serial_puts(row_divider_str, ARR_LEN(row_divider_str));
	serial_puts(nl_str, ARR_LEN(nl_str));

	for (i = 0; i < 3; i++)
	{
		serial_putc('|');
		for (j = 0; j < 3; j++)
		{
			b = board_values[i][j];
			if (b == 0)
			{
				serial_puts(blank_str, ARR_LEN(blank_str));
			}
			else
			{
				btoah(board_values[i][j], &(obuf[0]));
				serial_puts(obuf, 2);
			}
			serial_putc('|');
		}

		serial_puts(nl_str, ARR_LEN(nl_str));
		serial_puts(row_divider_str, ARR_LEN(row_divider_str));
		serial_puts(nl_str, ARR_LEN(nl_str));
	}
}

ubyte *value_ptr(int r, int c, int transpose)
{
	if (transpose) // column first
		return &(board_values[c][r]);
	// row first
	return &(board_values[r][c]);
}

void move_ascending(int transpose)
{
	register int row, col, col1;
	ubyte b;
	ubyte move[3];
	ubyte move_len;

	for (row = 0; row < 3; row++)
	{
		move_len = 0;
		for (col = 0; col < 3; col++)
		{
			b = *value_ptr(row, col, transpose);
			if (b != 0)
			{
				move[move_len++] = b;
			}
		}

		for (col = 1; col < move_len; col++)
		{
			if (move[col-1] == move[col])
			{
				move[col-1] = move[col] << 1;
				move[col] = 0;
			}
		}

		col = 0;
		for(col1 = 0; col1 < move_len; col1++)
		{
			b = move[col1];
			if (b != 0)
			{
				*value_ptr(row, col, transpose) = move[col1];
				col++;
			}
		}

		for (; col < 3; col++)
			*value_ptr(row, col, transpose) = 0;
	}
}

void move_decending(int transpose)
{
	register int row, col, col1;
	ubyte b;
	ubyte move[3];
	ubyte move_len;

	for (row = 0; row < 3; row++)
	{
		move_len = 3;
		for (col = 2; col >= 0; col--)
		{
			b = *value_ptr(row, col, transpose);
			if (b != 0)
			{
				move[--move_len] = b;
			}
		}

		for (col = 1; col >= move_len; col--)
		{
			if (move[col+1] == move[col])
			{
				move[col+1] = move[col] << 1;
				move[col] = 0;
			}
		}

		col = 2;
		for(col1 = 2; col1 >= move_len; col1--)
		{
			b = move[col1];
			if (b != 0)
			{
				*value_ptr(row, col, transpose) = move[col1];
				col--;
			}
		}

		for (; col >= 0; col--)
			*value_ptr(row, col, transpose) = 0;
	}
}

inline void move_left()		{ move_ascending(0); }
inline void move_right()	{ move_decending(0); }
inline void move_up()		{ move_ascending(1); }
inline void move_down()		{ move_decending(1); }

inline
void init_values()
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			board_values[i][j] = 0;
		}
	}

	board_values[0][0] = 1;
	board_values[0][1] = 2;
	board_values[0][2] = 1;

	board_values[1][1] = 8;
}

inline int zeros()
{
	register int i, j, c;
	ubyte b;

	c = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			b = board_values[i][j];
			if (b == 0)
				c++;
		}
	}
	return c;
}

inline
void clear_screen()
{
#ifndef SIM
	serial_puts(clr_screen_str, ARR_LEN(clr_screen_str));
#else
	__asm__ __volatile__ ("move.l	%/d1,-(%/sp)\n"		// save registers
						  "move.l	%/d0,-(%/sp)\n"
						  "move.l	#0xff00,%/d1\n"		// clear screen
						  "move.w	#11,%/d0\n"			// task 11
						  "trap		#15\n"				// trap 15: SIM tasks
						  "move.l	(%/sp)+,%/d0\n"		// restore registers
						  "move.l	(%/sp)+,%/d1\n"
						  ::: "cc", "memory");
	return;
#endif
}