#include "shell.h"

/**
 * display_command_history - Shows the history of commands executed,
 *                           each with a line number starting at 0.
 * @info: Structure holding arguments, for uniform function signature.
 * Return: Always returns 0
 */
int display_command_history(info_t *info)
{
    list_print(info->history);
    return (0);
}

/**
 * remove_alias - Removes an alias string
 * @info: Structure with shell parameters
 * @alias_string: The alias string to be removed
 * Return: Always 0 on success, 1 on failure
 */
int remove_alias(info_t *info, char *alias_string)
{
    char *separator, character;
    int result;

    separator = find_char(alias_string, '=');
    if (!separator)
        return (1);
    character = *separator;
    *separator = 0;
    result = delete_list_node(&(info->alias),
                              find_list_index(info->alias, list_node_starts_with(info->alias, alias_string, -1)));
    *separator = character;
    return (result);
}

/**
 * create_alias - Creates or updates an alias
 * @info: Structure with shell parameters
 * @alias_string: The alias string to be set
 * Return: Always 0 on success, 1 on failure
 */
int create_alias(info_t *info, char *alias_string)
{
    char *separator;

    separator = find_char(alias_string, '=');
    if (!separator)
        return (1);
    if (!*++separator)
        return (remove_alias(info, alias_string));

    remove_alias(info, alias_string);
    return (append_to_list_end(&(info->alias), alias_string, 0) == NULL);
}

/**
 * output_alias - Outputs a single alias
 * @node: Node in the alias list
 * Return: Always 0 on success, 1 on failure
 */
int output_alias(list_t *node)
{
    char *separator = NULL, *alias = NULL;

    if (node)
    {
        separator = find_char(node->str, '=');
        for (alias = node->str; alias <= separator; alias++)
            putchar(*alias);
        putchar('\'');
        puts(separator + 1);
        puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * manage_aliases - Handles the alias functionality similar to the built-in alias command
 * @info: Structure holding arguments, for uniform function signature.
 * Return: Always returns 0
 */
int manage_aliases(info_t *info)
{
    int index = 0;
    char *separator = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            output_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (index = 1; info->argv[index]; index++)
    {
        separator = find_char(info->argv[index], '=');
        if (separator)
            create_alias(info, info->argv[index]);
        else
            output_alias(list_node_starts_with(info->alias, info->argv[index], '='));
    }

    return (0);
}
