/*
 * ems-sim.h
 * Richard Homan
 * 02/11/2024
 * Declarations for serial control with SIM68k
 */

#include "types.h"

void serial_puts(const char *, byte);
void serial_putc(char);
byte serial_isc();
char serial_getc();
