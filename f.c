#include "f.h"

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
    run_shell();
    return 0;
}

/**
 * run_shell - Main function to run the shell
 */
void run_shell(void)
{
    char buffer[BUFFER_SIZE];

    while (1)
    {
        /* Display the prompt */
        printf("$ ");

        /* Read the command from the user */
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the newline character */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Tokenize the command to separate command and arguments */
        char *token = strtok(buffer, " ");
        if (token != NULL)
        {
            /* Check if the command is "exit" */
            if (strcmp(token, "exit") == 0)
            {
                /* Exit the shell */
                printf("Exiting shell...\n");
                exit(EXIT_SUCCESS);
            }

            /* Check if the command is "env" */
            if (strcmp(token, "env") == 0)
            {
                /* Print the current environment */
                char **env = environ;
                while (*env != NULL)
                {
                    printf("%s\n", *env);
                    env++;
                }
                continue;
            }

            /* Create a child process */
            pid_t pid = fork();

            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                /* Child process */
                /* Execute the command */
                char *args[BUFFER_SIZE];
                int i = 0;
                while (token != NULL)
                {
                    args[i++] = token;
                    token = strtok(NULL, " ");
                }
                args[i] = NULL;

                if (execvp(args[0], args) == -1)
                {
                    /* If execvp fails, print an error message */
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                /* Parent process */
                /* Wait for the child process to complete */
                int status;
                if (waitpid(pid, &status, 0) == -1)
                {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                {
                    fprintf(stderr, "Command failed with exit status %d\n", WEXITSTATUS(status));
                }
            }
        }
    }
}

