#include "main.h"

/**
 * add_rvar_node - Adds a variable node at the end of a r_var list
 * @head: Head of the r_var linked list
 * @lvar: Length of the variable name
 * @val: Value of the variable
 * @lval: Length of the value
 * Return: Address of the head of the linked list
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
    r_var *new, *temp;

    new = malloc(sizeof(r_var));
    if (new == NULL)
        return (NULL);

    new->len_var = lvar;
    new->val = val;
    new->len_val = lval;
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
 * free_rvar_list - Frees a r_var linked list
 * @head: Head of the linked list
 * Return: No return (void function)
 */
void free_rvar_list(r_var **head)
{
    r_var *temp;
    r_var *curr;

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
