#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _strcmp - Compares two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: An integer less than, equal to, or greater than zero
 *         if str1 is found to be less than, equal to, or greater
 *         than str2, respectively.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
	{
		return (*str1 < *str2 ? -1 : 1);
	}
}


/**
 * _strcpy - Copies a string from source to destination.
 * @dest: The destination string where the copy will be placed.
 * @src: The source string to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strcat - Concatenates (appends) a source string to a destination string.
 * @dest: The destination string where the concatenation will occur.
 * @src: The source string to be appended.
 *
 * Return: A pointer to the destination string.
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;
	return (result);
}
