#include "shell.h"

char *copy_string(char *dest, char *src)
{
    char *ret = dest;
    while ((*dest++ = *src++))
        ;
    return ret;
}

char *duplicate_string(const char *str)
{
    int len = calculate_string_length((char *)str);
    char *dup = malloc(len + 1);
    if (!dup)
        return NULL;
    copy_string(dup, (char *)str);
    return dup;
}

void print_string(char *str)
{
    while (*str)
        print_char(*str++);
}

int print_char(char c)
{
    static char buffer[WRITE_BUF_SIZE];
    static int index = 0;

    if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(STDOUT_FILENO, buffer, index);
        index = 0;
    }
    if (c != BUF_FLUSH)
        buffer[index++] = c;
    return 1;
}
