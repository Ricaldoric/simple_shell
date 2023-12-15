#include "main.h"

/**
 * repeated_char - Counts continuous repetition of a character
 * @input: Pointer to the input string
 * @i: Current index in the input
 * Return: Number of repeated characters
 */
int repeated_char(char *input, int i)
{
    if (*(input - 1) == *input)
        return (repeated_char(input - 1, i + 1));
    return (i);
}

/**
 * error_sep_op - Identifies errors in command separators
 * @input: Input string to be checked
 * @i: Current position in the string
 * @last: The previous character read
 * Return: Position of the syntax error, 0 if none
 */
int error_sep_op(char *input, int i, char last)
{
    int count;
    count = 0;
    if (*input == '\0')
        return (0);
    if (*input == ' ' || *input == '\t')
        return (error_sep_op(input + 1, i + 1, last));
    if (*input == ';' && (last == '|' || last == '&' || last == ';'))
        return (i);
    if ((*input == '|' && (last == ';' || last == '&')) ||
        (*input == '&' && (last == ';' || last == '|')))
        return (i);
    if ((*input == '|' && last == '|') || (*input == '&' && last == '&'))
    {
        count = repeated_char(input, 0);
        if (count == 0 || count > 1)
            return (i);
    }
    return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - Determines the position of the first non-whitespace character
 * @input: The command line input string
 * @i: Pointer to store the index of the first character
 * Return: -1 if an error is found, 0 otherwise
 */
int first_char(char *input, int *i)
{
    for (*i = 0; input[*i]; *i += 1)
    {
        if (input[*i] != ' ' && input[*i] != '\t')
        {
            if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
                return (-1);
            break;
        }
    }
    return (0);
}

/**
 * print_syntax_error - Displays syntax error messages
 * @datash: Struct containing shell data
 * @input: The command line input
 * @i: Index where the error was detected
 * @bool: Flag indicating the type of error
 * Return: None
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
    char *msg, *msg2, *msg3, *error, *counter;
    int length;

    msg = identify_error_message(input, i, bool);
    msg2 = ": Syntax error: \"";
    msg3 = "\" unexpected\n";
    counter = aux_itoa(datash->counter);
    length = _strlen(datash->av[0]) + _strlen(counter);
    length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(counter);
        return;
    }
    _strcpy(error, datash->av[0]);
    _strcat(error, ": ");
    _strcat(error, counter);
    _strcat(error, msg2);
    _strcat(error, msg);
    _strcat(error, msg3);
    _strcat(error, "\0");
    write(STDERR_FILENO, error, length);
    free(error);
    free(counter);
}

/**
 * check_syntax_error - Checks and prints syntax errors in input
 * @datash: Data structure containing shell information
 * @input: The command line input string
 * Return: 1 if an error is detected, 0 otherwise
 */
int check_syntax_error(data_shell *datash, char *input)
{
    int begin = 0;
    int f_char = 0;
    int i = 0;

    f_char = first_char(input, &begin);
    if (f_char == -1)
    {
        print_syntax_error(datash, input, begin, 0);
        return (1);
    }

    i = error_sep_op(input + begin, 0, *(input + begin));
    if (i != 0)
    {
        print_syntax_error(datash, input, begin + i, 1);
        return (1);
    }
    return (0);
}
