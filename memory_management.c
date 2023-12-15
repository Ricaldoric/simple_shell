#include "main.h"

/**
 * _memcpy - Copies bytes between two memory areas
 * @newptr: Destination pointer for the copy
 * @ptr: Source pointer from which to copy
 * @size: Number of bytes to copy
 * Return: No return (void function)
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
    char *char_ptr = (char *)ptr;
    char *char_newptr = (char *)newptr;
    unsigned int i;

    for (i = 0; i < size; i++)
        char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - Reallocates a memory block
 * @ptr: Pointer to the memory previously allocated
 * @old_size: Size in bytes of the allocated space for ptr
 * @new_size: Size in bytes for the new memory block
 * Return: Pointer to the newly allocated memory
 * If new_size == old_size, returns ptr without changes
 * If malloc fails, returns NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *newptr;

    if (ptr == NULL)
        return (malloc(new_size));

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(new_size);
    if (newptr == NULL)
        return (NULL);

    if (new_size < old_size)
        _memcpy(newptr, ptr, new_size);
    else
        _memcpy(newptr, ptr, old_size);

    free(ptr);
    return (newptr);
}

/**
 * _reallocdp - Reallocates a double pointer memory block
 * @ptr: Double pointer to the memory previously allocated
 * @old_size: Size in bytes of the allocated space for ptr
 * @new_size: Size in bytes for the new memory block
 * Return: Pointer to the newly allocated memory
 * If new_size == old_size, returns ptr without changes
 * If malloc fails, returns NULL
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int i;

    if (ptr == NULL)
        return (malloc(sizeof(char *) * new_size));

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
        return (NULL);

    for (i = 0; i < old_size; i++)
        newptr[i] = ptr[i];

    free(ptr);

    return (newptr);
}

/**
 * This code was authored by Moffat and Sisinio.
 */
