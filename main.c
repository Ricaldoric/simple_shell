#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void execute_command(char *cmd);
int read_command(char *buffer);

/* 
 * Main function - Entry point for the simple shell 
 */
int main(void) {
    char buffer[BUFFER_SIZE]; /* Buffer to store the command input */

    while (1) {
        printf("$ "); /* Shell prompt */

        /* Read a command and continue if none is read */
        if (!read_command(buffer)) {
            continue;
        }

        /* Exit the shell if the command is 'exit' */
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        /* Execute the command entered by the user */
        execute_command(buffer);
    }

    return EXIT_SUCCESS;
}

/* 
 * Reads a command from standard input.
 * Returns 1 if a command is read, 0 otherwise.
 */
int read_command(char *buffer) {
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        /* Exit on End-of-File (Ctrl+D) or handle read error */
        if (feof(stdin)) {
            exit(EXIT_SUCCESS); 
        } else {
            perror("read_command: fgets");
            exit(EXIT_FAILURE);
        }
    }
    return 1;
}

/* 
 * Executes the command entered by the user.
 * This function is a placeholder and needs further implementation.
 */
void execute_command(char *cmd) {
    /* Placeholder for command execution logic */
    printf("Executing command: %s", cmd);
    /* Further implementation will be required here. */
}

