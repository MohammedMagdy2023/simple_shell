#include "main.h"

/**
*print - custom function that prints to the stdout
*@msg: the message to print
*
*Return: nothing
*/

void print(const char *msg)
{
write(STDERR_FILENO, msg, stringlen(msg));
}
