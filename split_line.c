#include "shell.h"

/**
 * split_line - Split a line into tokens
 * @line: The line to split
 *
 * Return: An array of tokens
 */
char **split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\n\r\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\n\r\a");
    }
    tokens[position] = NULL;
    return tokens;
}

