#include "shell.h"

/**
 * lenstr - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int lenstr(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * copystr - copies a string
 * @dest: the destination string
 * @src: the source string
 *
 * Return: pointer to destination
 */
char *copystr(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 **cpystr - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@c: the amount of characters to be copied
 *Return: the concatenated string
 */
char *cpystr(char *dest, char *src, int c)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < c - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < c)
	{
		j = i;
		while (j < c)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * **strtoword - splits a string into words. Repeat delimiters are ignored
 * @str: the input string to be split
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtoword(char *str, char *d)
{
	int i, j, k, m, n = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			n++;

	if (n == 0)
		return (NULL);
	c = malloc((1 + n) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = str[i++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}
