#include "main.h"

/**
 * cap_string - Capitalizes all words of a string
 * @str: Pointer to the string
 *
 * Return: Pointer to str
 */
char *cap_string(char *str)
{
	int i;
	int debut;

	i = 0;
	debut = 1;

	while (str[i] != '\0')
	{
		if (debut && str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
			debut = 0;
		}
		else if (str[i] == ' ' || str[i] == '\t' ||
			 str[i] == '\n' || str[i] == ',' ||
			 str[i] == ';' || str[i] == '.' ||
			 str[i] == '!' || str[i] == '?' ||
			 str[i] == '"' || str[i] == '(' ||
			 str[i] == ')' || str[i] == '{' ||
			 str[i] == '}')
		{
			debut = 1;
		}
		else
		{
			debut = 0;
		}
		i++;
	}
	return (str);
}
