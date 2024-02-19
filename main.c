#include "main.h"

int main(int ac, char **argv)
{
	char *prompt = "(Eshell) $ ";
	char *lineptr;
	size_t n = 0;
	ssize_t read;
	(void)ac;
	(void)argv;
	while(1)
	{
	printf("%s", prompt);
	read = getline(&lineptr, &n, stdin);
	/*printf("%s/n", lineptr);*/
	if (read == -1)
	{
		break;
	}
	printf("%s/n", lineptr);
	}
	 free(lineptr);
	return (0);
}

