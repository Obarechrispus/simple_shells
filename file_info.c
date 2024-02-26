#include "shell.h"

/**
 * main - Get information about a file
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    FILE *file;
    char ch;
    int character_count = 0, word_count = 0, line_count = 0;

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
        character_count++;

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
        {
            word_count++;
        }

        if (ch == '\n' || ch == '\0')
        {
            line_count++;
        }
    }

    fclose(file);

    printf("File: %s\n", av[1]);
    printf("Characters: %d\n", character_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    return (0);
}

