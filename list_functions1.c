#include "shell.h"


/**
 * add_node - Add a new node to the beginning of a linked list.
 * @head: Pointer to the pointer of the head node of the list.
 * @str: String to be stored in the new node.
 * @num: Numeric value to be stored in the new node.
 *
 * Return: Pointer to the new node on success, NULL on failure.
 */
str_list *add_node(str_list **head, const char *str, int num)
{
	str_list *new_node;

	/* Check if the head pointer is NULL. */
	if (!head)
		return (NULL);

	/* Allocate memory for the new node. */
	new_node = malloc(sizeof(str_list));

	/* Check if memory allocation failed. */
	if (!new_node)
		return (NULL);

	/* Initialize the new node's fields. */
	_memset((void *)new_node, 0, sizeof(str_list));
	new_node->num = num;

	/* Duplicate and store the string in the new node. */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	/* Set the new node's next pointer to the current head of the list. */
	new_node->next = *head;

	/* Update the head pointer to point to the new node. */
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Add a new node to the end of a linked list.
 * @head: Pointer to the pointer of the head node of the list.
 * @str: String to be stored in the new node.
 * @num: Numeric value to be stored in the new node.
 *
 * Return: Pointer to the new node on success, NULL on failure.
 */
str_list *add_node_end(str_list **head, const char *str, int num)
{
	str_list *new_node, *current_node;
	/* Check if the head pointer is NULL. */
	if (!head)
		return (NULL);

	/* Initialize a temporary pointer to traverse the list. */
	current_node = *head;
	/* Allocate memory for the new node. */
	new_node = malloc(sizeof(str_list));
	if (!new_node)
		return (NULL);
	/* Initialize the new node's fields */
	_memset((void *)new_node, 0, sizeof(str_list));
	new_node->num = num;
	/* Duplicate and store the string in the new node. */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	/* Check if the list is not empty. */
	if (current_node)
	{
		 /* Traverse the list to find the last node. */
		while (current_node->next)
			current_node = current_node->next;
		/* Attach the new node to the last node's next pointer. */
		current_node->next = new_node;
	}
	else
		 /* If the list is empty, set the head pointer to the new node. */
		*head = new_node;
	return (new_node);
}


/**
 * print_list_str - Print the strings stored in a linked list.
 * @head: Pointer to the head node of the list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const str_list *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");

		head = head->next; /* Move to the next node.*/
		count++; /* Increment the node count.*/
	}
	return (count);
}

/**
 * delete_node_at_index - Delete a node at a specified index in a linked list.
 * @head: Pointer to the pointer of the head node of the list.
 * @index: The index of the node to be deleted.
 *
 * Return: 1 if the node was deleted successfully, 0 otherwise.
 */
int delete_node_at_index(str_list **head, unsigned int index)
{
	str_list *current_node, *prev_node;
	unsigned int i = 0;

	/* Check if the head pointer is NULL or if the list is empty. */
	if (!head || !*head)
		return (0);

	/* If the index is 0, delete the first node. */
	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *head;

	/* Loop through the list to find the node at the specified index.*/
	while (current_node)
	{
		if (i == index)
		{
			/* Update the previous node's next pointer to skip the current node. */
			prev_node->next = current_node->next;

			/* Free the memory for the current node's string and node. */
			free(current_node->str);
			free(current_node);
			return (1);
		}
		i++;
		prev_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * free_list - Free all nodes in a linked
 * list and set the head pointer to NULL.
 *
 * @head_ptr: Pointer to the pointer of the head node of the list.
 *
 * Return: void
 */
void free_list(str_list **head_ptr)
{
	str_list *current_node, *next_node, *head;

	/* Check if the head pointer is NULL or if the list is empty.*/
	if (!head_ptr || !*head_ptr)
	{
		return;
	}

	head = *head_ptr;
	current_node = head;

	/* Loop through the list and free each node and its string.*/
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*head_ptr = NULL;
}
