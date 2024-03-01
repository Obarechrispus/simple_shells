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
		printf("#alxisfun$ ");
		input = read_input();
		execute_command(input);
		free(input);
	}

	return (0);
}
