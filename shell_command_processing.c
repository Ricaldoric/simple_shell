#include "shell.h"

/**
 * process_shell_commands - Processes shell commands with chaining
 * @shell_info: Shell information structure
 * Return: void
 */
void process_shell_commands(shell_info_t *shell_info)
{
    size_t buf_pos = 0;

    while (shell_info->command_buffer[buf_pos])
    {
        if (is_command_chain(shell_info, shell_info->command_buffer, &buf_pos))
            evaluate_command_chain(shell_info, shell_info->command_buffer, &buf_pos);

        process_command(shell_info, &shell_info->command_buffer[buf_pos]);
        buf_pos++;
    }
}

/**
 * replace_aliases - Replaces aliases in the command string
 * @shell_info: Shell information structure
 * Return: void
 */
void replace_aliases(shell_info_t *shell_info)
{
    for (int i = 0; shell_info->argv[i]; i++)
    {
        char *alias_replacement = find_alias(shell_info, shell_info->argv[i]);
        if (alias_replacement)
            shell_info->argv[i] = duplicate_string(alias_replacement);
    }
}

/**
 * replace_variables - Replaces variables in the command string
 * @shell_info: Shell information structure
 * Return: void
 */
void replace_variables(shell_info_t *shell_info)
{
    for (int i = 0; shell_info->argv[i]; i++)
        replace_variable_in_command(shell_info, &shell_info->argv[i]);
}

/**
 * replace_variable_in_command - Replaces a variable in a command string
 * @shell_info: Shell information structure
 * @command: Command string to process
 * Return: void
 */
void replace_variable_in_command(shell_info_t *shell_info, char **command)
{
    if (is_variable(*command))
        *command = get_variable_value(shell_info, *command);
}
