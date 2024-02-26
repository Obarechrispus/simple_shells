#include "shell.h"

/**
 * execute_program - Executes a program with arguments.
 */
void execute_program(char *program, char **arguments)
{
    printf("Before execve\n");
    if (execve(program, arguments, NULL) == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
}

int main(void)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    execute_program(argv[0], argv);

    return (0);
}

