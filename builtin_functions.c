#include "shell.h"


/**
 * _exit1 - Custom implementation of the "exit" built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: -2 to indicate the program should exit, 1 on error.
 */
int _exit1(CommandInfo *info)
{
	int exit_code;

	/* Check if there is an argument after "exit." */
	if (info->cmd_arguments[1])
	{
		/* Convert the argument to an integer.*/
		exit_code = _erratoi(info->cmd_arguments[1]);
		if (exit_code == -1)
		{
			/* If conversion fails, set an error status and print an error message.*/
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->cmd_arguments[1]);
			_eputchar('\n');
			return (1);
		}

		/* Store the exit code .*/
		info->err_number = _erratoi(info->cmd_arguments[1]);
		return (-2); /* Return -2 to indicate program exit with a err code. */
	}

	/* If no argument is provided, set the error number to -1 and exit. */
	info->err_number = -1;
	return (-2); /* Return -2 to indicate program exit without a specific code. */
}

/**
 * _cd - Custom implementation of the "cd" built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: 0 on success, 1 on error.
 */
int _cd(CommandInfo *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024); /* Get current directory.*/
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->cmd_arguments[1]) /* Check if no argument is provided.*/
	{ /* Try to change to the user's home directory or root */
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_result =
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (_strcmp(info->cmd_arguments[1], "-") == 0) /* Check if the cmd_str is hyphen.*/
	{
		if (!_getenv(info, "OLDPWD=")) /* Check if the "OLDPWD" env var is set.*/
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = /* Print and change to the "OLDPWD" directory.*/
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else /* Otherwise, treat the argument as a target directory.*/
		chdir_result = chdir(info->cmd_arguments[1]);
	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->cmd_arguments[1]), _eputchar('\n');
	}
	else /* Update the "OLDPWD" and "PWD" environment variables.*/
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - Custom implementation of the "help" built-in command.
 * @info: Pointer to a structure containing program information.
 *
 * Return: Always returns 0.
 */
int _help(CommandInfo *info)
{
	char **arg_array;

	/* Store the argument array in a local variable (not currently used).*/
	arg_array = info->cmd_arguments;

	/* Print a message function "help" is not yet implemented. */
	_puts("help call works. Function not yet implemented \n");

	/* Temporary unused variable workaround (not currently used).*/
	if (0)
		_puts(*arg_array);
	return (0);
}
