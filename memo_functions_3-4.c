#include "shell.h"

/**
 * strfree - frees a string of strings from the memory
 * @ss: string of strings
 */
void strfree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * panfree - frees a pointer and NULLs the address from the memory
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int panfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
