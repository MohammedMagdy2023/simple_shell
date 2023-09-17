#include "main.h"

/**
*main - the main entry point for my custom shell
*
*Return: 0
*/

int main(void)
{
char cmd[150];

while (true)
{
/*displaying a promtwaiting for user to enter command*/
usr_promt();
/*reading the command that user inputs*/
read_cmd();
/*runs the command that read_cmd() reads*/
run_cmd(cmd);
}
return (0);
}
