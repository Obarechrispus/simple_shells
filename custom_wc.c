#include "shell.h"

/**
 * main - Custom word count (wc)
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    FILE *file;
    char ch;
    int word_count = 0;

    if (ac != 2)
    {
        printf("Usage: %s filename\n", av[0]);
        return (1);
    }

    file = fopen(av[1], "r");

    if (file == NULL)
    {
        perror("Error");
        return (1);
    }

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
        {
            word_count++;
        }
    }

    fclose(file);

    printf("Words: %d\n", word_count);

    return (0);
}

