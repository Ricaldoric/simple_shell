#include "main.h"

/**
 * _strcat - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *_strcat(char *dest, const char *src)
{
    int i;
    int j;

    for (i = 0; dest[i] != '\0'; i++)
        ;

    for (j = 0; src[j] != '\0'; j++)
    {
        dest[i] = src[j];
        i++;
    }

    dest[i] = '\0';
    return (dest);
}

/**
 * _strcpy - Copies a string to another
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
    size_t a;

    for (a = 0; src[a] != '\0'; a++)
    {
        dest[a] = src[a];
    }
    dest[a] = '\0';

    return (dest);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if strings are equal, otherwise non-zero
 */
int _strcmp(char *s1, char *s2)
{
    int i;

    for (i = 0; s1[i] == s2[i] && s1[i]; i++)
        ;

    if (s1[i] > s2[i])
        return (1);
    if (s1[i] < s2[i])
        return (-1);
    return (0);
}

/**
 * _strchr - Locates a character in a string
 * @s: String to be searched
 * @c: Character to locate
 * Return: Pointer to the first occurrence of c
 */
char *_strchr(char *s, char c)
{
    unsigned int i = 0;

    for (; *(s + i) != '\0'; i++)
        if (*(s + i) == c)
            return (s + i);
    if (*(s + i) == c)
        return (s + i);
    return ('\0');
}

/**
 * _strspn - Gets the length of a prefix substring
 * @s: String to be scanned
 * @accept: String containing characters to match
 * Return: Number of characters in the initial segment
 *         of s which consist only of characters from accept
 */
int _strspn(char *s, char *accept)
{
    int i, j, bool;

    for (i = 0; *(s + i) != '\0'; i++)
    {
        bool = 1;
        for (j = 0; *(accept + j) != '\0'; j++)
        {
            if (*(s + i) == *(accept + j))
            {
                bool = 0;
                break;
            }
        }
        if (bool == 1)
            break;
    }
    return (i);
}

/**
 * This code was authored by Moffat and Sisinio.
 */
