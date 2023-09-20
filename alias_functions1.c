#include "shell.h"


/**
 * unset_alias - Unset (remove) an alias.
 * @info: Pointer to a structure containing program information.
 * @str: The alias string to unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(CommandInfo *info, char *str)
{
	char *equal_sign, saved_char;
	int result;

	/* Find the location of the equal sign ('=') in the alias string. */
	equal_sign = _strchr(str, '=');

	/* Check if the equal sign was not found. */
	if (!equal_sign)
		return (1);

	/* Save the character at the equal sign location. */
	saved_char = *equal_sign;

	/* Temporarily replace the equal sign with a null terminator. */
	*equal_sign = 0;

	/* Delete the alias by its index and calling the delete function. */
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	/* Restore the saved character to its original location. */
	*equal_sign = saved_char;
	return (result);
}

/**
 * set_alias - Set (add or update) an alias.
 * @info: Pointer to a structure containing program information.
 * @str: The alias string to set.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(CommandInfo *info, char *str)
{
	char *equal_sign;

	/* Find the location of the equal sign ('=') in the alias string.*/
	equal_sign = _strchr(str, '=');

	/* Check if the equal sign was not found.*/
	if (!equal_sign)
		return (1);

	/* Check if the character after the equal sign is a null terminator.*/
	if (!*++equal_sign)
		return (unset_alias(info, str));

	/* Call unset_alias to remove any existing alias with the same name.*/
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: Pointer to a node containing the alias string.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(str_list *node)
{
	char *equal_sign = NULL, *alias_start = NULL;

	/* Check if the node pointer is not NULL.*/
	if (node)
	{
		/* Find the location of the equal sign ('=') in the alias string. */
		equal_sign = _strchr(node->str, '=');

		/* Loop through the alias string up to the equal sign. */
		for (alias_start = node->str; alias_start <= equal_sign; alias_start++)
		{
			_putchar(*alias_start); /* Print each character of the alias name.*/
		}

		/* Print single quote + the alias value after the equal sign. */
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Handle alias-related functionality.
 * @info: Pointer to a structure containing program information.
 *
 * Return: 0 on success, 1 on error.
 */
int _myalias(CommandInfo *info)
{
	int i = 0;
	char *equal_sign = NULL;
	str_list *node = NULL;

	/*Check if no arguments were provided. */
	if (info->argc == 1)
	{
		/* Print all aliases in the linked list.*/
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	/* Loop through command-line arguments. */
	for (i = 1; info->argv[i]; i++)
	{
		/* Find the location of the equal sign ('=') in the argument. */
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
