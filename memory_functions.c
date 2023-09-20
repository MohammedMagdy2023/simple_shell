#include "shell.h"


/**
 * _memset - Fills memory with a
 * specified character for a given number of bytes.
 * @s: The character array to be filled.
 * @character: The character to fill the array with.
 * @num_bytes: The number of bytes to fill.
 *
 * Return: A pointer to the filled character array.
 */
char *_memset(char *s, char character, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
	{
		s[i] = character;
	}
	return (s);
}

/**
 * _free - Frees memory occupied by an array
 * of strings and the array itself.
 * @str_array: A pointer to an array of strings.
 */
void _free(char **str_array)
{
	char **a = str_array;

	if (!str_array)
	{
		return;
	}
	while (*str_array)
	{
		free(*str_array++);
	}
	free(a);
}


/**
 * _realloc - Reallocate memory for a given pointer.
 * @ptr: Pointer to the previously allocated memory.
 * @old_size: Size of the old memory block.
 * @new_size: Size of the new memory block.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		p[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (p);
}

/**
 * _freenreset - Frees memory and sets the pointer to NULL.
 * @ptr: A pointer to a pointer to the memory to be freed.
 *
 * Return: 1 if memory was freed, 0 if not.
 */
int _freenreset(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
