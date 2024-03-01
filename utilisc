#include "shell.h"

/**
 * check_command - Check if a command exists in the PATH
 * @command: The command to check
 *
 * Return: The full path of the command if it exists, NULL otherwise
 */
char *check_command(char *command)
{
    char *path, *token, *full_path;
    struct stat st;
    char *path_copy;

    path = getenv("PATH");
    path_copy = _strdup(path);

    if (!path_copy)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        full_path = path_concat(token, command);
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

/**
 * path_concat - Concatenate a directory and a command
 * @dir: The directory
 * @command: The command
 *
 * Return: The concatenated path
 */
char *path_concat(char *dir, char *command)
{
    char *path;
    size_t dir_len, command_len;

    dir_len = _strlen(dir);
    command_len = _strlen(command);

    path = malloc(dir_len + command_len + 2);
    if (!path)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    _strcpy(path, dir);
    path[dir_len] = '/';
    _strcpy(path + dir_len + 1, command);

    return (path);
}

