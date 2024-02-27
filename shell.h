#ifndef SHELL_H
#define SHELL_H

#define PROMPT_STRING "\x1b[35mChris@yvonne:/# \x1b[0m"
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 100
#define MAX_INPUT_SIZE 1024

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
void execute_command(char *command);
void get_parent_pid(void);
void print_pid(void);
void print_arguments(char **av);
void prompt_user(void);
char **split_string(char *line);
void execute_program(char *program, char **arguments);
void create_child_processes(void);
void super_simple_shell(void);
void check_file_status(int ac, char **av);

void exercise_getppid(void);
void exercise_pid_max(void);
void exercise_av(void);
void exercise_read_line(void);
void exercise_command_line_to_av(void);
void exercise_execve_example(void);
void exercise_fork_example(void);
void exercise_fork_wait_execve(void);
void exercise_simple_shell(void);
void exercise_file_stat(int ac, char **av);
void exercise_find_file_in_path(int ac, char **av);
void exercise_print_environment(void);
void exercise_env_vs_environ(void);
char *_getenv(const char *name);
void exercise_print_path_directories(void);
void exercise_build_path_list(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
extern char **environ;
void print_environment(void)
void print_env_addresses(char **envp);
char *_getenv(const char *name);
void print_path_directories(void);
typedef struct PathNode
{
    char *directory;
    struct PathNode *next;
} PathNode;

char *find_command(const char *command);
void build_path_linked_list(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif /* SHELL_H */

