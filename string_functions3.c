#include "shell.h"


/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @str: The string to search within.
 * @character: The character to find in the string.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(char *str, char character)
{
	do {
		if (*str == character)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}


/**
 * strtow - Splits a string into an array of words based on a delimiter.
 * @str: The input string to be split.
 * @delimiter: The characters used to split the string.
 *
 * Return: An array of strings containing the words from the input string.
 *         Returns NULL if str is NULL, empty, or on memory allocation failure.
 */
char **strtow(char *str, char *delimiter)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delimiter) &&
(is_delim(str[i + 1], delimiter) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delimiter))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delimiter) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * strtow2 - Splits a string into an array of
 * words based on a delimiter character.
 * @str: The input string to be split.
 * @delimiter: The character used to split the string.
 *
 * Return: An array of strings containing the words from the input string.
 *         Returns NULL if str is NULL, empty, or on memory allocation failure.
 */
char **strtow2(char *str, char delimiter)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


/**
 * _atoi - Converts a string to an integer.
 * @str: The string to convert to an integer.
 *
 * Return: The integer value of the string.
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
