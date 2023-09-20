#include "shell.h"


/**
 * get_environ - Get the environment variables as an array of strings.
 * @info: Pointer to a structure containing program information.
 *
 * Return: An array of strings containing environment variables.
 */
char **get_environ(CommandInfo *info)
{
	/* Check if the 'environ' array is not set or if the env has changed.*/
	if (!info->environ || info->env_changed)
	{
		/* Convert the linked list of environment variables to an array of strings.*/
		info->environ = str_listo_strings(info->env_variables);

		/* Reset the 'env_changed' to indicate that the environment is updated.*/
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Unset (remove) an environment variable.
 * @info: Pointer to a structure containing program information.
 * @name: The name of the environment variable to unset.
 *
 * Return: 1 if the environment was changed, 0 if not.
 */
int _unsetenv(CommandInfo *info, char *name)
{
	str_list *current_node = info->env_variables;
	size_t i = 0;
	char *p;

	/* Check if the environment list is empty or if the variable name is NULL. */
	if (!current_node || !name)
	{
		return (0);
	}

	/* Loop through the environment list. */
	while (current_node)
	{
		/* Check if the variable starts with the name and is followed by '='. */
		p = starts_with(current_node->str, name);
		if (p && *p == '=')
		{
			/* Delete the node at the current index and update the 'env_changed'. */
			info->env_changed = delete_node_at_index(&(info->env_variables), i);

			/* Reset the index and start over from the beginning of the list. */
			i = 0;
			current_node = info->env_variables;
			continue;
		}
		current_node = current_node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Set (or update) an environment variable.
 * @info: Pointer to a structure containing program information.
 * @var: The name of the environment variable to set.
 * @value: The value to assign to the environment variable.
 *
 * Return: 0 on success, 1 on error.
 */
int _setenv(CommandInfo *info, char *var, char *value)
{
	char *buf = NULL;
	str_list *current_node;
	char *p;

	/* Check if either the variable name or value is NULL. */
	if (!var || !value)
		return (0);
	/* Allocate memory for the new environment variable string. */
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	/* Create the new environment variable string in the format "name=value". */
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	/* Start at the beginning of the environment list. */
	current_node = info->env_variables;
	/* Loop through the environment list. */
	while (current_node)
	{
		/* Check if the variable starts with name and is followed by '='. */
		p = starts_with(current_node->str, var);
		if (p && *p == '=')
		{
			/* Free the old environment variable string. */
			free(current_node->str);
			/* Update the node's string with the new environment variable. */
			current_node->str = buf;
			/* Set the 'env_changed' flag to indicate a change. */
			info->env_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	/* If the variable does not exist, add it to the end of the env list. */
	add_node_end(&(info->env_variables), buf, 0);
	/* Free the allocated memory for the new environment variable string. */
	free(buf);
	info->env_changed = 1; /* Set the 'env_changed' flag to indicate a change. */
	return (0);
}

/**
 * replace_vars - Replace environment variables in the command arguments.
 * @info: Pointer to the info structure.
 * Return: 0 (success).
 */
int replace_vars(CommandInfo *info)
{
	int i = 0;
	str_list *node;

	/* Loop through each argument in the argv array */
	for (i = 0; info->cmd_arguments[i]; i++)
	{
		/* Check if the argument starts with a '$' character and is not empty */
		if (info->cmd_arguments[i][0] != '$' || !info->cmd_arguments[i][1])
			continue; /* Skip if doesn't start with '$' or is empty */

		/* Check if the argument is "$?" */
		if (!_strcmp(info->cmd_arguments[i], "$?"))
		{
			/* Replace with the exit status converted to a string */
			replace_string(&(info->cmd_arguments[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue; /* Move to the next argument */
		}
		/* Check if the argument is "$$" */
		if (!_strcmp(info->cmd_arguments[i], "$$"))
		{
			/* Replace with the current process ID converted to a string */
			replace_string(&(info->cmd_arguments[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		/* Find an env variable that matches the arg (exclud '$') */
		node = node_starts_with(info->env_variables, &info->cmd_arguments[i][1], '=');
		if (node)
		{
			/* Replace with the value of the environment variable */
			replace_string(&(info->cmd_arguments[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		/* If no match was found, replace the argument with an empty string */
		replace_string(&info->cmd_arguments[i], _strdup(""));

	}
	return (0);
}
