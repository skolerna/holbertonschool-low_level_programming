#include "main.h"

/**
 * more_numbers - Prints ten times 0 to 14
 */
void more_numbers(void)
{
	int n;
	int count;

	count = 0;

while (count < 10)
{
	n = 0;

	while (n < 15)
	{
		if (n >= 10)
		{
			_putchar((n / 10) + '0');
		}
		_putchar((n % 10) + '0');
		n++;
	}
	_putchar('\n');
	count++;
}
}
