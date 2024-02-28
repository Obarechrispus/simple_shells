#include "shell.h"

void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("$ ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    }
    while (status);
}

