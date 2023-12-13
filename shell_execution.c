#include "shell.h"

/**
 * shell_main_loop - Main loop of the shell
 * @shell_info: Shell information structure
 * @args: Arguments passed to the shell
 * Return: Exit code of the shell
 */
int shell_main_loop(shell_info_t *shell_info, char **args)
{
    ssize_t input_status = 0;
    int command_status = 0;

    while (input_status != -1 && command_status != EXIT_SHELL_CODE)
    {
        reset_shell_info(shell_info);
        prompt_if_interactive(shell_info);

        input_status = fetch_user_input(shell_info);
        if (input_status != -1)
        {
            initialize_shell_info(shell_info, args);
            command_status = execute_builtin_or_command(shell_info);
        }
        else if (is_interactive_mode(shell_info))
            putchar('\n');

        release_shell_resources(shell_info, false);
    }

    finalize_shell_execution(shell_info);
    return determine_exit_code(shell_info, command_status);
}

/**
 * execute_builtin_or_command - Executes a builtin or external command
 * @shell_info: Shell information structure
 * Return: Status of the command execution
 */
int execute_builtin_or_command(shell_info_t *shell_info)
{
    int command_status = execute_builtin_command(shell_info);

    if (command_status == BUILTIN_NOT_FOUND)
        execute_external_command(shell_info);

    return command_status;
}
