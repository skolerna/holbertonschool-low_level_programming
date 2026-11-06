#include "main.h"

/**
 * _atoi - Converts a string to an integer
 * @s: String to convert
 *
 * Return: Converted integer or 0
 */
int _atoi(char *s)
{
	int i;
	int sign;
	unsigned int result;

	i = 0;
	sign = 1;
	result = 0;
	while (s[i] != '\0')
{
	if (s[i] >= '0' && s[i] <= '9')
	{
		break;
	}
	if (s[i] == '-')
	{
		sign = sign * -1;
	}
	i++;
}
}
