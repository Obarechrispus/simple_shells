#include "shell.h"

/**
 * execute - Execute a command
 * @command: The command to execute
 * @args: The arguments for the command
 *
 * Return: Always 0
 */
int execute(char *command, char **args)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error");
        return (EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        if (execve(command, args, NULL) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }

    return (0);
}

