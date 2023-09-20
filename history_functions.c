#include "shell.h"

/**
 * get_history_file - Generates a cmd_path to the history file.
 * @info: Pointer to an Info structure containing home directory information.
 * Return: A dynamically allocated string containing the history file cmd_path.
 */
char *get_history_file(CommandInfo *info)
{
	char *history_file_path, *home_directory;

	/* Get the user's home directory */
	home_directory = _getenv(info, "HOME=");
	if (!home_directory)
	{
		/* Home directory not found */
		return (NULL);
	}

	history_file_path = malloc(sizeof(char) *
		(_strlen(home_directory) + _strlen(HISTORY_FNAME) + 2));
	if (!history_file_path)
	{
		/* Memory allocation failed */
		return (NULL);
	}

	/* Initialize the history_file_path as an empty string */
	history_file_path[0] = 0;

	/* Copy the home directory cmd_path */
	_strcpy(history_file_path, home_directory);

	/* Append a slash to separate the directory */
	_strcat(history_file_path, "/");

	/* Append the history file name */
	_strcat(history_file_path, HISTORY_FNAME);

	return (history_file_path);
}

/**
 * save_history - Write history data to a file.
 * @info: Pointer to an Info structure.
 * Return: 1 on success, -1 on failure.
 */
int save_history(CommandInfo *info)
{
	ssize_t fileddescriptor;
	char *filename = get_history_file(info);
	str_list *node = NULL;

	if (!filename)
		return (-1);

	fileddescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileddescriptor == -1)
		return (-1);

	/* Iterate through the history and write each history to the file */
	for (node = info->history; node; node = node->next)
	{
		_fputs(node->str, fileddescriptor);
		_fputc('\n', fileddescriptor);
	}

	/* Write the buffer flush character to possibly flush the buffer */
	_fputc(BUF_FLUSH_FLAG, fileddescriptor);
	close(fileddescriptor);
	return (1);
}

/**
 * load_history - Read history data from a file.
 * @info: Pointer to an Info structure.
 * Return: Number of history entries read or 0 on failure.
 */
int load_history(CommandInfo *info)
{
	int i, last = 0, linecount = 0;
	ssize_t filedescriptor, bytes_read, file_size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)/* Check if the filename is not set (NULL) */
		return (0);
	filedescriptor = open(filename, O_RDONLY);
	free(filename); /* Free the memory allocated for the filename */
	if (filedescriptor == -1) /* Check if the file couldn't be opened */
		return (0); /* Error: Unable to open history file */
	if (!fstat(filedescriptor, &st)) /* Get file information, also size */
		file_size = st.st_size;
	if (file_size < 2)
		return (0); /* Error: History file is too small */
	/* Allocate memory to store the file content */
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0); /* Error: Memory allocation failed */
	bytes_read = read(filedescriptor, buf, file_size);
	buf[file_size] = 0; /* Null-terminate the buffer */
	if (bytes_read <= 0)
		return (free(buf), 0); /* Error: Unable to read history file */
	close(filedescriptor); /* Close the file descriptor */
	/* Iterate through the buffer and split it into history entries */
	for (i = 0; i < file_size; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_history_tolist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i) /* Check if the last entry was not processed */
		add_history_tolist(info, buf + last, linecount++);
	free(buf); /* Free the buffer as it's no longer needed */
	info->history_count = linecount; /* Update the history entry count */
	while (info->history_count-- >= MAX_HISTORY_ENTRIES)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info); /* Renumber the history entries */
	return (info->history_count);
}

/**
 * add_history_tolist - Builds a history entry and adds it to the list.
 * @info: Pointer to the history list.
 * @data: The data to add.
 * @line_number: The line number associated with the data.
 * Return: 0 on success.
 */
int add_history_tolist(CommandInfo *info, char *data, int line_number)
{
	str_list *new_node = NULL;

	if (info->history)
		new_node = info->history;
	add_node_end(&new_node, data, line_number);

	if (!info->history)
		info->history = new_node;
	return (0);
}

/**
 * renumber_history - Renumber history entries in the list.
 * @info: Pointer to the history entry list.
 * Return: The total number of history entries.
 */
int renumber_history(CommandInfo *info)
{
	str_list *node = info->history;
	int cpt = 0;

	while (node)
	{
		/* Set the entry's line number and increment count. */
		node->num = cpt++;
		node = node->next;
	}
	return (info->history_count = cpt);
}
