/*
 * hasher.c
 * Richard Homan
 * 02/17/2024
 * Determine how many bins and where to place functions in a hashmap
 */

#include <stdio.h>

#define ARR_LEN(a) sizeof(a)/sizeof(a[0])

const char str0[] = "cr";
const char str1[] = "cm";
const char str2[] = "dr";
const char str3[] = "dm";
const char str4[] = "l";
const char str5[] = "r";
const char str6[] = "h";

const char *c[] =
{
	str0,
	str1,
	str2,
	str3,
	str4,
	str5,
	str6
};

const size_t l[] =
{
	ARR_LEN(str0),
	ARR_LEN(str1),
	ARR_LEN(str2),
	ARR_LEN(str3),
	ARR_LEN(str4),
	ARR_LEN(str5),
	ARR_LEN(str6)
};

char calc(const char *str, size_t len, int slots);

int main(void)
{
	int i;
	unsigned char s;

	for (i = 0; i < ARR_LEN(c); i++)
	{
		s = (unsigned char)calc(c[i], l[i], 16);
		printf("%u ", s);
	}

	printf("\n");
	return 0;
}

char calc(const char *str, size_t len, int slots)
{
	unsigned char sum;

	sum = 0;
	len--;
	for (; len > 0; len--)
	{
		sum += str[len-1];
	}

	sum = (unsigned char)(~sum) % slots;
	return sum;
}
