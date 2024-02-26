#include "shell.h"

/**
 * create_child_processes - Creates child processes.
 */
void create_child_processes(void)
{
    pid_t my_pid;
    pid_t child_pid;

    printf("Before fork\n");
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    printf("After fork\n");
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);

    if (child_pid == 0)
    {
        printf("(%u) Nooooooooo!\n", my_pid);
    }
    else
    {
        printf("(%u) %u, I am your father\n", my_pid, child_pid);
    }
}

int main(void)
{
    create_child_processes();

    return (0);
}

