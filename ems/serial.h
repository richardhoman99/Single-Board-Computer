/*
 * serial.h
 * Richard Homan
 * 02/11/2024
 * Declarations for serial control. Use sim make target for EASy68K simulator
 *	target.
 */

#include "types.h"

#ifndef SERIAL_H
#define SERIAL_H

void serial_init();
void serial_puts(const char *, int);
void serial_putc(char);
byte serial_isc();
char serial_getc();

#endif
