#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

extern char **environ;

#define BUFSIZE 256
#define DELIMITERS " \t\r\n\a"
#define UNUSED(x) (void)(x)

char _gentenv;
/* check_command.c */
int *check_commands(char *command);
char *check_command(char *command);
char *path_concat(char *dir, char *command);

/* builtins.c */
int is_builtin(char *command);
int execute_builtin(char **command);
void print_environment(void);

/* parse.c */
char **parse_line(char *line);

/* execute.c */
int execute_command(char **tokens);
int execute(char *command, char **args);

/* utilis.c */
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);

void shell_loop(void);

char **split_line(char *line);

char *read_line(void);

#endif /* SHELL_H */

