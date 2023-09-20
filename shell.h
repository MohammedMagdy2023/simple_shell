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

/* string_functions1.c */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

/* string_functions2.c */
char *_strdup(const char *str);
char *starts_with(const char *haystack, const char *needle);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);

/* string_functions3.c */
char *_strchr(char *str, char character);
char **strtow(char *str, char *delimiter);
char **strtow2(char *str, char delimiter);
int _atoi(char *str);

/* string_functions4.c */
int replace_string(char **old_str, char *new_str);

/* io_file_functions1.c */
void _eputs(char *str);
int _eputchar(char character);
int _fputc(char character, int filedescriptor);
int _fputs(char *str, int filedescriptor);

/* io_file_functions2.c */
void _puts(char *str);
int _putchar(char character);

/* chars_functions.c */
int is_delim(char character, char *delimiters);
int _isalpha(int character);
char *dup_chars(char *source, int start, int stop);

/* alias_functions1.c */
int unset_alias(CommandInfo *info, char *str);
int set_alias(CommandInfo *info, char *str);
int print_alias(str_list *node);
int _alias_handler(CommandInfo *info);

/* alias_functions2.c */
int replace_alias(CommandInfo *info);
int _mysetenv(CommandInfo *info);
int _myunsetenv(CommandInfo *info);

/* builtin_functions.c */
int _exit1(CommandInfo *info);
int _cd(CommandInfo *info);
int _help(CommandInfo *info);

/* chain_functions.c */
int is_chain(CommandInfo *info, char *buf, size_t *p);
void check_chain(CommandInfo *info, char *buf, size_t *pos, size_t idx, size_t len);

/* enviroment_functions1.c */
int _myenv(CommandInfo *info);
char *_getenv(CommandInfo *info, const char *name);
int _unsetenv(CommandInfo *info, char *name);
int _setenv(CommandInfo *info, char *var, char *value);


/* enviroment_functions2.c */
int populate_env_list(CommandInfo *info);
char **get_environ(CommandInfo *info);
int replace_vars(CommandInfo *info);

/* getline.c */
ssize_t read_buf(CommandInfo *info, char *buffer, size_t *bytes_read);
int _getline(CommandInfo *info, char **ptr, size_t *n);
void sigintHandler(__attribute__((unused))int sig_num);

/* history_functions.c */
char *get_history_file(CommandInfo *info);
int save_history(CommandInfo *info);
int load_history(CommandInfo *info);
int add_history_tolist(CommandInfo *info, char *data, int line_number);
int renumber_history(CommandInfo *info);

/* history_functions2.c */
int _history(CommandInfo *info);

/* hsh.c */
int hsh(CommandInfo *info, char **cmd_arguments);

/* info.c */
void clear_info(CommandInfo *info);
void set_info(CommandInfo *info, char **command_line_args);
void free_info(CommandInfo *info, int all);

/* input_functions.c */
ssize_t input_buf(CommandInfo *info, char **user_input, size_t *buffer_length);
ssize_t get_input(CommandInfo *info);
void remove_comments(char *input_string);

/* err_functions.c */
int _erratoi(char *str);
int _dprintf(int input, int filedescriptor);
void print_error(CommandInfo *info, char *str);
char *convert_number(long int num, int base, int flags);

/* list_functions1.c */
str_list *add_node(str_list **head, const char *str, int num);
str_list *add_node_end(str_list **head, const char *str, int num);
size_t print_list_str(const str_list *head);
int delete_node_at_index(str_list **head, unsigned int index);
void free_list(str_list **head_ptr);

/* list_functions2.c */
size_t list_len(const str_list *head);
char **str_listo_strings(str_list *head);
size_t print_list(const str_list *head);
str_list *node_starts_with(str_list *head, char *prefix, char character);
ssize_t get_node_index(str_list *head, str_list *node);

/* memory_functions.c */
char *_memset(char *s, char character, unsigned int num_bytes);
void _free(char **str_array);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _freenreset(void **ptr);

/* path_functions1.c */
int is_cmd(CommandInfo *info, char *cmd_path);
char *find_path(CommandInfo *info, char *pathstr, char *cmd);
void find_cmd(CommandInfo *info);
void fork_cmd(CommandInfo *info);

/* path_functions2.c */
int find_builtin(CommandInfo *info);

/* shell_mode_functions.c */
int interactive(CommandInfo *info);

#endif
