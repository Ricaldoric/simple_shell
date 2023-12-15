#include "main.h"

/**
 * get_builtin - Identifies if a command builtin and pairs it
 * @cmd: The command to check
 * Return: Function pointer of the builtin command, NULL if not found
 */
int (*get_builtin(char *cmd))(data_shell *)
{
    builtin_t builtin[] = {
        { "env", _env },
        { "exit", exit_shell },
        { "setenv", _setenv },
        { "unsetenv", _unsetenv },
        { "cd", cd_shell },
        { "help", get_help },
        { NULL, NULL }
    };
    int i;

    for (i = 0; builtin[i].name; i++)
    {
        if (_strcmp(builtin[i].name, cmd) == 0)
            break;
    }

    return (builtin[i].f);
}

/**
 * This code was authored by Moffat and Sisinio.
 */
