#include "main.h"

/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    unsigned int i;
    struct stat st;

    if (ac < 2)
    {
        printf("Usage: %s path_to_file ...\n", av[0]);
        return (1);
    }

    for (i = 1; i < ac; i++)
    {
        if (stat(av[i], &st) == 0)
        {
            printf("File: %s\n", av[i]);
            printf("Size: %ld bytes\n", st.st_size);
            printf("Blocks: %ld\n", st.st_blocks);
            printf("Block size: %ld bytes\n", st.st_blksize);
            printf("Inode number: %ld\n", st.st_ino);
            printf("Links: %ld\n", st.st_nlink);
            printf("Last status change: %s", ctime(&st.st_ctime));
            printf("Last file access: %s", ctime(&st.st_atime));
            printf("Last file modification: %s", ctime(&st.st_mtime));
            printf("\n");
        }
        else
        {
            perror("Error:");
        }
    }

    return (0);
}

