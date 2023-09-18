#include "main.h"

/**
*stringlen - return the length of string
*
*@str: the string to count
*Return: string lenght
*/

int stringlen(const char *str)
{
int count, i;
count = 0;
i = 0;
while (str[i] != '\0')
{
count++;
i++;
}
return (count);
}
