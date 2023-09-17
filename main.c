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
usr_promt();
read_cmd();
run_cmd(cmd);
}
return (0);
}
