#include "shell.h"

/**
 * main - Execute ls -l /tmp in 5 different child processes.
 *
 * Return: Always 0.
 */
int main(void)
{
    int i;
    pid_t child_pid;
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

    for (i = 0; i < 5; i++)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error:");
            return (1);
        }
        if (child_pid == 0)
        {
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("Error:");
                return (1);
            }
        }
        else
        {
            wait(NULL);
        }
    }
    return (0);
}

