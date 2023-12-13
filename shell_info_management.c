#include "shell.h"

/**
 * initialize_info - Initializes the info_t structure
 * @info: Pointer to the info_t structure
 */
void initialize_info(info_t *info)
{
    memset(info, 0, sizeof(info_t));
}

/**
 * setup_info - Sets up the info_t structure with arguments
 * @info: Pointer to the info_t structure
 * @args: Argument vector
 */
void setup_info(info_t *info, char **args)
{
    info->fname = args[0];
    if (info->arg)
    {
        parse_arguments(info);
        update_argument_count(info);
        substitute_aliases(info);
        substitute_variables(info);
    }
}

/**
 * release_info - Frees fields in the info_t structure
 * @info: Pointer to the info_t structure
 * @complete: Flag to indicate whether to free all fields
 */
void release_info(info_t *info, int complete)
{
    free_arguments(info->argv);
    reset_shell_path(info);

    if (complete)
    {
        free_if_allocated(&(info->arg), info->cmd_buf);
        free_linked_lists(info);
        free_environment(info->environ);
        close_file_descriptor(info);
        flush_output_buffer();
    }
}
