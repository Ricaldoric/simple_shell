#include "main.h"

/**
 * read_line - Captures the user's input from 
 *standard input
 * @i_eof: Pointer to store the status 
 * of getline (end-of-file indicator)
 * Return: The captured input string from the user
 * Description: Utilizes getline to 
 * dynamically allocate and read the user's input
 */
char *read_line(int *i_eof)
{
    char *input = NULL;
    size_t bufsize = 0;

    *i_eof = getline(&input, &bufsize, stdin);

    return (input);
}
