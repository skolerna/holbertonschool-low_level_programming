#include "main.h"

/**
 * print_line - Prints a line
 * @n: The length of the line to print
 */
void print_line(int n)
{
	int i;

	i = 0;

	while (i < n)
	{
		_putchar('_');
		i++;
	}
	_putchar('\n');
}
