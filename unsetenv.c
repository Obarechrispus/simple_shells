#include "shell.h"

/**
 * _unsetenv - Deletes the variable name from the environment without using unsetenv.
 * @name: The name of the environment variable to delete
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
    if (name == NULL || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "Invalid variable name\n");
        return -1;
    }

    char *existing_value = _getenv(name);

    if (existing_value != NULL)
    {
        size_t new_env_size = 1; // Including the NULL pointer at the end

        int i = 0;
        while (environ[i] != NULL)
        {
            if (environ[i] != existing_value)
            {
                new_env_size++;
            }
            i++;
        }

        char **new_environ = (char **)malloc(new_env_size * sizeof(char *));
        if (new_environ == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        i = 0;
        int j = 0;
        while (environ[i] != NULL)
        {
            if (environ[i] != existing_value)
            {
                new_environ[j]

