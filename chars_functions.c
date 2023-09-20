#include "shell.h"


/**
 * is_delim - Check if a character is a delimiter
 * @character: The character to check
 * @delimiters: A string containing delimiters to check against
 *
 * This function checks if a character 'c' is a delimiter by comparing it to
 * a string of delimiters 'delimiters'.
 *
 * Return: 1 if 'c' is a delimiter, 0 otherwise.
 */
int is_delim(char character, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == character)
			return (1);
	return (0);
}

/**
 * _isalpha - Check if a character is an alphabet letter
 * @character: The character to check
 *
 * This function checks if a character 'c' is an alphabet letter (A-Z or a-z).
 *
 * Return: 1 if 'c' is an alphabet letter, 0 otherwise.
 */
int _isalpha(int character)
{
	if ((character >= 'a' && character <= 'z') ||
		(character >= 'A' && character <= 'Z'))

		return (1);
	else
		return (0);
}

/**
 * dup_chars - Duplicate characters from a string within a specified range
 * @source: The source string
 * @start: The start index of the range (inclusive)
 * @stop: The stop index of the range (exclusive)
 *
 * This function duplicates characters
 * from the source string within the specified
 * range and returns the
 * duplicated characters as a new string.
 *
 * Return: The duplicated characters as a new string.
 */
char *dup_chars(char *source, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (source[i] != ':')
			buf[k++] = source[i];
	buf[k] = 0;
	return (buf);
}
