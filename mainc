#include "shell.h"

/**
 * main - Simple shell main function with command lines having arguments
 *
 * Return: Always 0
 */
int main(void)
{
    char *buffer;
    size_t bufsize = 32;
    ssize_t characters;
    char *token;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    while (1)
    {
        printf("chris:/# ");
        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* Remove newline character from input */
        if (buffer[characters - 1] == '\n')
            buffer[characters - 1] = '\0';

        token = strtok(buffer, " ");
        while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }
    }

    free(buffer);
    return (0);
}


