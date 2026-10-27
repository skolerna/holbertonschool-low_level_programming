#include <stdio.h>

/**
 * main - Prints number from 0 to 9
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int n;

	n = 0;

	while (n <= 9)
	{
		printf("%d", n);
		n++;
	}

	printf("\n");

	return (0);
}
