#include "main.h"

/**
*run_cmd - run the command scaned from user input
*
*@cmd: a command that user inputs
*Return: void
*/

void run_cmd(const char *cmd)
{
pid_t ch_pid = fork();
char cmd_path[100];
if (ch_pid == -1)
{
/*indecating forking error*/
perror("fork");
exit(EXIT_FAILURE);
}
else if (ch_pid == 0)
{
/*replace the child process with the cmd inserted*/
execlp(cmd, cmd, (char *)NULL);
perror("execlp");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
