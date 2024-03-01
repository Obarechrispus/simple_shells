#include "f.h"

/**
 * main - Simple shell program
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input;

	while (1)
	{
		display_prompt();
		input = read_input();
		execute_command(input);
		free(input);
	}

	return (0);
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

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

		if (execve(command, args, NULL) == -1)
		{
			perror(command);
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}

