#include "shell.h"

/**
 * shell_exit - Terminates the shell process
 * @info: Structure holding arguments, for uniform function signature.
 * Return: Triggers exit with a specific status
 * Exits with status 0 if info.argv[0] is not "exit"
 */
int shell_exit(info_t *info)
{
    int status_check;

    if (info->argv[1]) /* Checks for an exit argument */
    {
        status_check = parse_exit_arg(info->argv[1]);
        if (status_check == -1)
        {
            info->status = 2;
            display_error(info, "Invalid number: ");
            error_puts(info->argv[1]);
            error_putchar('\n');
            return (1);
        }
        info->err_num = parse_exit_arg(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * shell_cd - Modifies the current working directory
 * @info: Structure holding arguments, for uniform function signature.
 * Return: Always returns 0
 */
int shell_cd(info_t *info)
{
    char *current_path, *target_dir, buffer[1024];
    int dir_change_status;

    current_path = getcwd(buffer, 1024);
    if (!current_path)
        _puts("Error: Failed to retrieve current working directory.\n");

    if (!info->argv[1]) /* No argument provided */
    {
        target_dir = fetch_env_var(info, "HOME=");
        if (!target_dir)
            dir_change_status = 
                chdir((target_dir = fetch_env_var(info, "PWD=")) ? target_dir : "/");
        else
            dir_change_status = chdir(target_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0) /* Argument is '-' */
    {
        if (!fetch_env_var(info, "OLDPWD="))
        {
            _puts(current_path);
            _putchar('\n');
            return (1);
        }
        _puts(fetch_env_var(info, "OLDPWD=")), _putchar('\n');
        dir_change_status = 
            chdir((target_dir = fetch_env_var(info, "OLDPWD=")) ? target_dir : "/");
    }
    else /* Other arguments */
        dir_change_status = chdir(info->argv[1]);

    if (dir_change_status == -1) /* Failed to change directory */
    {
        display_error(info, "Cannot change directory to ");
        error_puts(info->argv[1]), error_putchar('\n');
    }
    else /* Successfully changed directory */
    {
        update_env_var(info, "OLDPWD", fetch_env_var(info, "PWD="));
        update_env_var(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * shell_help - Displays help information for the shell commands
 * @info: Structure holding arguments, for uniform function signature.
 * Return: Always returns 0
 */
int shell_help(info_t *info)
{
    char **argument_list;

    argument_list = info->argv;
    _puts("Help functionality activated. More details to be implemented.\n");
    if (0) /* Temporary placeholder */
        _puts(*argument_list);
    return (0);
}
