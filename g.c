#include "c.h"

extern char **environ;

void run_shell(void);

int main(void)
{
	run_shell();
	return 0;
}

void run_shell(void)
{
	while (1)
	{
		char buffer[BUFFER_SIZE];
		char *tokens[BUFFER_SIZE];
		size_t token_count = 0;
		int exit_status = 0;
		char **env = environ;
		char *token = strtok(buffer, " ");
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");
		int command_found = 0;
		char command_path[BUFFER_SIZE];
		pid_t pid = fork();
		int status;

		/* Display the prompt */
		printf(":) ");

		/* Read the command from the user */
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			/* Handle end of file (Ctrl+D) */
			if (feof(stdin))
			{
				printf("\nExiting shell...\n");
				break;
			}
			else
			{
				perror("fgets");
				exit(EXIT_FAILURE);
			}
		}

		/* Remove the newline character */
		buffer[strcspn(buffer, "\n")] = '\0';

		/* Tokenize the entire input line */
		while (token != NULL)
		{
			tokens[token_count++] = token;
			token = strtok(NULL, " ");
		}

		if (token_count > 0)
		{
			/* Check if the command is "exit" */
			if (strcmp(tokens[0], "exit") == 0)
			{
				/* Check if an argument is provided for exit status */
				if (token_count > 1)
				{
					/* Convert the argument to an integer */
					exit_status = atoi(tokens[1]);
				}

				/* Exit the shell with the specified status */
				printf("Exiting shell with status %d...\n", exit_status);
				exit(exit_status);
			}

			/* Check if the command is "env" */
			if (strcmp(tokens[0], "env") == 0)
			{
				/* Print the current environment */
				while (*env != NULL)
				{
					printf("%s\n", *env);
					env++;
				}
				continue;
			}

			/* Search for the command in the directories listed in the PATH */
			while (dir != NULL)
			{
				snprintf(command_path, BUFFER_SIZE, "%s/%s", dir, tokens[0]);

				/* Check if the command exists in the current directory */
				if (access(command_path, X_OK) == 0)
				{
					command_found = 1;
					break;
				}

				dir = strtok(NULL, ":");
			}

			free(path_copy);

			if (!command_found)
			{
				fprintf(stderr, "Command not found: %s\n", tokens[0]);
				continue;
			}

			/* Create a child process */

			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				/* Child process */
				/* Execute the command with arguments */
				if (execvp(tokens[0], tokens) == -1)
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
				if (waitpid(pid, &status, 0) == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}

