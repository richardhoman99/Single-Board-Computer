/*
 * isr.h
 * Richard Homan
 * 02/11/2024
 * Interrupt service routine definition macros
 */

#define ISR(NAME)\
void __attribute__((interrupt_handler)) NAME(void)
