#include "shell.h"

/**
 * _setenv - Changes or adds an environment variable without using setenv.
 * @name: The name of the environment variable
 * @value: The value to set for the environment variable
 * @overwrite: Flag to overwrite if the variable already exists
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "Invalid variable name\n");
        return -1;
    }

    char *existing_value = _getenv(name);

    if (existing_value != NULL)
    {
        if (overwrite)
        {
            free(environ[existing_value - environ[0]]);
        }
        else
        {
            return 0; // Variable exists, and overwrite is not set
        }
    }

    size_t new_env_size = 2; // Including the NULL pointer at the end
    if (existing_value != NULL)
    {
        new_env_size += strlen(existing_value) + 1; // +1 for '='
    }
    new_env_size += strlen(name) + 1 + strlen(value) + 1; // +1 for '=' and +1 for NULL terminator

    char **new_environ = (char **)malloc(new_env_size * sizeof(char *));
    if (new_environ == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (environ[i] != NULL)
    {
        if (environ[i] != existing_value)
        {
            new_environ[i] = environ[i];
        }
        else
        {
            free(environ[i]);
        }
        i++;
    }

    char *new_env_var = (char *)malloc(strlen(name) + 1 + strlen(value) + 1);
    if (new_env_var == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    sprintf(new_env_var, "%s=%s", name, value);
    new_environ[i] = new_env_var;
    new_environ[i + 1] = NULL;

    free(environ);
    environ = new_environ;

    return 0;
}

