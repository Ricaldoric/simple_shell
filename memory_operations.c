#include "shell.h"

/**
 * set_memory - Fills memory with a constant byte
 * @ptr: Pointer to the memory area
 * @value: Byte value to fill with
 * @size: Number of bytes to fill
 * Return: Pointer to the memory area
 */
void *set_memory(void *ptr, char value, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
        ((char *)ptr)[i] = value;
    return ptr;
}

/**
 * free_string_array - Frees an array of strings
 * @array: Array of strings to free
 */
void free_string_array(char **array)
{
    if (!array)
        return;

    for (char **current = array; *current; current++)
        free(*current);

    free(array);
}

/**
 * reallocate_memory - Reallocates a memory block
 * @memory: Pointer to the existing memory block
 * @old_size: Size of the existing block
 * @new_size: Size of the new block
 * Return: Pointer to the new memory block
 */
void *reallocate_memory(void *memory, unsigned int old_size, unsigned int new_size)
{
    void *new_memory;

    if (new_size == 0)
    {
        free(memory);
        return NULL;
    }

    new_memory = malloc(new_size);
    if (!new_memory)
        return NULL;

    if (memory)
    {
        copy_memory(new_memory, memory, old_size < new_size ? old_size : new_size);
        free(memory);
    }

    return new_memory;
}
