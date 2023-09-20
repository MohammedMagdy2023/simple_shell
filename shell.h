#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants for command chaining */
#define NORMAL_COMMAND	0
#define OR_COMMAND	1
#define AND_COMMAND	2
#define COMMAND_CHAIN	3

/* Constants for number conversion */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Flags for system function usage */
#define USE_SYS_GETLINE 0
#define USE_SYS_STRTOK 0

/* Constants for buffer sizes */
#define INPUT_BUF_SIZE 1024
#define OUTPUT_BUF_SIZE 1024
#define BUF_FLUSH_FLAG -1

/* Constants for history filename and entries sizes */
#define HISTORY_FNAME	".simple_shell_history"
#define MAX_HISTORY_ENTRIES	4096

/**
 * INFO_INITIALIZER - Macro for initializing a CommandInfo struct with default values.
 *
 * This macro creates an instance of the CommandInfo struct with all its members
 * set to appropriate initial values, typically NULL or 0. It is useful for creating
 * a default CommandInfo instance when setting up or resetting command information.
 */
#define INFO_INITIALIZER \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

extern char **environ;

/**
 * struct str_list - Represents a linked list
 * of string elements with numeric identifiers.
 *
 * @num: The numeric identifier associated with the string element.
 * @str: A pointer to the character array holding the string data.
 * @next: A pointer to the next element in the linked list.
 */
typedef struct str_list
{
	int num;
	char *str;
	struct str_list *next;
} str_list;

/**
 * struct CommandInfo - Represents information about a command in a shell.
 *
 * @cmd_str: The original command string entered by the user.
 * @cmd_arguments: An array of strings representing the individual command arguments.
 * @cmd_path: The path to the executable associated with the command.
 * @argc: The number of command arguments.
 * @err_count: Count of errors encountered while processing the command.
 * @err_number: The error number associated with the command (if an error occurred).
 * @linecount_flag: Flag to indicate whether line counting is enabled.
 * @fname: The name of the file (if the command is related to a script or file execution).
 * @env_variables: A linked list of environment variables associated with the command.
 * @history: A linked list representing the command history.
 * @aliases: A linked list of command aliases.
 * @environ: An array of strings representing the environment variables.
 * @env_changed: Flag to indicate whether the environment has been modified.
 * @status: The status of the command execution (e.g., exit status).
 * @cmd_buffer: An array of strings representing a buffer for commands (e.g., for pipelines).
 * @cmd_chaintype: Type of command chaining (e.g., sequential, background).
 * @read_file: Flag to indicate if the command reads from a file.
 * @history_count: Count of commands in the history.
 */
typedef struct CommandInfo {
    char *cmd_str;
    char **cmd_arguments;
    char *cmd_path;
    int argc;
    unsigned int err_count;
    int err_number;
    int linecount_flag;
    char *fname;
    str_list *env_variables;
    str_list *history;
    str_list *aliases;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buffer;
    int cmd_chaintype;
    int read_file;
    int history_count;
} CommandInfo;

/**
 * struct BuiltInCommand - Represents a built-in command in a shell.
 *
 * @cmd_name: The name of the built-in command.
 * @cmd_function: A function pointer to the corresponding function for the command.
 */
typedef struct BuiltInCommand
{
	char *cmd_name;
	int (*cmd_function)(CommandInfo *);
} BuiltInCommandTable;


/* hsh.c */
int hsh(CommandInfo *, char **);
int find_builtin(CommandInfo *);
void find_cmd(CommandInfo *);
void fork_cmd(CommandInfo *);

/* cmd_path.c */
int is_cmd(CommandInfo *, char *);
char *dup_chars(char *, int, int);
char *find_path(CommandInfo *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_functions4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory_functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree(void **);

/* more_functions.c */
int interactive(CommandInfo *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* more_functions2.c */
int _erratoi(char *);
void print_error(CommandInfo *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin_emulators.c */
int _myexit(CommandInfo *);
int _mycd(CommandInfo *);
int _myhelp(CommandInfo *);

/* builtin_emulators2.c */
int _myhistory(CommandInfo *);
int _myalias(CommandInfo *);

/* getline.c module */
ssize_t get_input(CommandInfo *);
int _getline(CommandInfo *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void clear_info(CommandInfo *);
void set_info(CommandInfo *, char **);
void free_info(CommandInfo *, int);

/* env.c module */
char *_getenv(CommandInfo *, const char *);
int _myenv(CommandInfo *);
int _mysetenv(CommandInfo *);
int _myunsetenv(CommandInfo *);
int populate_env_list(CommandInfo *);

/* env2.c module */
char **get_environ(CommandInfo *);
int _unsetenv(CommandInfo *, char *);
int _setenv(CommandInfo *, char *, char *);

/* file_io_functions.c */
char *get_history_file(CommandInfo *info);
int write_history(CommandInfo *info);
int read_history(CommandInfo *info);
int build_history_list(CommandInfo *info, char *buf, int linecount);
int renumber_history(CommandInfo *info);

/* liststr.c module */
str_list *add_node(str_list **, const char *, int);
str_list *add_node_end(str_list **, const char *, int);
size_t print_list_str(const str_list *);
int delete_node_at_index(str_list **, unsigned int);
void free_list(str_list **);

/* liststr2.c module */
size_t list_len(const str_list *);
char **str_listo_strings(str_list *);
size_t print_list(const str_list *);
str_list *node_starts_with(str_list *, char *, char);
ssize_t get_node_index(str_list *, str_list *);

/* chain.c */
int is_chain(CommandInfo *, char *, size_t *);
void check_chain(CommandInfo *, char *, size_t *, size_t, size_t);
int replace_alias(CommandInfo *);
int replace_vars(CommandInfo *);
int replace_string(char **, char *);

#endif
