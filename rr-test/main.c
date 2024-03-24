/*
 * main.c
 * Richard Homan
 * 03/22/2024
 * Entry point for ROM/RAM test
 */

int main(void)
{
	register int i;
	int j, k;

	for (i = 0; i < 50000000; i++) // more than 5 seconds at 10Mhz
		__asm__ __volatile__ ("nop");

	j = *(int *)(0x800000);
	k = j + 1;

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}
