#include "shell.h"

/**
 * list_length - Counts the number of nodes in the linked list
 * @head: Pointer to the head of the list
 * Return: Number of nodes in the list
 */
size_t list_length(const list_t *head)
{
    const list_t *current = head;
    size_t count = 0;

    while (current)
    {
        current = current->next;
        count++;
    }
    return count;
}

/**
 * list_to_string_array - Converts a linked list to an array of strings
 * @head: Pointer to the head of the list
 * Return: Array of strings
 */
char **list_to_string_array(list_t *head)
{
    size_t length = list_length(head), i;
    char **strings;
    list_t *current = head;

    if (!head || length == 0)
        return NULL;

    strings = malloc(sizeof(char *) * (length + 1));
    if (!strings)
        return NULL;

    for (i = 0; current; current = current->next, i++)
    {
        strings[i] = duplicate_string(current->str);
        if (!strings[i])
            return free_string_array(strings, i);
    }
    strings[length] = NULL;

    return strings;
}

/**
 * print_linked_list - Prints the contents of a linked list
 * @head: Pointer to the head of the list
 * Return: Number of nodes in the list
 */
size_t print_linked_list(const list_t *head)
{
    const list_t *current = head;
    size_t count = 0;

    while (current)
    {
        print_number(current->num);
        print_string(": ");
        print_string(current->str ? current->str : "(nil)");
        print_string("\n");
        current = current->next;
        count++;
    }
    return count;
}

/**
 * find_node_by_prefix - Finds a node that starts with a specific prefix
 * @head: Pointer to the head of the list
 * @prefix: Prefix to search for
 * @c: Additional character criterion for matching
 * Return: Pointer to the node or NULL if not found
 */
list_t *find_node_by_prefix(list_t *head, char *prefix, char c)
{
    list_t *current = head;

    while (current)
    {
        if (does_string_start_with(current->str, prefix, c))
            return current;
        current = current->next;
    }
    return NULL;
}

/**
 * get_index_of_node - Gets the index of a node in the linked list
 * @head: Pointer to the head of the list
 * @node: Node to find the index of
 * Return: Index of the node or -1 if not found
 */
ssize_t get_index_of_node(list_t *head, list_t *node)
{
    list_t *current = head;
    size_t index = 0;

    while (current)
    {
        if (current == node)
            return index;
        current = current->next;
        index++;
    }
    return -1;
}
