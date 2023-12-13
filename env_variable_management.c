#include "shell.h"

/**
 * fetch_environment - Retrieves a string array of the environment
 * @info: Structure with shell information
 * Return: String array of the environment
 */
char **fetch_environment(info_t *info)
{
    if (!info->environ || info->env_modified)
    {
        free(info->environ);
        info->environ = list_to_env_array(info->env);
        info->env_modified = 0;
    }
    return info->environ;
}

/**
 * remove_env_var - Deletes an environment variable
 * @info: Structure with shell information
 * @var_name: Environment variable name to remove
 * Return: 1 if deleted, 0 otherwise
 */
int remove_env_var(info_t *info, char *var_name)
{
    list_t *current = info->env;
    size_t index = 0;
    char *env_entry;

    while (current)
    {
        env_entry = find_env_var(current->str, var_name);
        if (env_entry && *env_entry == '=')
        {
            delete_env_node(&(info->env), index);
            info->env_modified = 1;
            current = info->env;
            index = 0;
            continue;
        }
        current = current->next;
        index++;
    }
    return info->env_modified;
}

/**
 * add_or_update_env_var - Adds or updates an environment variable
 * @info: Structure with shell information
 * @var_name: Environment variable name
 * @value: Value to set for the environment variable
 * Return: 0 on success, 1 on failure
 */
int add_or_update_env_var(info_t *info, char *var_name, char *value)
{
    char *env_string;
    list_t *current;
    char *env_entry;

    if (!var_name || !value)
        return 1;

    env_string = create_env_string(var_name, value);
    if (!env_string)
        return 1;

    current = info->env;
    while (current)
    {
        env_entry = find_env_var(current->str, var_name);
        if (env_entry && *env_entry == '=')
        {
            update_env_node(current, env_string);
            info->env_modified = 1;
            return 0;
        }
        current = current->next;
    }

    append_env_node(&(info->env), env_string);
    info->env_modified = 1;
    return 0;
}
