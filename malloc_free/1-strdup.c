#include "main.h"
#include <stdlib.h>

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string, or NULL
 */
char *_strdup(char *str)
{
	unsigned int i;
	unsigned int j;
	char *copy;

	i = 0;

	if (str == NULL)
	{
		return (NULL);
	}

	while (str[i] != '\0')
	{
		i++;
	}

	copy = malloc(i + 1);

	if (copy == NULL)
	{
		return (NULL);
	}

	for (j = 0; j < i; j++)
	{
		copy[j] = str[j];
	}

	copy[i] = '\0';

	return (copy);
}
