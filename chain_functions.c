#include "shell.h"


/**
 * is_chain - Check if there is a command chaining operator in the buffer.
 * @info: Pointer to the info structure.
 * @buf: The buffer containing the command line.
 * @p: Pointer to the current position in the buffer.
 * Return: 1 if a chaining operator is found, 0 otherwise.
 */
int is_chain(CommandInfo *info, char *buf, size_t *p)
{
	size_t pos = *p;

	/* Check for the logical OR operator (||) */
	if (buf[pos] == '|' && buf[pos + 1] == '|')
	{
		buf[pos] = 0;
		pos++;
		info->cmd_chaintype = OR_COMMAND;
	}
	/* Check for the logical AND operator (&&) */
	else if (buf[pos] == '&' && buf[pos + 1] == '&')
	{
		buf[pos] = 0;
		pos++;
		info->cmd_chaintype = AND_COMMAND;
	}
	/* Check for the semicolon operator (;) */
	else if (buf[pos] == ';')
	{
		buf[pos] = 0; /* Replace semicolon with null */
		info->cmd_chaintype = COMMAND_CHAIN;
	}
	else
		return (0); /* No chaining operator found */
	*p = pos; /* Update the current position */
	return (1);
}

/**
 * check_chain - Handle command chaining based on the current status.
 * @info: Pointer to the info structure.
 * @buf: The buffer containing the command line.
 * @pos: Pointer to the current position in the buffer.
 * @idx: The current position in the buffer.
 * @len: The length of the buffer.
 */
void check_chain(CommandInfo *info, char *buf, size_t *pos, size_t idx, size_t len)
{
	size_t temp_pos = *pos;

	/* Check if the command buffer type is AND_COMMAND */
	if (info->cmd_chaintype == AND_COMMAND)
	{
		/* If the prev command had a non-zero status, terminate the current one */
		if (info->status)
		{
			buf[idx] = 0; /* terminate the current command */
			temp_pos = len; /* Set the current position to the end of the buffer */
		}
	}
	/* Check if the command buffer type is OR_COMMAND */
	if (info->cmd_chaintype == OR_COMMAND)
	{
		/* If the prev command had a non-zero status, terminate the current one */
		if (!info->status)
		{
			buf[idx] = 0;
			temp_pos = len;
		}
	}

	*pos = temp_pos; /* Update the current position in the buffer */
}
