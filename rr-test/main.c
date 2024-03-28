/*
 * main.c
 * Richard Homan
 * 03/22/2024
 * Entry point for ROM/RAM test
 */

int main(void)
{
	register int i;
	int j;
	int *k;

	for (i = 0; i < 50000000; i++) // more than 5 seconds at 10Mhz
		__asm__ __volatile__ ("nop");

	k = (int *)(0x800000);
	j = *k;
	j++;
	*k = j;

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}
