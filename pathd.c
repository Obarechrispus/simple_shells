#include "shell.h"

/**
 * print_path_directories - Prints each directory contained in the PATH environment variable.
 */
void print_path_directories(void)
{
    char *path = _getenv("PATH");
    if (path != NULL)
    {
        char *token = strtok(path, ":");
        while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, ":");
        }
    }
}

