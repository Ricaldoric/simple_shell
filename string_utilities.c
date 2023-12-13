#include "shell.h"

/**
 * calculate_string_length - Returns the length of a string
 * @str: String to calculate the length of
 * Return: Length of the string
 */
int calculate_string_length(char *str)
{
    int length = 0;

    while (str && *str++)
        length++;

    return length;
}

/**
 * compare_strings - Compares two strings lexicographically
 * @str1: First string
 * @str2: Second string
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if equal
 */
int compare_strings(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }

    return *str1 ? 1 : (*str2 ? -1 : 0);
}

/**
 * string_starts_with - Checks if a string starts with a given substring
 * @string: String to check
 * @substring: Substring to look for
 * Return: Pointer to the part of the string after the substring, or NULL
 */
char *string_starts_with(const char *string, const char *substring)
{
    while (*substring)
        if (*substring++ != *string++)
            return NULL;

    return (char *)string;
}

/**
 * concatenate_strings - Concatenates two strings
 * @destination: Destination buffer
 * @source: Source buffer
 * Return: Pointer to the destination buffer
 */
char *concatenate_strings(char *destination, char *source)
{
    char *dest_end = destination;

    while (*dest_end)
        dest_end++;
    while ((*dest_end++ = *source++))
        ;

    return destination;
}
