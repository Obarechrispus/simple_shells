#include "main.h"

/**
 * list_files - Recursive ls
 *
 * @dir_name: Directory name
 */
void list_files(const char *dir_name)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_name);

    if (dir == NULL)
    {
        perror("Error");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                printf("Directory: %s\n", entry->d_name);
                char path[1024];
                snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
                list_files(path);
            }
        }
        else
        {
            printf("File: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

/**
 * main - Recursive ls
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage: %s path_to_directory\n", av[0]);
        return (1);
    }

    list_files(av[1]);

    return (0);
}

