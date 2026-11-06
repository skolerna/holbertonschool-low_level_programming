#include "main.h"

/**
 * _strspn - Gets the length of a prefix substring
 * @s: String to search
 * @accept: Characters to accept
 *
 * Return: Length of the prefix substring
 */
unsigned int _strspn(char *s, char *accept)
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
