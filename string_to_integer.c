#include "shell.h"

/**
 * check_interactive_mode - Determines if shell operates in interactive mode
 * @info: pointer to the structure containing shell information
 *
 * Return: 1 if in interactive mode, 0 if not
 */
int check_interactive_mode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * char_is_delimiter - Verifies if a given character is a delimiter
 * @ch: the character to be checked
 * @delimiter: string containing delimiter characters
 * Return: 1 if ch is a delimiter, 0 otherwise
 */
int char_is_delimiter(char ch, char *delimiter)
{
    while (*delimiter)
        if (*delimiter++ == ch)
            return (1);
    return (0);
}

/**
 * is_alpha - Validates if a character is an alphabet letter
 * @ch: character to be checked
 * Return: 1 if ch is a letter, 0 if not
 */
int is_alpha(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * string_to_integer - Converts a string to an integer
 * @str: the string to convert to an integer
 * Return: the integer representation of str, or 0 if str has no digits
 */
int string_to_integer(char *str)
{
    int index, negative = 1, digit_found = 0, converted;
    unsigned int num = 0;

    for (index = 0; str[index] != '\0' && digit_found != 2; index++)
    {
        if (str[index] == '-')
            negative *= -1;

        if (str[index] >= '0' && str[index] <= '9')
        {
            digit_found = 1;
            num *= 10;
            num += (str[index] - '0');
        }
        else if (digit_found == 1)
            digit_found = 2;
    }

    if (negative == -1)
        converted = -num;
    else
        converted = num;

    return (converted);
}
