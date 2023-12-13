#include "shell.h"

int calculate_string_length(char *str)
{
    int length = 0;
    while (*str++)
        length++;
    return length;
}

int compare_strings(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    return (*str1 == *str2) ? 0 : (*str1 < *str2 ? -1 : 1);
}

char *check_string_prefix(const char *str, const char *prefix)
{
    while (*prefix)
        if (*prefix++ != *str++)
            return NULL;
    return (char *)str;
}

char *concatenate_strings(char *dest, char *src)
{
    char *ret = dest;
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return ret;
}
