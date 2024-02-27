#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void run_shell(void) {
	char **env;
	char buffer[BUFFER_SIZE];	
	char *token = strtok(buffer, " ");
	
	pid_t pid = fork();

	while (1) {
		/* Display the prompt */
		printf(":) ");

		/* Read the command from the user */
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
			/* Handle end of file (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove the newline character */
		buffer[strcspn(buffer, "\n")] = '\0';

		/* Tokenize the command to separate command and arguments */
		
		if (token != NULL) {
			/* Check if the command is "exit" */
			if (strcmp(token, "exit") == 0) {
				/* Exit the shell */
				printf("Exiting shell...\n");
				exit(EXIT_SUCCESS);
			}

			/* Check if the command is "env" */
			if (strcmp(token, "env") == 0) {
				/* Print the current environment */
				
				while (*env != NULL) {
					printf("%s\n", *env);
					env++;
				}
				continue;
			}

			/* Create a child process */
			

			if (pid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			} else if (pid == 0) {
				/* Child process */
				/* Execute the command */
				execvp(token, &token);
				
				/* If execvp fails, print an error message */
				perror("execvp");
				exit(EXIT_FAILURE);
			} else {
				/* Parent process */
				/* Wait for the child process to complete */
				waitpid(pid, NULL, 0);
			}
		}
	}
}
