#include "shell.h"


/**
 * is_cmd - Check if the given path points to a regular file.
 * @info: A pointer to an CommandInfo struct (not used in this function).
 * @path: A pointer to a string representing the file path to check.
 *
 * Return: 1 if path is a regular file, 0 otherwise.
 */
int is_cmd(CommandInfo *info, char *path)
{
	struct stat st;

	(void)info;

	/* Check if the path is a null pointer or encounter an error */
	if (!path || stat(path, &st))
		return (0);

	/* Check if the st_mode of the stat contains the S_IFREG flag, */
	/* indicating that path is a regular file. */
	if (st.st_mode & S_IFREG)
	{
		return (1); /* Return 1 indicate path is a regular file. */
	}
	return (0);
}

/**
 * find_path - Find the full path of a command executable.
 * @info: A pointer to an CommandInfo struct (not used in this function).
 * @pathstr: A string containing a list of
 * directories in which to search for the command.
 * @cmd: The command name to find.
 *
 * Return: A pointer to a string containing the full
 * path of the command if found, or NULL if not found.
 */
char *find_path(CommandInfo *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			/* If cmd starts with "./" and is a valid command, return it. */
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			/* Extract a directory from pathstr. */
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd); /* If path is empty, concatenate cmd to it. */
			else
			{
				_strcat(path, "/"); /* Otherwise, add a '/' before cmd. */
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path); /* If the constructed path is a valid command, return it. */
			if (!pathstr[i])
				break; /* If we reach the end of pathstr, exit the loop. */
			curr_pos = i;
		}
		i++;
	}
	return (NULL); /* If the command is not found in any directory, return NULL.*/
}

/**
 * find_cmd - Find and execute a command in PATH.
 * @info: Pointer to a structure containing program information.
 *
 * Return: void
 */
void find_cmd(CommandInfo *info)
{
	char *path = NULL;
	int i, num_args;

	/* Set the default command path to the first argument. */
	info->cmd_path = info->cmd_arguments[0];
	/* Check if a line count flag is set and increment the line count. */
	if (info->linecount_flag == 1)
	{
		info->err_count++;
		info->linecount_flag = 0;
	}
	/* Count the number of non-delimiter arguments. */
	for (i = 0, num_args = 0; info->cmd_str[i]; i++)
		if (!is_delim(info->cmd_str[i], " \t\n"))
			num_args++;

	/* If there are no non-delimiter arguments, return early. */
	if (!num_args)
		return;
	/* Try to find the full path of the command. */
	path = find_path(info, _getenv(info, "PATH="), info->cmd_arguments[0]);

	/* If the command path is found, update the info structure and execute cmd */
	if (path)
	{
		info->cmd_path = path;
		fork_cmd(info);
	}
	else
	{
		/* Check if the command can be executed based on certain conditions. */
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->cmd_arguments[0][0] == '/') && is_cmd(info, info->cmd_arguments[0]))
			fork_cmd(info);
		else if (*(info->cmd_str) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Execute a command in a child process.
 * @info: Pointer to a structure containing program information.
 *
 * Return: void
 */
void fork_cmd(CommandInfo *info)
{
	pid_t child_pid;

	child_pid = fork(); /* Create a child process. */

	if (child_pid == -1)  /* Check for fork errors. */
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0) /* In the child process. */
	{
		/* Execute the command with execve. */
		if (execve(info->cmd_path, info->cmd_arguments, get_environ(info)) == -1)
		{
			free_info(info, 1);

			/* Handle permission denied error. */
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		/* Wait for the child to finish. */
		wait(&(info->status));

		/* Check if the child process exited normally. */
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			/* Check if the exit status is permission denied. */
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
