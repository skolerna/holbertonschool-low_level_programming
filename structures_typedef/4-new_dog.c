#include "dog.h"
#include <stdlib.h>

/**
 * new_dog - Creates a new dog
 * @name: Name of the dog
 * @age: Age of the dog
 * @owner: Owner of the dog
 *
 * Return: Pointer to the new dog, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	int i, j;

	if (name == NULL || owner == NULL)
		return (NULL);

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	i = 0;
	while (name[i] != '\0')
		i++;

	dog->name = malloc(i + 1);
	if (dog->name == NULL)
	{
		free(dog);
		return (NULL);
	}
	for (j = 0; j <= i; j++)
		dog->name[j] = name[j];

	i = 0;
	while (owner[i] != '\0')
		i++;

	dog->owner = malloc(i + 1);
	if (dog->owner == NULL)
	{
		free(dog->name);
		free(dog);
		return (NULL);
	}
	for (j = 0; j <= i; j++)
		dog->owner[j] = owner[j];

	dog->age = age;
	return (dog);
}
