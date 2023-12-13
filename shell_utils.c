#include "shell.h"

/**
 * parse_string_to_int - Converts a string to an integer, with error checking
 * @str: The string to convert
 * Return: Integer value or -1 on error
 */
int parse_string_to_int(char *str)
{
    unsigned long int number = 0;
    int digit;

    if (*str == '+')
        str++;
    while (*str)
    {
        digit = *str - '0';
        if (digit >= 0 && digit <= 9)
        {
            number = number * 10 + digit;
            if (number > INT_MAX)
                return (-1);
        }
        else
            return (-1);
        str++;
    }
    return (number);
}

/**
 * display_error_msg - Outputs an error message
 * @info: Shell information structure
 * @error_message: Error message string
 */
void display_error_msg(info_t *info, char *error_message)
{
    _eputs(info->fname);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(error_message);
    output_int(info->line_count, STDERR_FILENO);
}

/**
 * output_int - Outputs an integer to a specified file descriptor
 * @number: Number to print
 * @fd: File descriptor
 * Return: Number of characters printed
 */
int output_int(int number, int fd)
{
    int count = 0;
    if (number < 0)
    {
        _putchar_fd('-', fd);
        number = -number;
        count++;
    }
    count += print_number_recursive(number, fd);
    return count;
}

int print_number_recursive(int number, int fd)
{
    int count = 0;
    if (number / 10)
        count += print_number_recursive(number / 10, fd);
    _putchar_fd((number % 10) + '0', fd);
    return count + 1;
}

/**
 * itoa_custom - Custom implementation of itoa function
 * @num: Number to convert
 * @base: Conversion base
 * @flags: Format flags
 * Return: Pointer to the string representation of number
 */
char *itoa_custom(long int num, int base, int flags)
{
    static char repr[50];
    char *ptr = repr + sizeof(repr) - 1;
    unsigned long n = num < 0 && !(flags & CONVERT_UNSIGNED) ? -num : num;
    const char *digits = flags & CONVERT_LOWERCASE ? 
                         "0123456789abcdef" : "0123456789ABCDEF";

    *ptr = '\0';
    do {
        *--ptr = digits[n % base];
        n /= base;
    } while (n);
    if (num < 0 && !(flags & CONVERT_UNSIGNED))
        *--ptr = '-';
    return ptr;
}

/**
 * clear_line_comments - Clears comments from a line of input
 * @line: Line to process
 */
void clear_line_comments(char *line)
{
    while (*line && *line != '#')
        line++;
    if (*line == '#')
        *line = '\0';
}
