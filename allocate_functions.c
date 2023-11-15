#include "shell.h"

/**
 * _realloc - Function that reallocates a memory block using malloc and free
 * The pointer ptr has been free and the content is copy in a new pointer
 *
 * @ptr: The pointer we want to free and copy the content
 * @old_size: The size of the old pointer
 * @new_size: The size of the new pointer
 *
 * Return: new_ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;
	unsigned int loop;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);

	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}

	for (loop = 0; loop < old_size && loop < new_size; loop++)
		*((char *)new_ptr + loop) = *((char *)ptr + loop);

	*((char *)new_ptr + loop) = '\0';
	free(ptr);

	return (new_ptr);
}

/**
 * _calloc - Function that allocates memory for an array
 *
 * @nmemb: Number of element for the array
 * @size: The size of type we want for the array
 *
 * Return: ptr
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;
	unsigned int loop;

	if (nmemb == 0 || size == 0)
		return (NULL);

	ptr = (char *)malloc(nmemb * size);

	if (ptr == NULL)
		return (NULL);

	for (loop = 0; loop < nmemb * size; loop++)
		*(ptr + loop) = 0;

	return (ptr);
}
