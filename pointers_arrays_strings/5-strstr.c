#include "main.h"
#include <stddef.h>

/**
 * _strstr - Finds the first occurrence of a substring
 * @haystack: String to search
 * @needle: Substring to find
 *
 * Return: Pointer to substring, or NULL if not found
 */
char *_strstr(char *haystack, char *needle)
{
	unsigned int i, j;

	i = 0;

	if (needle[0] == '\0')
	{
		return (haystack);
	}

	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' &&
		       haystack[i + j] == needle[j])
		{
			j++;
		}
		if (needle[j] == '\0')
		{
			return (haystack + i);
		}
		i++;
	}
	return (NULL);
}
