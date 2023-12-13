#include "shell.h"

/**
 * print_string_err - Prints a string to stderr
 * @str: String to be printed
 * Return: Nothing
 */
void print_string_err(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        putchar_err(str[i]);
        i++;
    }
}

/**
 * putchar_err - Writes a character to stderr
 * @c: Character to print
 * Return: 1 on success, -1 on error with errno set
 */
int putchar_err(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * putchar_fd - Writes a character to specified file descriptor
 * @c: Character to print
 * @fd: File descriptor to write to
 * Return: 1 on success, -1 on error with errno set
 */
int putchar_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * print_string_fd - Prints a string to a given file descriptor
 * @str: String to be printed
 * @fd: File descriptor to write to
 * Return: Number of characters printed
 */
int print_string_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += putchar_fd(*str++, fd);
    }
    return (i);
}
