#include "f.h"

/**
 * read_input - Reads input from the user.
 *
 * Return: User input as a string.
 */
char *read_input(void)
{
	char *input = NULL;
	size_t len = 0;

	if (getline(&input, &len, stdin) == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			free(input);
			exit(EXIT_SUCCESS);
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	input[strlen(input) - 1] = '\0'; /* Remove newline character */
	return (input);
}

/**
 * execute_command - Executes the given command.
 *
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
	char **args = malloc(2 * sizeof(char *));
	pid_t pid;
	int status;
	/*char *args[] = {command, NULL};*/

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (args == NULL)
		{
			perror("mailloc");
			exit(EXIT_FAILURE);
		}

		args[0] = command;
		args[1] = NULL;

		if (strcmp(command, "echo") == 0)
		{
			/*ifree(args);*/
			execlp(command, command, NULL);
			perror(command);
			exit(EXIT_FAILURE);
		}
		else
		{

		/*if (execve(command, args, NULL) == -1)
		{
			fprintf(stderr, "%s: command not found\n", command);
			free(args);
			exit(EXIT_FAILURE);
		}*/
			if (execvp(command, args) == -1)
			{
				fprintf(stderr, "%s: command not found\n", command);
				exit(EXIT_FAILURE);
			}
		}
		free(args);
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}

