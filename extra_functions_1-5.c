#include "shell.h"

/**
 * strtoint - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int strtoint(char *s)
{
	int i = 0;
	unsigned long int convert = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			convert *= 10;
			convert += (s[i] - '0');
			if (convert > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (convert);
}

/**
 * isdelim - checks if character is a delimeter or not
 * @c: the char to check
 * @delm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delm)
{
	while (*delm)
		if (*delm++ == c)
			return (1);
	return (0);
}

/**
 * print_deci - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @f: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_deci(int input, int f)
{
	int (*__putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int _abs_, curr;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			c++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	c++;

	return (c);
}

/**
 *stoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int stoi(char *s)
{
	int i, sign = 1, flag = 0, result;
	unsigned int convert = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			convert *= 10;
			convert += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -convert;
	else
		result = convert;

	return (result);
}

/**
 * rmcomments - function replaces first instance of '#' with '\0'
 * @add: address of the string to modify
 *
 * Return: Always 0;
 */
void rmcomments(char *add)
{
	int i;

	for (i = 0; add[i] != '\0'; i++)
		if (add[i] == '#' && (!i || add[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
