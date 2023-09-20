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
	int i, built_in_ret = -1;

	/* Define an array of built-in commands their corresponding functions. */
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	/* Loop through the array of built-in commands. */
	for (i = 0; builtintbl[i].type; i++)

		/* Check if the user's input matches a built-in command.*/
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
		/* Increment the line count and execute the built-in command.*/
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
