#include "shell.h"


/**
 * _myenv - Custom implementation of the "env" built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: Always returns 0.
 */
int _myenv(CommandInfo *info)
{
	print_list_str(info->env_variables);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: Pointer to a structure containing program information.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: A pointer to the value of the
 * environment variable or NULL if not found.
 */
char *_getenv(CommandInfo *info, const char *name)
{
	str_list *current_node = info->env_variables;
	char *p;

	/* Iterate through the list of environment variables.*/
	while (current_node)
	{
		/* Check if the current variable starts with the specified name.*/
		p = starts_with(current_node->str, name);

		/* If a match is found and the value is not empty, return it.*/
		if (p && *p)
		{
			return (p);
		}

		/* Move to the next environment variable in the list.*/
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Custom implementation of the "setenv" built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: 0 on success, 1 on error.
 */
int _mysetenv(CommandInfo *info)
{
	/* Check if the number of arguments is not equal to 3. */
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1); /*Return 1 to indicate an error. */
	}

	/* Call the _setenv function to set the environment variable. */
	if (_setenv(info, info->cmd_arguments[1], info->cmd_arguments[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenv - Custom implementation of the "unsetenv" built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: 0 on success, 1 on error.
 */
int _myunsetenv(CommandInfo *info)
{
	int i;

	/* Check if the number of arguments is 1 (too few). */
	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}

	/* Loop through the arguments starting from index 1. */
	for (i = 1; i <= info->argc; i++)
	{
		_unsetenv(info, info->cmd_arguments[i]);
	}

	return (0);
}
