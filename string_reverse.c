#include "main.h"

/**
 * rev_string - Reverses a string
 * @s: Input string to be reversed
 * Return: No return (void function)
 */
void rev_string(char *s)
{
    int count = 0, i, j;
    char *str, temp;

    /* Determine the length of the string */
    while (count >= 0)
    {
        if (s[count] == '\0')
            break;
        count++;
    }
    str = s;

    /* Swap characters to reverse the string */
    for (i = 0; i < (count - 1); i++)
    {
        for (j = i + 1; j > 0; j--)
        {
            temp = *(str + j);
            *(str + j) = *(str + (j - 1));
            *(str + (j - 1)) = temp;
        }
    }
}

/**
 * This code was authored by Moffat and Sisinio.
 */
