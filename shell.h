#ifndef SHELL_H
#define SHELL_H

#define PROMPT_STRING "\x1b[35mChris@yvonne:/# \x1b[0m"
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 100

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
void execute_command(char *command);

#endif /* SHELL_H */

