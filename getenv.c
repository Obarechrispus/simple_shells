#include "shell.h"

/**
 * _getenv - Gets an environment variable without using getenv.
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
    int i = 0;
    while (environ[i] != NULL)
    {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=')
        {
            return environ[i] + strlen(name) + 1;
        }
        i++;
    }
    return NULL;
}

