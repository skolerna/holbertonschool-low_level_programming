#include "main.h"

/**
 * leet - Encodes a string
 * @str: String to modify
 *
 * Return: Pointer to str
 */
char *leet(char *str)
{
	int i;
	int j;
	char min[] = "aeotl";
	char maj[] = "AEOTL";
	char num[] = "43071";

	i = 0;

	while (str[i] != '\0')
	{
		j = 0;
		while (j < 5)
		{
			if (str[i] == min[j] || str[i] == maj[j])
			{
				str[i] = num[j];
			}
			j++;
		}
		i++;
	}
	return (str);
}
