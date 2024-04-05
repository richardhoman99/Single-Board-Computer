/*
 * exec.h
 * Richard Homan
 * 02/18/2024
 * Loaded executable shared entrypoint for Enemigo Monitor System
 */

#ifndef EXEC_H
#define EXEC_H

#include "types.h"

extern byte has_exec;
extern int (*exec_entry_ptr)(void);

#endif
