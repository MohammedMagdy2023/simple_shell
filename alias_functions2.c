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
