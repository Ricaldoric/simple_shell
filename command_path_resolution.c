#include "shell.h"

/**
 * is_executable - Checks if a file is an executable
 * @info: Shell information structure
 * @filepath: Path to the file
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(shell_info_t *info, char *filepath)
{
    struct stat file_stat;

    if (!filepath || stat(filepath, &file_stat) != 0)
        return 0;

    return (file_stat.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * duplicate_substring - Duplicates a substring
 * @src: Source string
 * @start: Starting index
 * @end: Ending index
 * Return: Pointer to the new substring
 */
char *duplicate_substring(char *src, int start, int end)
{
    static char buffer[1024];
    int k = 0;

    for (int i = start; i < end; i++)
        if (src[i] != ':')
            buffer[k++] = src[i];

    buffer[k] = '\0';
    return buffer;
}

/**
 * resolve_command_path - Finds the command in the PATH
 * @info: Shell information structure
 * @path_string: PATH environment variable
 * @command: Command to find
 * Return: Full path of the command or NULL
 */
char *resolve_command_path(shell_info_t *info, char *path_string, char *command)
{
    char *path;
    int i = 0, current_position = 0;

    if (is_direct_command(command) && is_executable(info, command))
        return command;

    while (path_string[i] != '\0')
    {
        if (path_string[i] == ':' || path_string[i + 1] == '\0')
        {
            path = duplicate_substring(path_string, current_position, i);
            if (is_executable(info, build_full_command_path(path, command)))
                return path;

            current_position = i + 1;
        }
        i++;
    }
    return NULL;
}
