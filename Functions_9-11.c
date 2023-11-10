#include "shell.h"

/**
 * beginwith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *beginwith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 *_puts - prints an input string
 *@strn: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strn)
{
	int i = 0;

	if (!strn)
		return;
	while (strn[i] != '\0')
	{
		_putchar(strn[i]);
		i++;
	}
}

/**
 **findchar - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *findchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
