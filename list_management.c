#include "main.h"

/**
 * add_sep_node_end - Adds a separator node at the end of a list
 * @head: Head of the sep_list linked list
 * @sep: Separator character (e.g., ';' or '|')
 * Return: Address of the head of the linked list
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
    sep_list *new, *temp;

    new = malloc(sizeof(sep_list));
    if (new == NULL)
        return (NULL);

    new->separator = sep;
    new->next = NULL;
    temp = *head;

    if (temp == NULL)
    {
        *head = new;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }

    return (*head);
}

/**
 * free_sep_list - Frees a sep_list linked list
 * @head: Head of the linked list
 * Return: No return (void function)
 */
void free_sep_list(sep_list **head)
{
    sep_list *temp;
    sep_list *curr;

    if (head != NULL)
    {
        curr = *head;
        while ((temp = curr) != NULL)
        {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}

/**
 * add_line_node_end - Adds a command line node at the end of a list
 * @head: Head of the line_list linked list
 * @line: Command line string
 * Return: Address of the head of the linked list
 */
line_list *add_line_node_end(line_list **head, char *line)
{
    line_list *new, *temp;

    new = malloc(sizeof(line_list));
    if (new == NULL)
        return (NULL);

    new->line = line;
    new->next = NULL;
    temp = *head;

    if (temp == NULL)
    {
        *head = new;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }

    return (*head);
}

/**
 * free_line_list - Frees a line_list linked list
 * @head: Head of the linked list
 * Return: No return (void function)
 */
void free_line_list(line_list **head)
{
    line_list *temp;
    line_list *curr;

    if (head != NULL)
    {
        curr = *head;
        while ((temp = curr) != NULL)
        {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}

/**
 * This code was authored by Moffat and Sisinio.
 */
