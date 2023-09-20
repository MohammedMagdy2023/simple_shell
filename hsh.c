#include "shell.h"

/**
 * hsh - Custom shell function that reads and executes user commands.
 * @info: Pointer to a structure containing program information.
 * @argv: Command-line arguments.
 *
 * Return: The return value of the executed command.
 */
int hsh(info_t *info, char **argv)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	/* Main loop for reading and executing commands. */
	while (read_result != -1 && builtin_result != -2)
	{
		clear_info(info); /* Clear previous command info. */

		 /* Display the shell prompt if in interactive mode. */
		if (interactive(info))
			_puts("$ ");

		/* Flush the output buffer. */
		_eputchar(BUF_FLUSH_FLAG);

		/* Read user input.*/
		read_result = get_input(info);
		if (read_result != -1)
		{
			set_info(info, argv); /* Set up command information. */
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);  /* Free dynamically allocated memory.*/
	}
	write_history(info); /* Write command history.*/
	free_info(info, 1); /* Free remaining allocated memory. */

	if (!interactive(info) && info->status) /* Exit with appropriate err code */
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1) /* If error, exit with that error code.*/
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}
