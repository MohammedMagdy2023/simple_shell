#include "shell.h"

/**
 * _eputs - function that prints a string to standard output
 * @str: The string to be printed
 *
 * This function prints each character
 * of the input string 'str' to the standard output.
 *
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - function to write characters to the standard error output
 * @character: The character to write
 *
 * This function writes characters
 * to the standard error output and flushes the buffer
 * if the character is a flush character or the buffer is full.
 *
 * Return: 1 on success, 0 on failure.
 */
int _eputchar(char character)
{
	static int i;
	static char buf[OUTPUT_BUF_SIZE];

	if (character == BUF_FLUSH_FLAG || i >= OUTPUT_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (character != BUF_FLUSH_FLAG)
		buf[i++] = character;
	return (1);
}

/**
 * _putfd - function to write characters to a specified file descriptor
 * @character: The character to write
 * @filedescriptor: The file descriptor where
 * the character should be written
 *
 * This function writes characters to
 * the specified file descriptor and flushes
 * the buffer if the character is a flush
 * character or the buffer is full.
 *
 * Return: 1 on success, 0 on failure.
 */
int _putfd(char character, int filedescriptor)
{
	static int i;
	static char buf[OUTPUT_BUF_SIZE];

	if (character == BUF_FLUSH_FLAG || i >= OUTPUT_BUF_SIZE)
	{
		write(filedescriptor, buf, i);
		i = 0;
	}
	if (character != BUF_FLUSH_FLAG)
		buf[i++] = character;
	return (1);
}

/**
 * _putsfd - function to write characters to a specified file descriptor
 * @str: he string to write
 * @filedescriptor: he file descriptor where
 * the string should be written
 *
 * This function writes string to
 * the specified file descriptor the number of characters written.
 *
 * Return: 1 on success, 0 on failure.
 */
int _putsfd(char *str, int filedescriptor)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		i += _putfd(*str++, filedescriptor);
	}
	return (i);
}
