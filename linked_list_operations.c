#include "shell.h"

/**
 * prepend_node - Prepends a node to the start of the linked list
 * @head: Pointer to the head of the list
 * @str: String to store in the node
 * @num: Node index, typically used in history lists
 * Return: Pointer to the new node
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
    list_t *new_node;

    if (!head)
        return NULL;

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    clear_memory(new_node, sizeof(list_t));
    new_node->num = num;
    new_node->str = str ? duplicate_string(str) : NULL;
    new_node->next = *head;
    *head = new_node;

    return new_node;
}

/**
 * append_node - Appends a node to the end of the linked list
 * @head: Pointer to the head of the list
 * @str: String to store in the node
 * @num: Node index, typically used in history lists
 * Return: Pointer to the new node
 */
list_t *append_node(list_t **head, const char *str, int num)
{
    list_t *new_node, *tail;

    if (!head)
        return NULL;

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    clear_memory(new_node, sizeof(list_t));
    new_node->num = num;
    new_node->str = str ? duplicate_string(str) : NULL;

    if (*head)
    {
        tail = find_list_tail(*head);
        tail->next = new_node;
    }
    else
    {
        *head = new_node;
    }

    return new_node;
}

/**
 * print_string_list - Prints strings from a linked list
 * @head: Pointer to the head of the list
 * Return: Number of nodes in the list
 */
size_t print_string_list(const list_t *head)
{
    const list_t *current = head;
    size_t count = 0;

    while (current)
    {
        print_string(current->str ? current->str : "(nil)");
        current = current->next;
        count++;
    }

    return count;
}

/**
 * remove_node_by_index - Removes a node by its index in the list
 * @head: Pointer to the head of the list
 * @index: Index of the node to remove
 * Return: 1 on success, 0 on failure
 */
int remove_node_by_index(list_t **head, unsigned int index)
{
    list_t *current, *to_delete;
    unsigned int current_index = 0;

    if (!head || !*head)
        return 0;

    if (index == 0)
        return remove_head_node(head);

    current = *head;
    while (current->next && current_index < index - 1)
    {
        current = current->next;
        current_index++;
    }

    if (current->next && current_index == index - 1)
    {
        to_delete = current->next;
        current->next = to_delete->next;
        free_node(to_delete);
        return 1;
    }

    return 0;
}

/**
 * free_linked_list - Frees all nodes in the linked list
 * @head: Pointer to the head of the list
 */
void free_linked_list(list_t **head)
{
    list_t *current, *next;

    if (!head || !*head)
        return;

    current = *head;
    while (current)
    {
        next = current->next;
        free_node(current);
        current = next;
    }
    *head = NULL;
}
