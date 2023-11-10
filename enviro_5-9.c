#include "shell.h"

/**
 * getenvirocopy - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getenvirocopy(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listtostrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * getenvro - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *getenvro(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = beginwith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setenvro - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int setenvro(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *poi;

	if (!var || !value)
		return (0);

	buff = malloc(lenstr(var) + lenstr(value) + 2);
	if (!buff)
		return (1);
	copystr(buff, var);
	catstr(buff, "=");
	catstr(buff, value);
	node = info->env;
	while (node)
	{
		poi = beginwith(node->str, var);
		if (poi && *poi == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addnodeatend(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

/**
 * unsetenvro - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetenvro(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		erroputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		rmenvro(info, info->argv[i]);

	return (0);
}
