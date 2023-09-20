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
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
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
	if (info->arg)
	{
	/* Split the argument into an array of strings */
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			/* If splitting fails, allocate memory for a single argument */
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		/* Count the number of arguments */
		for (i = 0; info->argv && info->argv[i]; i++)
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
	ffree(info->argv);
	info->argv = NULL;

	/* Reset the path */
	info->path = NULL;
	if (all)
	{
		/* Free argument string if cmd_buf is not present */
		if (!info->cmd_buf)
			free(info->arg);

		/* Free environment variables list */
		if (info->env)
			free_list(&(info->env));

		/* Free history list */
		if (info->history)
			free_list(&(info->history));

		/* Free alias list */
		if (info->alias)
			free_list(&(info->alias));

		/* Free the environment variables array */
		ffree(info->environ);
			info->environ = NULL;

		/* Free cmd_buf and close the read_fd */
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);

		/* Output a character, possibly for buffer flushing */
		_putchar(BUF_FLUSH_FLAG);
	}
}
