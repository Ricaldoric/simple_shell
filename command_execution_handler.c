#include "main.h"

/**
 * exec_line - Executes a command line
 * @datash: Data relevant to the shell (arguments)
 * Return: 1 on success, or appropriate return value of the called function
 */
int exec_line(data_shell *datash)
{
    int (*builtin)(data_shell *datash);

    if (datash->args[0] == NULL)
        return (1);

    builtin = get_builtin(datash->args[0]);

    if (builtin != NULL)
        return (builtin(datash));

    return (cmd_exec(datash));
}

/**
 * This code was authored by Moffat and Sisinio.
 */
