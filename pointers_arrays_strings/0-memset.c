#include "main.h"

/**
 * _memset - Fills memory with a constant byte
 * @s: Memory area
 * @b: Byte to write
 * @n: Number of bytes
 *
 * Return: Pointer to s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}
