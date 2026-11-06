#include "main.h"

/**
 * _strpbrk - Finds the first occurence of any character from a string
 * @s: String to search
 * @accept: Characters to search for
 * Return: Pointer to the first occurence of any character from accept, or
 * NULL if not found
 */
char *_strpbrk(char *s, char *accept)
{
	unsigned int i, j;
	int found;

	i = 0;

	while (s[i] != '\0')
	{
		found = 0;
		j = 0;

		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
			{
				found = 1;
			}
			j++;
		}

		if (found == 0)
		{
			return (i);
		}
		i++;
	}
	return (i);
}
