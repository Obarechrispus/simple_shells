#include "shell.h"

int main(void)
{
	char *line = read_line();
	char **args = parse_line(line);
	/*int status = execute(args);*/

	/* Display prompt and read input in a loop */
	do
	{
		printf("c_shell> ");

		/* Check if the command is 'exit' to exit the shell */
		if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			/* Handle exit command */
			free(line);
			free(args);
			exit(EXIT_SUCCESS);
		}

		free(line);
		free(args);

	} while (1);

	return 0;
}

char *read_line(void)
{
	/* Read a line of input from the user */
	char *line = NULL;
	size_t bufsize = 0;

	ssize_t chars_read = getline(&line, &bufsize, stdin);

	/* Check if getline encountered an error or end of file (Ctrl+D) */
	if (chars_read == -1)
	{
		if (feof(stdin))
		{
			/* End of file (Ctrl+D) */
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Error reading line");
			exit(EXIT_FAILURE);
		}
	}

	/* Remove newline character from the end of the line */
	if (line[chars_read - 1] == '\n')
	{
		line[chars_read - 1] = '\0';
	}

	return line;
}

char **parse_line(char *line)
{
	/* Parse the input line into an array of tokens */
	int bufsize = MAX_INPUT_SIZE / 2;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	/* Check if memory allocation was successful */
	if (!tokens)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	/* Tokenize the input line using strtok */
	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		/* Store the token in the array */
		tokens[position] = token;
		position++;

		/* Check if the array needs to be resized */
		if (position >= bufsize)
		{
			bufsize += MAX_INPUT_SIZE / 2;
			tokens = realloc(tokens, bufsize * sizeof(char *));

			/* Check if memory reallocation was successful */
			if (!tokens)
			{
				perror("Allocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL; /* Set the last element to NULL */
	return tokens;
}

int execute(char **args)
{
	char *command_path = find_command(args[0]);
	char **env = environ;
	int status;

	pid_t pid, wpid;
	pid = fork();

	/* Execute a command */
	if (args[0] == NULL)
	{
		/* No command entered */
		return 1;
	}
	if (strcmp(args[0], "env") == 0)
	{
		/*If the command is "env", print the current environment*/
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return 1;
	}

	if (command_path == NULL)
	{
		fprintf(stderr, "c_shell: %s: command not found\n", args[0]);
		return 1;
	}


	/* Check if fork encountered an error */
	if (pid == -1)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execv(command_path, args) == -1)
		{
			perror("c_shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (wpid == -1 && errno == EINTR);

		if (wpid == -1)
		{
			perror("Error waiting for child process");
			exit(EXIT_FAILURE);
		}
	}

	free(command_path);
	return 1;
}


/**
 * find_command - Find the full path of a command using the PATH environment variable.
 *
 * @command: The command to find.
 * Return: The full path of the command if found, NULL otherwise.
 */
char *find_command(const char *command)
{
	/* Find the full path of a command using the PATH environment variable */
	char *result = NULL;
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");
	char *command_path = malloc(strlen(token) + strlen(command) + 2);

	if (path == NULL)
	{
		fprintf(stderr, "c_shell: PATH environment variable not set\n");
		exit(EXIT_FAILURE);
	}

	if (path_copy == NULL)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		if (command_path == NULL)
		{
			perror("Allocation error");
			exit(EXIT_FAILURE);
		}

		sprintf(command_path, "%s/%s", token, command);

		if (access(command_path, F_OK) == 0)
		{
			result = strdup(command_path);
			free(command_path);
			free(path_copy);
			break;
			/*free(path_copy);  Free the copied path
			return command_path;  Return the valid path*/
		}

		free(command_path);/*Free the memory in case the path is not valid*/
		token = strtok(NULL, ":");
	}

	free(path_copy);/*Free the copied path if the command is not found*/
	return result;/*Return NULL if the command is not found in any path*/
}

