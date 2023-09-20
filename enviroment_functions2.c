#include "shell.h"



/**
 * populate_env_list - Populate the environment list from the 'environ' array.
 * @info: Pointer to a structure containing program information.
 *
 * Return: 0 on success, no error handling for simplicity.
 */
int populate_env_list(CommandInfo *info)
{
	str_list *env_list = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		/* Add each environment variable to the end of the list. */
		add_node_end(&env_list, environ[i], 0);
	}

	/* Set the 'env' member of the 'info' structure to the populated list.*/
	info->env_variables = env_list;
	return (0);
}

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
 * replace_vars - Replace environment variables in the command arguments.
 * @info: Pointer to the info structure.
 * Return: 0 (success).
 */
int replace_vars(CommandInfo *info)
{
	int i = 0;
	str_list *node;

	/* Loop through each argument in the cmd_arguments array */
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
		} /* Find an env var matches cmd_str (exclud '$') */
		node = node_starts_with(info->env_variables,
			&info->cmd_arguments[i][1], '=');
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
