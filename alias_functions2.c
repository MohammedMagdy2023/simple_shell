#include "shell.h"


/**
 * replace_alias - Replace a command with its alias value.
 * @info: Pointer to a structure containing program information.
 *
 * Return: 1 on success, 0 on error.
 */
int replace_alias(CommandInfo *info)
{
	int i;
	str_list *node;
	char *equal_sign;

	for (i = 0; i < 10; i++)
	{
		/* Find an alias node that matches the command (info->cmd_arguments[0]). */
		node = node_starts_with(info->aliases, info->cmd_arguments[0], '=');

		/* If no matching alias is found, exit the loop. */
		if (!node)
			return (0);

		/* Free the current command (info->cmd_arguments[0]). */
		free(info->cmd_arguments[0]);

		/* Find the location of the equal sign ('=') in the alias string. */
		equal_sign = _strchr(node->str, '=');

		/* If no equal sign is found, exit the loop. */
		if (!equal_sign)
			return (0);

		/* Duplicate the alias value (string after the equal sign). */
		equal_sign = _strdup(equal_sign + 1);

		/* If strdup fails, exit the loop. */
		if (!equal_sign)
			return (0);

		/* Update the command with the alias value. */
		info->cmd_arguments[0] = equal_sign;
	}
	return (1);
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
