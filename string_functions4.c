#include "shell.h"


/**
 * replace_string - Replaces an old string with
 * a new one and frees the old string.
 * @old_str: A pointer to the old string
 * (will be modified to point to the new string).
 * @new_str: The new string to replace the old one.
 *
 * Return: 1 on success, 0 on failure.
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
