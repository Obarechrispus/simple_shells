#include "shell.h"

/**
 * print_env_addresses - Prints the address of env and environ.
 * @envp: The third parameter of the main function
 */
void print_env_addresses(char **envp)
{
    printf("Address of env: %p\n", envp);
    printf("Address of environ: %p\n", environ);
}

