#include "main.h"

/**
 * print_square - Prints a square
 * @size: The size of the square to print
 */
void print_square(int size)
{
	int i;
	int j;

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
