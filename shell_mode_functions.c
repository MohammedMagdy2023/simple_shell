#include "shell.h"


/**
 * interactive - Check if the program is running in an interactive mode.
 * @info: Pointer to the CommandInfo structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(CommandInfo *info)
{

	/* Check if the std input (file  0) is associated with a terminal, */
	/* and if the read file in info is less than or equal to 2. */
	/* File  0, 1, and 2 are typically associated with stdio and stderr. */

	return (isatty(STDIN_FILENO) && info->read_file <= 2);
}
