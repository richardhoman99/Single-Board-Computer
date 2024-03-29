/*
 * serial.h
 * Richard Homan
 * 02/11/2024
 * Declarations for serial control. Uncomment the SIM variable directive to
 *	apply simulator (SIM68K) serial functions.
 */

#include "types.h"

// #define SIM

#ifndef SERIAL_H
#define SERIAL_H

void serial_init();
void serial_puts(const char *, ubyte);
void serial_putc(char);
byte serial_isc();
char serial_getc();

#endif
