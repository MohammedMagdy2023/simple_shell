#include "main.h"

/**
*read_cmd - reads the user input command to execute
*
*@cmd:command from user
*@size:size of the command
*Return: void
*/

void read_cmd(char *cmd, size_t size)
{
if (fgets(cmd, size, stdin) == NULL)
{
if (feof(stdin))
{
print("\n");
exit(EXIT_SUCCESS);
}
else
{
print("error input.\n");
exit(EXIT_FAILURE);
}
}
cmd[strcspn(cmd, "\n")] = '\0';
}
