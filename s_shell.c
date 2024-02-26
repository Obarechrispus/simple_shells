#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - Simple Shell
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *argv[10];
    int status;

    while (1)
    {
        printf("Chris@Osmerah:/# ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            perror("Error:");
            break;
        }
        if (read > 1)
        {
            line[read - 1] = '\0';  // remove the newline character

            char *token = strtok(line, " ");
            int i = 0;
            while (token != NULL)
            {
                argv[i++] = token;
                token = strtok(NULL, " ");
            }
            argv[i] = NULL;

            pid_t child_pid = fork();
            if (child_pid == -1)
            {
                perror("Error:");
                break;
            }
            if (child_pid == 0)
            {
                if (execve(argv[0], argv, NULL) == -1)
                {
                    perror("Error:");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                wait(&status);
            }
        }
    }

    free(line);
    return (0);
}

