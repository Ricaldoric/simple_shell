#include "main.h"

/**
 * _strdup - Duplicates a string in heap memory
 * @s: Pointer to the string to be duplicated
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *s)
{
    char *new;
    size_t len;

    len = _strlen(s);
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return (NULL);
    /* Copy the source string into the new memory space */
    _memcpy(new, s, len + 1);
    return (new);
}

/**
 * _strlen - Returns the length of a string
 * @s: Pointer to the string
 * Return: Length of the string
 */
int _strlen(const char *s)
{
    int len;

    /* Counting characters in the string until the null terminator */
    for (len = 0; s[len] != 0; len++)
        ;
    return (len);
}

/**
 * cmp_chars - Compares characters of two strings
 * @str: Input string
 * @delim: Delimiter characters
 * Return: 1 if equal, 0 if not
 */
int cmp_chars(char str[], const char *delim)
{
    unsigned int i, j, k;

    /* Comparing each character in the string to the delimiters */
    for (i = 0, k = 0; str[i]; i++)
    {
        for (j = 0; delim[j]; j++)
        {
            if (str[i] == delim[j])
            {
                k++; /* Counting matching characters */
                break;
            }
        }
    }
    /* Return 1 if all characters match the delimiters */
    if (i == k)
        return (1);
    return (0);
}

/**
 * _strtok - Splits a string by a delimiter
 * @str: Input string
 * @delim: Delimiter characters
 * Return: Pointer to the next token or NULL
 */
char *_strtok(char str[], const char *delim)
{
    static char *splitted, *str_end;
    char *str_start;
    unsigned int i, bool;

    if (str != NULL)
    {
        /* Avoid processing if string is only delimiters */
        if (cmp_chars(str, delim))
            return (NULL);
        splitted = str; /* Assign start of string */
        i = _strlen(str);
        str_end = &str[i]; /* Mark end of the string */
    }
    str_start = splitted;
    if (str_start == str_end) /* End of string reached */
        return (NULL);

    for (bool = 0; *splitted; splitted++)
    {
        /* Find next non-delimiter character */
        if (splitted != str_start)
            if (*splitted && *(splitted - 1) == '\0')
                break;
        /* Replace delimiters with null characters */
        for (i = 0; delim[i]; i++)
        {
            if (*splitted == delim[i])
            {
                *splitted = '\0';
                if (splitted == str_start)
                    str_start++;
                break;
            }
        }
        /* Check if there's a valid token */
        if (bool == 0 && *splitted)
            bool = 1;
    }
    /* Return NULL if only delimiters were found */
    if (bool == 0)
        return (NULL);
    return (str_start);
}

/**
 * _isdigit - Checks if a string represents a number
 * @s: Input string
 * Return: 1 if string is a number, 0 otherwise
 */
int _isdigit(const char *s)
{
    unsigned int i;

    /* Iterate through the string to check for non-digit characters */
    for (i = 0; s[i]; i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
    }
    return (1);
}

/**
 * This code was authored by Moffat and Sisinio.
 */
