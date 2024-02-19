/*
 * command.h
 * Richard Homan
 * 02/17/2024
 * Command determination for Enemigo Monitor System
 */

#include "err.h"

#ifndef COMMAND_H
#define COMMAND_H

typedef int (*command_func)(const char **argv, int argc) ;

int ems_cr(const char **argv, int argc);
int ems_cm(const char **argv, int argc);
int ems_dr(const char **argv, int argc);
int ems_dm(const char **argv, int argc);
int ems_l (const char **argv, int argc);
int ems_r (const char **argv, int argc);
int ems_h (const char **argv, int argc);

int invalid_command(const char **argv, int argc);

int split_args(char *in, int len, char **argv, int *argc, int argm);
command_func gcommand(const char *commname);

#endif
