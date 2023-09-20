#include "shell.h"


/**
 * input_buf - Read input from the user and store it in a buffer.
 * @info: Pointer to the CommandInfo structure.
 * @user_input: Pointer to the buffer to store input.
 * @buffer_length: Pointer to the length of the buffer.
 *
 * Return: Number of characters read or an error code.
 */
ssize_t input_buf(CommandInfo *info, char **user_input, size_t *buffer_length)
{
	ssize_t characters_read  = 0;
	size_t buffer_size = 0;

	/* If the buffer is empty, fill it with user input */
	if (!*buffer_length) /* if nothing left in the buffer, fill it */
	{
		free(*user_input); /* Free the prev buffer, if exists */
		*user_input = NULL;

		signal(SIGINT, sigintHandler); /* Set signal handler for SIGINT */
#if USE_GETLINE
		/* Use the getline function to read input from stdin */
		characters_read  = getline(user_input, &buffer_size, stdin);
#else
		/* Use a custom _getline function to read input */
		characters_read  = _getline(info, user_input, &buffer_size);
#endif
		if (characters_read  > 0)
		{
			/* Remove trailing newline character if it exists */
			if ((*user_input)[characters_read  - 1] == '\n')
			{
				(*user_input)[characters_read  - 1] = '\0'; /* remove trailing newline */
				characters_read--;
			}
			/* Set a flag to indicate that a line of input was received */
			info->linecount_flag = 1;

			remove_comments(*user_input); /* Remove comments from the input */

			/* Build a history list with the input and increment the history count */
			build_history_list(info, *user_input, info->history_count++);
			/* if (_strchr(*user_input, ';')) is this a command chain? */
			{
				*buffer_length = characters_read; /* Update buff len ,store info  */
				info->cmd_buffer = user_input;
			}
		}
	}
	return (characters_read);
}

/**
 * get_input - Read and process user input.
 * @info: Pointer to the CommandInfo structure containing shell information.
 *
 * This function reads user input, handles command chains separated by ';',
 * and sets up the next command to be executed.
 *
 * Return: The length of the current command, or -1 on EOF (End-of-File).
 */
ssize_t get_input(CommandInfo *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->cmd_str), *p;

	_putchar(BUF_FLUSH_FLAG);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_chaintype = NORMAL_COMMAND;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * remove_comments - Remove comments from a string.
 * @input_string: The string from which comments should be removed.
 *
 * This function searches for the '#' character and removes it and everything
 * after it until the end of the string or a newline character is encountered.
 *
 * Return: Always 0;
 */
void remove_comments(char *input_string)
{
	int i;

	for (i = 0; input_string[i] != '\0'; i++)
		if (input_string[i] == '#' && (!i || input_string[i - 1] == ' '))
		{
			input_string[i] = '\0';
			break;
		}
}
