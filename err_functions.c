#include "shell.h"

/**
 * _erratoi - Convert a string to an integer
 * @str: The input string
 *
 * Description: This function converts a string to an integer while
 * handling overflow and non-digit characters.
 *
 * Return: The integer value if conversion is successful, or -1 on error.
 */
int _erratoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		/* Check if the current character is a digit (0-9) */
		if (str[i] >= '0' && str[i] <= '9')
		{
			/* Convert the character to an integer and update the result */
			result *= 10;
			result += (str[i] - '0');
			/* Check for integer overflow */
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			/* Return -1 if a non-digit character is encountered */
			return (-1);
		}
	}
	return (result);
}

/**
 * _dprintf - Print an integer to a file descriptor
 * @input: The integer to be printed
 * @filedescriptor: The file descriptor to write to
 *
 * Description: This function prints an integer to a specified file descriptor.
 * It returns the number of characters printed.
 *
 * Return: The number of characters printed.
 */
int _dprintf(int input, int filedescriptor)
{
	/* Function pointer for character output */
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (filedescriptor == STDERR_FILENO)
		/* Change output function for STDERR */
		__putchar = _eputchar;
	if (input < 0) /* Handle negative input */
	{
		_abs_ = -input;
		/* Print a minus sign for negative numbers */
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;/* Handle positive input */
	current = _abs_; /* Initialize current number */
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i); /* Print the current digit */
			count++;
		}
		current %= i; /* Update the current number */
	}
	__putchar('0' + current); /* Print the last digit */
	count++;

	return (count); /* Return the total character count */
}

/**
 * print_error - Print an error message to stderr
 * @info: Pointer to information about the error
 * @str: Error string to print
 *
 * Description: This function prints an error message to the standard error
 * output (stderr) with information about
 * the error and the error message itself.
 * Return: void
 */
void print_error(CommandInfo *info, char *str)
{
	/* Print the filename associated with the error	*/
	_eputs(info->fname);
	_eputs(": ");
	/* Print the line number where the error occurred */
	_dprintf(info->err_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->cmd_arguments[0]); /* Print the name of the program */
	_eputs(": ");
	_eputs(str); /* Print the error string */
}

/**
 * convert_number - Convert a number to a string
 * representation in the specified base
 * @num: The number to convert
 * @base: The base for conversion
 * (e.g., 10 for decimal, 16 for hexadecimal)
 * @flags: Flags to control conversion
 * (e.g., CONVERT_UNSIGNED, CONVERT_LOWERCASE)
 *
 * This function converts a number to a
 * string representation in the specified base
 * and with optional flags.
 *
 * Return: A pointer to the string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	/* Handle negative numbers if not flagged as CONVERT_UNSIGNED */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}

	/* Define the character array based on the lowercase flag */
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	/* Convert the number to a string representation */
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	/* Add the sign character if necessary */
	if (sign)
		*--ptr = sign;
	return (ptr);
}
