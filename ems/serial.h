/*
 * serial.h
 * Richard Homan
 * 02/11/2024
 * Declarations for serial control. Uncomment the SIM variable directive to
 *	apply simulator (SIM68K) serial functions.
 */

#include "types.h"

// #define SIM

void serial_puts(const char *, ubyte);
void serial_putc(char);
byte serial_isc();
char serial_getc();
