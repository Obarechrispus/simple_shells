#include "shell.h"

/**
 * print_environment - Prints the environment using the global variable environ.
 */
void print_environment(void)
{
    int i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
}

