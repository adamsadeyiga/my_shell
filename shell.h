#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define True 1
#define False 0

/* Global environment variable*/
extern char **environ;

#define PATH_DELIMITER ":"
#define MAX_PATH_LENGTH 256

void print(const char *message);
char *search_path(const char *command);
void print_environment(void);

#endif
