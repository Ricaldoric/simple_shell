#include "main.h"

/**
 * aux_help - Display help for the 'help' command
 * Description: Provides help information for the builtin 'help' command
 * Return: No return (void function)
 */
void aux_help(void)
{
    char *help = "help: help [-dms] [pattern ...]\n";

    write(STDOUT_FILENO, help, _strlen(help));
    help = "\tDisplay information about builtin commands.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Displays brief summaries of builtin commands.\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_alias - Display help for the 'alias' command
 * Description: Provides help information for the builtin 'alias' command
 * Return: No return (void function)
 */
void aux_help_alias(void)
{
    char *help = "alias: alias [-p] [name[=value]...]\n";

    write(STDOUT_FILENO, help, _strlen(help));
    help = "\tDefine or display aliases.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_cd - Display help for the 'cd' command
 * Description: Provides help information for the builtin 'cd' command
 * Return: No return (void function)
 */
void aux_help_cd(void)
{
    char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

    write(STDOUT_FILENO, help, _strlen(help));
    help = "\tChange the shell working directory.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * This code was authored by Moffat and Sisinio.
 */
