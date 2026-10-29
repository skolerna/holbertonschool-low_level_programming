#include "main.h"

/**
 * print_square - Prints a square
 * @size: The size of the square
 */
void print_square(int size)
{
	int i;
	int j;

	if (size <= 0)
	{
		_putchar('\n');
		return;
	}

	i = 0;

	while (i < size)
	{
		j = 0;

		while (j < size)
		{
			_putchar('#');
			j++;
		}

		_putchar('\n');
		i++;
	}
}
