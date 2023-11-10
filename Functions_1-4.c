#include "shell.h"

/**
 * compstr - comparsion between two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compstr(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * dupstr - duplicates a given string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *dupstr(const char *s)
{
	int i = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	for (i++; i--;)
		ret[i] = *--s;
	return (ret);
}


/**
 **concat - concatenates two strings
 *@s1: the first string to concatenates
 *@s2: the second string to concatenates
 *@b: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *concat(char *s1, char *s2, int b)
{
	int i, j;
	char *c = s1;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0' && j < b)
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	if (j < b)
		s1[i] = '\0';
	return (c);
}

/**
 * **stringtoword - splits a string into words
 * @str: the input string to be split
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **stringtoword(char *str, char d)
{
	int i, j, k, m, n = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			n++;
	if (n == 0)
		return (NULL);
	c = malloc((1 + n) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
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
