#include "main.h"

/**
 * _strcpy - Copies a string to another place
 * @dest: Destination place
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	return (dest);
}
