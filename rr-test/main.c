/*
 * main.c
 * Richard Homan
 * 03/22/2024
 * Entry point for ROM/RAM test
 */

int main(void)
{
	register int i, j, *k;

	for (i = 0; i < 4000000; i++) // more than 5 seconds at 10Mhz
		__asm__ __volatile__ ("nop");

	k = (int *)(0x30000);
	j = *k;
	j++;
	*k = j;

	// we should never get to this point, but if we do, loop
	while (1)
		__asm__ __volatile__ ("nop");
	return 0;
}

void __access_error(void)
{
	const int d = 0x55;
	int *i;
	i = (int *)0x10000;
	*i = d;

	return;
}
