#include "shell.h"

/**
 * main - Entry point.
 * @argc: The number of command-line arguments.
 * @cmd_arguments: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, other values on failure.
 */
int main(int argc, char **cmd_arguments)
{
	/* Initialize an array of 'info' structures */
	CommandInfo info[] = { INFO_INITIALIZER };
	/* File descriptor for standard error (stderr) */
	int stderr_file = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (stderr_file)
		: "r" (stderr_file));

	if (argc == 2)
	{
		stderr_file = open(cmd_arguments[1], O_RDONLY);
		if (stderr_file == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(cmd_arguments[0]);
				_eputs(": 0: Can't open ");
				_eputs(cmd_arguments[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH_FLAG);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file = stderr_file;
	}

	/* Populate environment list */
	populate_env_list(info);

	/* Read command history */
	read_history(info);

	/* Execute the 'hsh' function with the 'info' */
	hsh(info, cmd_arguments);
	return (EXIT_SUCCESS);
}
