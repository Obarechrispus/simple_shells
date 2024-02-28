#include "shell.h"

/**
 * check_commands - Check if the command exists in the PATH
 * @command: The command to check
 *
 * Return: 1 if the command exists, 0 otherwise
 */
int *check_commands(char *command)
{	
    char *path;
    char *token;
    struct stat st;
    int found = 0;
	(void)found;
	(void)command;
    path = getenv("PATH");
    token = strtok(path, ":");
    while (token != NULL)
    {
        if (stat(token, &st) == 0)
        {
            if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
            {
                found = 1;
                break;
            }
        }
        token = strtok(NULL, ":");
    }

    free(path);
    return (0);
}

