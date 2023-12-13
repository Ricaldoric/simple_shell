#include "shell.h"

/**
 * buffer_commands - Manages buffering of shell commands
 * @info: Shell info structure
 * @buffer: Pointer to the command buffer
 * @length: Pointer to buffer length
 * Return: Number of bytes read or -1 on error
 */
ssize_t buffer_commands(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytes_read = 0;
    size_t buffer_size = 0;

    if (*length == 0) // Check if buffer needs to be refilled
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, signal_handler);

        bytes_read = fetch_line(info, buffer, &buffer_size);
        if (bytes_read > 0)
        {
            trim_newline(buffer, &bytes_read);
            info->line_count++;
            discard_comments(*buffer);
            build_history(info, *buffer, ++info->history_count);
            *length = bytes_read;
            info->cmd_buffer = buffer;
        }
    }
    return bytes_read;
}

/**
 * process_input - Processes input from the user
 * @info: Shell info structure
 * Return: Length of processed command or -1 on EOF
 */
ssize_t process_input(info_t *info)
{
    static char *cmd_buffer;
    static size_t buf_pos = 0, buf_len = 0;
    ssize_t bytes_read = 0;
    char *current_cmd;

    flush_output();
    bytes_read = buffer_commands(info, &cmd_buffer, &buf_len);

    if (bytes_read == -1 || (bytes_read == 0 && buf_len == 0))
        return -1;

    if (buf_len > 0)
    {
        current_cmd = parse_command(cmd_buffer, &buf_pos, buf_len);
        if (buf_pos >= buf_len)
            reset_buffer(&cmd_buffer, &buf_pos, &buf_len);

        info->arg = current_cmd;
        return strlen(current_cmd);
    }

    info->arg = cmd_buffer;
    return bytes_read;
}

/**
 * fetch_line - Retrieves a line of input
 * @info: Shell info structure
 * @buffer: Pointer to buffer to store input
 * @buf_size: Size of the buffer
 * Return: Length of line read or -1 on EOF
 */
ssize_t fetch_line(info_t *info, char **buffer, size_t *buf_size)
{
    static char internal_buffer[READ_BUF_SIZE];
    static size_t internal_pos = 0, internal_len = 0;
    ssize_t bytes_read;

    if (internal_pos == internal_len)
        internal_pos = internal_len = 0;

    bytes_read = read_input(info, internal_buffer, &internal_len);
    if (bytes_read <= 0)
        return -1;

    *buffer = realloc_buffer(*buffer, internal_buffer + internal_pos, buf_size, bytes_read);
    internal_pos += bytes_read;
    return bytes_read;
}

/**
 * signal_handler - Handles interrupt signals
 * @signal_num: Signal number
 */
void signal_handler(int signal_num)
{
    _puts("\n");
    prompt();
    flush_output();
}
