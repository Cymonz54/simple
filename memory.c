#include "shell.h"

/**
 * bfree - Frees the pointer and NULLs the address
 * @ptr: It addresses the pointer tthat it frees
 *
 * Return: 1 if 1 if the block was successfully freed,
 * otherwise 0. freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
