#include "main.h"
#include "string.h"

int main(int ac, char **argv)
{
	char *prompt = "(Chris) $ ";
	char *lineptr;
	size_t n = 0;
	ssize_t read;
	char *copy = NULL;
	const char *delim = " \n";
	(void)ac;
	(void)argv;
	(void)copy;
	(void)delim;

	while(1)
	{
	printf("%s", prompt);
	read = getline(&lineptr, &n, stdin);
	
	if (read == -1)
	{
		break;
	}
	if (strcmp(lineptr, "exit\n") == 1)
	{
            printf("Exiting the shell...\n");
            break;
        }
	
	printf("%s\n", lineptr);
	}
	 free(lineptr);
	return (0);
}

