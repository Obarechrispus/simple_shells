#ifndef F_H
#define F_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
void execute_command(char *command);

#endif /* F_H */

