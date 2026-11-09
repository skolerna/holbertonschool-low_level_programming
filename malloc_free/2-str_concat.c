#include "main.h"
#include <stdlib.h>

/**
 * str_concat - Concatenates two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: Pointer to the new string, or NULL on fail
 */
char *str_concat(char *s1, char *s2)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	char *result;

	i = 0;
	j = 0;

	if (s1 != NULL)
	{
		while (s1[i] != '\0')
			i++;
	}

	if (s2 != NULL)
	{
		while (s2[j] != '\0')
			j++;
	}

	result = malloc(i + j + 1);
	if (result == NULL)
		return (NULL);

	for (k = 0; k < i; k++)
		result[k] = s1[k];

	for (k = 0; k < j; k++)
		result[i + k] = s2[k];

	result[i + j] = '\0';

	return (result);
}
