#include "shell.h"

/**
 * read_line - Read a line from standard input
 *
 * Return: The line read
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    characters = getline(&line, &bufsize, stdin);
    if (characters == -1)
    {
        if (feof(stdin))
        {
            free(line);
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

