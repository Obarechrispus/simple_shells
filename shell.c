#include "shell.h"

/**
 * execute_command - Execute a shell command.
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        /* This is the child process */

        /* Execute the command */
        if (execlp(command, command, (char *)NULL) == -1)
        {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* This is the parent process */

        /* Wait for the child process to complete */
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            fprintf(stderr, "./shell: %s: command not found\n", command);
        }
    }
}

/**
 * main - The main function of the shell program.
 * Return: Always 0.
 */
int main(void)
{
	int i;
	int has_space = 0;
    char buffer[MAX_COMMAND_LENGTH];

    while (1)
    {
        printf(PROMPT_STRING);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n"); /* Print a newline for better formatting */
                break;       /* Exit the loop on Ctrl+D (EOF) */
            }
            else
            {
                perror("Error reading input");
                exit(EXIT_FAILURE);
            }
        }

        /* Check if the command line ends with a newline */
        if (buffer[strlen(buffer) - 1] != '\n')
        {
            fprintf(stderr, "./shell: Command line must end with a new line.\n");
            while (getchar() != '\n'); /*Clear the input buffer*/
            continue;
        }

        /* Remove the newline character */
        buffer[strlen(buffer) - 1] = '\0';

        if (strcmp(buffer, "exit") == 0)
        {
            break; /* Exit the loop on "exit" command */
        }

        /* Check if the command contains spaces */
        for (i = 0; buffer[i]; i++)
        {
            if (buffer[i] == ' ')
            {
                has_space = 1;
                break;
            }
        }

        if (has_space)
        {
            fprintf(stderr, "./shell: Command lines are made only of one word.\n");
        }
        else
        {
            execute_command(buffer);
        }

        /* Display the prompt again */
    }

    return 0;
}

