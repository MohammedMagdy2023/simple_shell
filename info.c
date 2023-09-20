#include "shell.h"


/**
 * clear_info - Clear the fields of an CommandInfo struct
 * @info: Pointer to the CommandInfo struct to be cleared
 *
 * Description: This function sets the fields of an CommandInfo struct to NULL or 0,
 * effectively clearing its contents.
 * Return:void.
 */
void clear_info(CommandInfo *info)
{
	info->cmd_str = NULL;
	info->cmd_arguments = NULL;
	info->cmd_path = NULL;
	info->argc = 0;
}

/**
 * set_info - Sets information in the Info structure.
 * @info: Pointer to an Info structure.
 * @command_line_args: Array of strings representing command-line arguments.
 * Return:void.
 */
void set_info(CommandInfo *info, char **command_line_args)
{
	int i = 0;

	info->fname = command_line_args[0];
	if (info->cmd_str)
	{
	/* Split the argument into an array of strings */
		info->cmd_arguments = strtow(info->cmd_str, " \t");
		if (!info->cmd_arguments)
		{
			/* If splitting fails, allocate memory for a single argument */
			info->cmd_arguments = malloc(sizeof(char *) * 2);
			if (info->cmd_arguments)
			{
				info->cmd_arguments[0] = _strdup(info->cmd_str);
				info->cmd_arguments[1] = NULL;
			}
		}
		/* Count the number of arguments */
		for (i = 0; info->cmd_arguments && info->cmd_arguments[i]; i++)
			;
		info->argc = i;

		/* Replace aliases and variables in the arguments */
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees memory allocated for
 * the Info structure and associated data.
 * @info: Pointer to an Info structure.
 * @all: Flag indicating whether to free all associated data.
 * Return:void.
 */
void free_info(CommandInfo *info, int all)
{
	/* Free the array of arguments */
	ffree(info->cmd_arguments);
	info->cmd_arguments = NULL;

	/* Reset the path */
	info->cmd_path = NULL;
	if (all)
	{
		/* Free argument string if cmd_buf is not present */
		if (!info->cmd_buffer)
			free(info->cmd_str);

		/* Free environment variables list */
		if (info->env_variables)
			free_list(&(info->env_variables));

		/* Free history list */
		if (info->history)
			free_list(&(info->history));

		/* Free alias list */
		if (info->aliases)
			free_list(&(info->aliases));

		/* Free the environment variables array */
		ffree(info->environ);
			info->environ = NULL;

		/* Free cmd_buf and close the read_fd */
		bfree((void **)info->cmd_buffer);
		if (info->read_file > 2)
			close(info->read_file);

		/* Output a character, possibly for buffer flushing */
		_putchar(BUF_FLUSH_FLAG);
	}
}
