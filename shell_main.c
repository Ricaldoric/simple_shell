#include "shell.h"

/**
 * entry_point - Main entry point of the shell program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0 on success, non-zero on error
 */
int entry_point(int argc, char **argv)
{
    shell_info_t shell_info = { SHELL_INFO_INIT };
    int file_descriptor = DEFAULT_FD;

    file_descriptor = adjust_file_descriptor(file_descriptor);

    if (argc == 2)
        if (handle_argument_file(argv[1], &shell_info) != 0)
            return EXIT_FAILURE;

    initialize_environment(&shell_info);
    load_shell_history(&shell_info);
    run_shell(&shell_info, argv);
    return EXIT_SUCCESS;
}
