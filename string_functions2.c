#include "shell.h"



/**
 * _strdup - Duplicates a string.
 * @str: The input string to be duplicated.
 *
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *duplicate_str;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		len++;
	}
	duplicate_str = malloc(sizeof(char) * (len + 1));
	if (!duplicate_str)
	{
		return (NULL);
	}
	for (len++; len--;)
	{
		duplicate_str[len] = *--str;
	}
	return (duplicate_str);
}

/**
 * starts_with - Checks if a string starts with another string.
 * @haystack: The string to check.
 * @needle: The prefix string to look for at the beginning.
 *
 * Return: A pointer to the start of the substring if found, or NULL otherwise.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}


/**
 * _strncpy - Copies up to 'n' characters from source to destination.
 * @dest: The destination string where the copy will be placed.
 * @src: The source string to be copied.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}


/**
 * _strncat - Concatenates (appends) up to 'n' characters
 * from source to destination.
 * @dest: The destination string where the concatenation will occur.
 * @src: The source string to be appended.
 * @n: The maximum number of characters to append.
 *
 * Return: A pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
	{
		dest[i] = '\0';
	}
	return (result);
}
