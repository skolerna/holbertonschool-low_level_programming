
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Adds positive numbers passed as arguments
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	int i = 1;
	int j;
	int result = 0;

	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (1);
			}
			j++;
		}

		result = result + atoi(argv[i]);
		i++;
	}
	printf("%d\n", result);
	return (0);
}
