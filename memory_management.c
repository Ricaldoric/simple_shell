#include "shell.h"

/**
 * free_pointer - Frees a pointer and sets it to NULL
 * @ptr: Double pointer to the memory to be freed
 * Return: 1 if freed, 0 otherwise
 */
int free_pointer(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
