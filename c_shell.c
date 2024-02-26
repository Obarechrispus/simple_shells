#include "shell.h"

/**
 * read_line - Read a line of input from the user.
 *
 * Return: The input string.
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS); // End of file (Ctrl+D)
        }
        else
        {
            perror("Error reading line");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

/**
 * parse_line - Parse the input line into an array of tokens.
 *
 * @line: The input line.
 * 
 * Return: An array of tokens.
 */
char **parse_line(char *line)
{
    int bufsize = MAX_INPUT_SIZE / 2;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += MAX_INPUT_SIZE / 2;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * execute - Execute a command.
 *
 * @args: Array of command arguments.
 * 
 * Return: 1 if the shell should continue, 0 if it should exit.
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("Error forking");
    }
    else
    {
        // Parent process
       waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}

/**
 * main - Simple Shell
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("Chris@Yvonne:/# ");
        line = read_line();
        args = parse_line(line);
        status = execute(args);

        free(line);
        free(args);

    } while (status);

    return 0;
}

