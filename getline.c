#include "shell.h"

/**
 * read_buf - Read data into a buffer.
 * @info: Pointer to a structure containing program information.
 * @buffer: Pointer to the buffer to read data into.
 * @bytes_read: Pointer to the variable that tracks the number of bytes read.
 *
 * Return: The number of bytes read or -1 on error.
 */
ssize_t read_buf(CommandInfo *info, char *buffer, size_t *bytes_read)
{
	ssize_t read_result = 0;

	/* If data has already been read, return 0 (no additional read needed). */
	if (*bytes_read)
	{
		return (0);
	}

	/* Read data from the specified file descriptor into the buffer. */
	read_result = read(info->read_file, buffer, INPUT_BUF_SIZE);

	/* Update the bytes_read variable with the number of bytes read. */
	if (read_result >= 0)
	{
		*bytes_read = read_result;
	}
	return (read_result);
}

/**
 * _getline - Read a line of input from a file or standard input.
 * @info: Pointer to a structure containing program information.
 * @ptr: Pointer to a pointer that will hold the line read from input.
 * @n: Pointer to the variable that will hold the length of the line.
 *
 * Return: The number of characters read,
 * -1 on failure, or 0 at the end of input.
 */
int _getline(CommandInfo *info, char **ptr, size_t *n)
{
	static char buf[INPUT_BUF_SIZE];
	static size_t buf_index, buf_len;
	size_t k;
	ssize_t read_result = 0, stored_length = 0;
	char *p = NULL, *new_p = NULL, *newline;

	p = *ptr;
	if (p && n) /* If lineptr and n are provided, store their values.*/
		stored_length = *n;
	/* If the buffer is fully consumed, reset the indices.*/
	if (buf_index == buf_len)
		buf_index = buf_len = 0;
	/* Read data into the buffer. */
	read_result = read_buf(info, buf, &buf_len);

	/* Check for read failure or end of input.*/
	if (read_result == -1 || (read_result == 0 && buf_len == 0))
		return (-1);
	/* Find a newline character in the buffer. */
	newline = _strchr(buf + buf_index, '\n');
	k = newline ? 1 + (unsigned int)(newline - buf) : buf_len;
	/* Reallocate memory for the line buffer. */
	new_p = _realloc(p, stored_length, stored_length ? stored_length + k : k + 1);

	if (!new_p) /* Handle memory allocation failure. */
		return (p ? free(p), -1 : -1);

	/* Copy the data from the buffer to the line buffer. */
	if (stored_length)
		_strncat(new_p, buf + buf_index, k - buf_index);
	else
		_strncpy(new_p, buf + buf_index, k - buf_index + 1);

	stored_length += k - buf_index;
	buf_index = k;
	p = new_p;
	if (n) /* If n is provided, update its value. */
		*n = stored_length;
	*ptr = p; /* Update the lineptr and return the number of characters read. */
	return (stored_length);
}

/**
 * sigintHandler - Signal handler function for SIGINT (Ctrl+C).
 * @sig_num: The signal number (unused in this function).
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH_FLAG);
}
