#include <stdio.h>
#include <stdlib.h>

/**
 * main - Print prompt
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;

    printf("$ ");
    getline(&line, &len, stdin);
    printf("%s", line);

    free(line);
    return (0);
}

