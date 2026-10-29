#include "main.h"

/**
 * print_numbers - Prints digits from 0 to 9
 */
void print_numbers(void)
{
	int n;

	n = 0;

	while (n < 10)
	{
		_putchar(n + '0');
		n++;
	}

	_putchar('\n');
}
