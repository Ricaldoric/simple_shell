#include "shell.h"

/**
 * copy_string - Copies a string up to n characters
 * @dest: Destination string
 * @src: Source string
 * @n: Number of characters to copy
 * Return: Pointer to the destination string
 */
char *copy_string(char *dest, const char *src, int n)
{
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

/**
 * concatenate_strings - Concatenates two strings up to n bytes
 * @dest: First string
 * @src: Second string to append
 * @n: Maximum bytes to use from src
 * Return: Pointer to the concatenated string
 */
char *concatenate_strings(char *dest, const char *src, int n)
{
    int dest_len = 0, i = 0;
    while (dest[dest_len] != '\0')
        dest_len++;
    while (i < n && src[i] != '\0')
    {
        dest[dest_len++] = src[i++];
    }
    dest[dest_len] = '\0';
    return dest;
}

/**
 * find_char - Locates a character in a string
 * @s: String to search in
 * @c: Character to find
 * Return: Pointer to the first occurrence of c, or NULL if not found
 */
char *find_char(char *s, char c)
{
    while (*s != '\0')
    {
        if (*s == c)
            return s;
        s++;
    }
    return NULL;
}
