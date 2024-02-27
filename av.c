#include <stdio.h>

/**
 * main - Print arguments
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    unsigned int i;
	(void)ac;
    i = 1;
    while (av[i])
    {
        printf("%s\n", av[i]);
        i++;
    }
    return (0);
}

