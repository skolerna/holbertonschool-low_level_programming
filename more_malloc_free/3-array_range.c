#include "main.h"
#include <stdlib.h>

/**
 * array_range - Creates an array of integers
 * @min: Minimum value
 * @max: Maximum value
 *
 * Return: Pointer to the array, or NULL
 */
int *array_range(int min, int max)
{
	int *array;
	int i;

	if (min > max)
	{
		return (NULL);
	}

	array = malloc((max - min + 1) * sizeof(int));
	if (array == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < max - min + 1; i++)
	{
		array[i] = min + i;
	}

	return (array);
}
