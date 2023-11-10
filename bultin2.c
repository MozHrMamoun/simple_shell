#include "shell.h"

/**
 * unsetalias - sets alias to string
 * @info: parameter struct
 * @strg: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetalias(info_t *info, char *strg)
{
	char *poi, c;
	int ret;

	poi = findchar(strg, '=');
	if (!poi)
		return (1);
	c = *poi;
	*poi = 0;
	ret = deletenodeatindex(&(info->alias),
		getnodeindex(info->alias, nodestartswith(info->alias, strg, -1)));
	*poi = c;
	return (ret);
}

/**
 * printalias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printalias(list_t *node)
{
	char *poi = NULL, *a = NULL;

	if (node)
	{
		poi = findchar(node->str, '=');
		for (a = node->str; a <= poi; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(poi + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int mycd(info_t *info)
{
	char *s, *dire, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("not found!\n");
	if (!info->argv[1])
	{
		dire = getenvro(info, "HOME=");
		if (!dire)
			chdir_ret = chdir((dire = getenvro(info, "PWD=")) ? dire : "/");
		else
			chdir_ret = chdir(dire);
	}
	else if (compstr(info->argv[1], "-") == 0)
	{
		if (!getenvro(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(getenvro(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dire = getenvro(info, "OLDPWD=")) ? dire : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printerror(info, "can't cd to ");
		erroputs(info->argv[1]), erroputchar('\n');
	}
	else
	{
		setenvro(info, "OLDPWD", getenvro(info, "PWD="));
		setenvro(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
