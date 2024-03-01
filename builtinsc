#include "shell.h"

/**
 * is_builtin - Check if a command is a built-in
 * @command: The command to check
 *
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int is_builtin(char *command)
{
    if (_strcmp(command, "exit") == 0 ||
        _strcmp(command, "env") == 0)
        return (1);
    return (0);
}

/**
 * execute_builtin - Execute a built-in command
 * @command: The command to execute
 *
 * Return: 0 on success, 1 on failure
 */
int execute_builtin(char **command)
{
    if (_strcmp(command[0], "exit") == 0)
    {
        free(command);
        exit(EXIT_SUCCESS);
    }
    else if (_strcmp(command[0], "env") == 0)
    {
        print_environment();
        return (0);
    }
    return (1);
}

/**
 * print_environment - Print the current environment
 */
void print_environment(void)
{
    int i = 0;
    char **env = environ;

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
}

