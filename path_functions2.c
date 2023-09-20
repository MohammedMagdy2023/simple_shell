#include "shell.h"


/**
 * find_builtin - Find and execute a built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: The return value of the executed
 * built-in command, or -1 if not found.
 */
int find_builtin(CommandInfo *info)
{
	int i, builtin_result = -1;

	/* Define an array of built-in commands their corresponding functions. */
	BuiltInCommandTable builtincmd[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _help},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	/* Loop through the array of built-in commands. */
	for (i = 0; builtincmd[i].cmd_name; i++)

		/* Check if the user's input matches a built-in command.*/
		if (_strcmp(info->cmd_arguments[0], builtincmd[i].cmd_name) == 0)
		{
		/* Increment the line count and execute the built-in command.*/
			info->err_count++;
			builtin_result = builtincmd[i].cmd_function(info);
			break;
		}
	return (builtin_result);
}
