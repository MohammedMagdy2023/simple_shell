#include "shell.h"

/**
 * _puts - function to print a string
 * @str: The string to be printed
 *
 * This function prints each character of the input string 'str'.
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - function to write a character to standard output
 * @character: The character to write
 *
 * This function writes characters to the standard output and flushes
 * the buffer if the character is a flush character or the buffer is full.
 *
 * Return: 1 on success, 0 on failure.
 */
int _putchar(char character)
{
	static int i;
	static char buf[OUTPUT_BUF_SIZE];

	if (character == BUF_FLUSH_FLAG || i >= OUTPUT_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (character != BUF_FLUSH_FLAG)
		buf[i++] = character;
	return (1);
}
