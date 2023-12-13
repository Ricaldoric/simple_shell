#include "shell.h"

/**
 * display_env - Outputs the current environment variables
 * @info: Structure with shell information.
 * Return: Always 0
 */
int display_env(info_t *info)
{
    list_display(info->env);
    return (0);
}

/**
 * fetch_env_var - Retrieves the value of an environment variable
 * @info: Structure containing shell information
 * @var_name: Environment variable name
 * Return: Pointer to the environment variable value
 */
char *fetch_env_var(info_t *info, const char *var_name)
{
    list_t *current_node = info->env;
    char *value_start;

    while (current_node)
    {
        value_start = match_prefix(current_node->str, var_name);
        if (value_start && *value_start)
            return (value_start);
        current_node = current_node->next;
    }
    return (NULL);
}

/**
 * set_env_var - Sets or updates an environment variable
 * @info: Structure with shell information.
 * Return: 0 on success, 1 on error
 */
int set_env_var(info_t *info)
{
    if (info->argc != 3)
    {
        error_puts("Incorrect number of arguments\n");
        return (1);
    }
    if (env_set(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * remove_env_var - Removes an environment variable
 * @info: Structure with shell information.
 * Return: 0 on success, 1 on error
 */
int remove_env_var(info_t *info)
{
    int arg_index;

    if (info->argc == 1)
    {
        error_puts("Insufficient arguments.\n");
        return (1);
    }
    for (arg_index = 1; arg_index <= info->argc; arg_index++)
        env_unset(info, info->argv[arg_index]);

    return (0);
}

/**
 * init_env_list - Fills the environment variable list
 * @info: Structure with shell information.
 * Return: Always 0
 */
int init_env_list(info_t *info)
{
    list_t *new_node = NULL;
    size_t index;

    for (index = 0; environ[index]; index++)
        append_node(&new_node, environ[index], 0);
    info->env = new_node;
    return (0);
}
