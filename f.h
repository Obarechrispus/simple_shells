#ifndef F_H
#define F_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * run_shell - Main function to run the shell
 */
void run_shell(void);
extern char **environ;

#endif /* F_H */

