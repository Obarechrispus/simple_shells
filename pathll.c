#include "shell.h"

PathNode *head = NULL;

/**
 * build_path_linked_list - Builds a linked list of the PATH directories.
 */
void build_path_linked_list(void)
{
    char *path = _getenv("PATH");
    if (path != NULL)
    {
        char *token = strtok(path, ":");
        while (token != NULL)
        {
            PathNode *new_node = (PathNode *)malloc(sizeof(PathNode));
            if (new_node == NULL)
            {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            new_node->directory = strdup(token);
            new_node->next = head;
            head = new_node;

            token = strtok(NULL, ":");
        }
    }
}

