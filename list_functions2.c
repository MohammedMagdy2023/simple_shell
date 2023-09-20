#include "shell.h"

/**
 * list_len - Calculate the number of nodes in a linked list.
 * @head: Pointer to the head node of the list.
 *
 * Return: The number of nodes in the list.
 */
size_t list_len(const str_list *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * str_listo_strings - Convert a linked list of strings to an array of strings.
 * @head: Pointer to the head node of the linked list.
 *
 * Return: An array of strings (char **) containing the converted strings.
 *         NULL is returned if there is an error or the list is empty.
 */
char **str_listo_strings(str_list *head)
{
	str_list *node = head;
	size_t count = list_len(head), i;
	char **strs;
	char *str;

	/* Check if the list is empty or invalid. */
	if (!head || !count)
		return (NULL);

	/* Check if the list is empty or invalid. */
	strs = malloc(sizeof(char *) * (count + 1));

	if (!strs)
		return (NULL);

	/* Loop through the linked list and convert each string. */
	for (count = 0; node; node = node->next, count++)
	{
		/* Allocate memory for the string and copy its content. */
		str = malloc(_strlen(node->str) + 1);

		if (!str)
		{
			/* Free allocated memory and return NULL on error. */
			for (i = 0; i < count; i++)
				free(strs[i]);

			free(strs);
			return (NULL);
		}

		/* Copy the content of the string node to the new string. */
		str = _strcpy(str, node->str);

		/* Store the converted string in the array. */
		strs[count] = str;
	}
	strs[count] = NULL;
	return (strs);
}


/**
 * print_list - Print the content of a linked list.
 * @head: Pointer to the head node of the linked list.
 *
 * Return: The number of nodes printed.
 */
size_t print_list(const str_list *head)
{
	size_t cpt = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		cpt++;
	}
	return (cpt);
}


/**
 * node_starts_with - Find the first node in a linked list whose string
 *                    starts with a specified prefix and optional character.
 * @head: Pointer to the head node of the linked list.
 * @prefix: Prefix to search for at the beginning of each string.
 * @character: Optional character to match at the end of the prefix.
 *
 * Return: A pointer to the first matching node, or NULL if not found.
 */
str_list *node_starts_with(str_list *head, char *prefix, char character)
{
	char *p = NULL;

	while (head)
	{
		/* Check if the string in the current node starts with the prefix.*/
		p = starts_with(head->str, prefix);

		/* If the prefix is found and check the opt charcater.*/
		if (p && ((character == -1) || (*p == character)))
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a specific node in a linked list.
 * @head: Pointer to the head node of the linked list.
 * @node: Pointer to the node whose index is to be found.
 *
 * Return: The index of the node in the list, or -1 if not found.
 */
ssize_t get_node_index(str_list *head, str_list *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
		{
			return (index);
		}
		head = head->next;
		index++;
	}
	return (-1);
}
