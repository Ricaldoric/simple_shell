#include "shell.h"

/**
 * fetch_history_filepath - Retrieves the path to the history file
 * @info: Shell information structure
 * Return: Path to the history file
 */
char *fetch_history_filepath(info_t *info)
{
    char *home_dir = get_env_value(info, "HOME=");
    char *history_path;

    if (!home_dir)
        return NULL;

    history_path = malloc(strlen(home_dir) + strlen(HIST_FILE) + 2);
    if (!history_path)
        return NULL;

    strcpy(history_path, home_dir);
    strcat(history_path, "/");
    strcat(history_path, HIST_FILE);
    return history_path;
}

/**
 * save_history - Saves the shell history to a file
 * @info: Shell information structure
 * Return: 1 on success, -1 on failure
 */
int save_history(info_t *info)
{
    int file_descriptor;
    char *history_filename = fetch_history_filepath(info);
    list_t *current_node;

    if (!history_filename)
        return -1;

    file_descriptor = open(history_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(history_filename);
    if (file_descriptor == -1)
        return -1;

    for (current_node = info->history; current_node; current_node = current_node->next)
    {
        write_string_to_fd(current_node->str, file_descriptor);
        write_char_to_fd('\n', file_descriptor);
    }
    flush_fd_buffer(file_descriptor);
    close(file_descriptor);
    return 1;
}

/**
 * load_history - Loads the shell history from a file
 * @info: Shell information structure
 * Return: Count of history entries read
 */
int load_history(info_t *info)
{
    int file_descriptor, history_count = 0;
    ssize_t read_size, file_size = 0;
    struct stat file_stat;
    char *history_buffer, *filename = fetch_history_filepath(info);

    if (!filename)
        return 0;

    file_descriptor = open(filename, O_RDONLY);
    free(filename);
    if (file_descriptor == -1 || fstat(file_descriptor, &file_stat) || (file_size = file_stat.st_size) < 2)
        return 0;

    history_buffer = malloc(file_size + 1);
    if (!history_buffer)
        return 0;

    read_size = read(file_descriptor, history_buffer, file_size);
    history_buffer[file_size] = '\0';
    close(file_descriptor);

    if (read_size <= 0)
        return (free(history_buffer), 0);

    history_count = process_history_buffer(info, history_buffer, file_size);
    free(history_buffer);
    prune_history(info);
    update_history_numbers(info);
    return history_count;
}

/**
 * append_to_history_list - Appends a new entry to the history list
 * @info: Shell information structure
 * @entry: History entry to add
 * @index: Index of the entry
 * Return: 0 on success
 */
int append_to_history_list(info_t *info, char *entry, int index)
{
    if (!info->history)
        info->history = create_history_node(entry, index);
    else
        add_history_node(info->history, entry, index);

    return 0;
}

/**
 * update_history_numbers - Updates the indices in the history list
 * @info: Shell information structure
 * Return: Updated count of history entries
 */
int update_history_numbers(info_t *info)
{
    list_t *current = info->history;
    int index = 0;

    while (current)
    {
        current->num = index++;
        current = current->next;
    }
    return (info->histcount = index);
}
