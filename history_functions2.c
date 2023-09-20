#include "shell.h"


/**
 * _history - Display the history entries.
 * @info: Pointer to the info structure.
 * Return: 0 (success).
 */
int _history(CommandInfo *info) /* display_history */
{
	print_list(info->history);
	return (0);
}
