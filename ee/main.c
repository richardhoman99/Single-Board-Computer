/*
 * main.c
 * Richard Homan
 * 02/17/2024
 * Entry point for 80h game
 */

#include "types.h"
#include "convert.h"
#include "serial.h"

#define ARR_LEN(v) sizeof(v)/sizeof(v[0])

#define MOVE_LEFT(mutate)	move(mutate, 0, 0)
#define MOVE_RIGHT(mutate)	move(mutate, 1, 0)
#define MOVE_UP(mutate)		move(mutate, 0, 1)
#define MOVE_DOWN(mutate)	move(mutate, 1, 1)

#define WIN_NUM	0x80

const char clr_screen_str[] = "\033[2J";
const char row_divider_str[] = "+--+--+--+";
const char loss_str[] = "Game Over";
const char win_str[] = "You Win!";
const char nl_str[] = "\r\n";
const char blank_str[] = "  ";

ubyte board_values[3][3] __attribute__ ((aligned (4)));

void draw();
void init_values();
void clear_screen();

int order_init(int order);
int order_compare(int val, int low, int high, int order);
int order_next(int val, int order);
ubyte *value_ptr(int r, int c, int t); // 1 for transpose row and column
// >= 2 if 0x80 was reached, 1 if made changes, 0 otherwise
int move(int mutate, int order, int transpose);
// 1 if insertion could be made, 0 otherwise (game over)
// move_count use as "random generation seed"
int insert(int move_count);

int main(void)
{
	char c;
	int count, change;

	init_values();
	count = 0;

poll_user:
	draw();

	while (!serial_isc()) ;
	c = serial_getc();

	switch (c)
	{
	case 'i':
		change = MOVE_UP(1);
		break;
	case 'k':
		change = MOVE_DOWN(1);
		break;
	case 'j':
		change = MOVE_LEFT(1);
		break;
	case 'l':
		change = MOVE_RIGHT(1);
		break;
	default:
		change = 0;
		break;
	}

	if (change == 1)
	{
		if (!insert(count))
		{
			// couldn't insert any values, game over
			draw(); // show user the final board
			serial_puts(loss_str, ARR_LEN(loss_str));
			serial_puts(nl_str, ARR_LEN(nl_str));
			return 0;
		}
		count++;
	}
	else if (change >= 2)
	{
		draw();
		serial_puts(win_str, ARR_LEN(win_str));
		serial_puts(nl_str, ARR_LEN(nl_str));
		return 0;
	}

	goto poll_user;

	while (1)
		asm __volatile__ ("nop");
	return 0;
}

inline
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

int insert(int move_count)
{
	register int i;
	int s;
	register ubyte *p;
	
	i = move_count % 8;
	if (move_count % 2 == 0)
		i = 9-i;
	s = i;
	do
	{
		p = (ubyte *)((ubyte *)board_values + (ulword)i);
		if (*p == 0)
		{
			*p = move_count % 8 == 0 ? 2 : 1;
			s = 0;
			// check that we have more moves
			for (i = 0; i < 4; i++)
				s = s || move(0, i & 0x1, i & 0x2);
			return s;
		}
		i++;
		if (i >= 9)
			i = 0;
	}
	while (i != s);

	// no more open spots, no more moves
	return 0;
}

// 0,0: left
// 1,0: right
// 0,1: up
// 1,1: down
int move(int mutate, int order, int transpose)
{
	register int row, col, idx, len, n, c;
	register ubyte b;
	ubyte move[3];

	c = 0;
	for (row = 0; row < 3; row++)
	{
		len = !order ? order_init(order) : order_init(order)+1;
		for (col = order_init(order);
			 order_compare(col, 0, 3, order);
			 col = order_next(col, order))
		{
			b = *value_ptr(row, col, transpose);
			if (b != 0)
			{
				if (order) // predecrement
					len = order_next(len, order);
				move[len] = b;
				if (!order) // postincrement
					len = order_next(len, order);
			}
		}

		for (col = 1;
			 order_compare(col, len, len, order);
			 col = order_next(col, order))
		{
			n = order_next(col, !order);
			if (move[n] == move[col])
			{
				move[n] = move[n] << 1;
				move[col] = 0;
				if (move[n] == WIN_NUM)
					c = 2;
				else
					c |= 1; // keep win state
			}
		}

		col = order_init(order);
		for (idx = order_init(order);
			 order_compare(idx, len, len, order);
			 idx = order_next(idx, order))
		{
			b = move[idx];
			if (b != 0)
			{
				c = c | (*value_ptr(row, col, transpose) != move[idx]);
				if (mutate) *value_ptr(row, col, transpose) = move[idx];
				col = order_next(col, order);
			}
		}

		if (mutate)
		{
			for (;
				 order_compare(col, 0, 3, order);
				 col = order_next(col, order))
			{
				*value_ptr(row, col, transpose) = 0;
			}
		}
	}

	return c;
}

int order_init(int order)
{
	if (!order) // begin at bottom
		return 0;
	return 2; // begin at top
}

int order_compare(int val, int low, int high, int order)
{
	if (!order)
		return val < high;
	return val >= low;
}

int order_next(int val, int order)
{
	if (!order)
		return val+1;
	return val-1;
}

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
	board_values[0][2] = 1;
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