#ifndef MAIN_H
#define MAIN_H

/*The standerd libraries include*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Prototypes of functions*/
int stringlen(const char *str);
void print(const char *msg);
void usr_promt(void);
void read_cmd(char *cmd, size_t size);
void run_cmd(const char *cmd);

#endif /*main.h*/
