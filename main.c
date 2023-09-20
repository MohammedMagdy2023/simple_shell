#include "shell.h"

/**
 * main - Entry point.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, other values on failure.
 */
int main(int argc, char **argv)
{
	/* Initialize an array of 'info' structures */
	CommandInfo info[] = { INFO_INITIALIZER };
	/* File descriptor for standard error (stderr) */
	int stderr_fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (stderr_fd)
		: "r" (stderr_fd));

	if (argc == 2)
	{
		stderr_fd = open(argv[1], O_RDONLY);
		if (stderr_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH_FLAG);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = stderr_fd;
	}

	/* Populate environment list */
	populate_env_list(info);

	/* Read command history */
	read_history(info);

	/* Execute the 'hsh' function with the 'info' */
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
