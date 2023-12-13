#include "shell.h"

/**
 * duplicate_string - Duplicates a string
 * @str: String to duplicate
 * Return: Pointer to the duplicated string
 */
char *duplicate_string(const char *str)
{
    int length;
    char *duplicate;

    if (!str)
        return NULL;

    for (length = 0; str[length]; length++)
        ;
    duplicate = malloc(sizeof(char) * (length + 1));
    
    if (!duplicate)
        return NULL;

    for (int i = 0; i <= length; i++)
        duplicate[i] = str[i];

    return duplicate;
}

/**
 * print_string - Prints a string
 * @str: String to print
 * Return: void
 */
void print_string(char *str)
{
    if (!str)
        return;

    while (*str)
        putchar(*str++);
}

/**
 * print_character - Writes a character to stdout
 * @c: Character to print
 * Return: 1 on success, -1 on error
 */
int print_character(char c)
{
    static int buffer_index = 0;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(1, buffer, buffer_index);
        buffer_index = 0;
    }

    if (c != BUF_FLUSH)
        buffer[buffer_index++] = c;

    return 1;
}

/**
 * find_command_path - Resolves the path of a command
 * @shell_info: Shell information structure
 * @cmd: Command to find
 * Return: Full path of the command or NULL
 */
char *find_command_path(shell_info_t *shell_info, char *cmd)
{
    char *pathstr = get_environment_variable(shell_info, "PATH");
    char *path;
    int i = 0;

    if (is_direct_path(cmd) && is_executable(cmd))
        return duplicate_string(cmd);

    while (pathstr && pathstr[i])
    {
        path = extract_path(pathstr, &i, cmd);
        if (is_executable(path))
            return path;
    }
    return NULL;
}
