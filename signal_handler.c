#include "main.h"

/**
 * get_sigint - Handles the Ctrl+C signal in the prompt
 * @sig: Signal number
 * Description: Upon receiving a SIGINT signal, 
 * prints a new prompt line
 */
void get_sigint(int sig)
{
    (void)sig; // Unused parameter
    write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * This code was authored by Moffat and Sisinio.
 */
