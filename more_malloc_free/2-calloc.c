#include "main.h"
#include <stdlib.h>
#include <stdint.h>

/**
 * _calloc - Allocates memory and initializes it to zero
 * @nmemb: Number of elements
 * @size: Size of each element in bytes
 *
 * Return: Pointer to allocated memory, or NULL
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ptr;
	char *p;
	size_t i;
	size_t total;

	if (nmemb == 0 || size == 0)
	{
		return (NULL);
	}

	if ((size_t)nmemb > SIZE_MAX / size)
	{
		return (NULL);
	}

	total = (size_t)nmemb * size;
	ptr = malloc(total);
	if (ptr == NULL)
	{
		return (NULL);
	}

	p = ptr;

	for (i = 0; i < total; i++)
	{
		p[i] = 0;
	}

	return (ptr);
}
