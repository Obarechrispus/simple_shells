#include "shell.h"

void shell_loop(void)
{
    char *line;
    char **args;
    int status;

        do
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);
}
