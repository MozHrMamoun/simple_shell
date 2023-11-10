#include "shell.h"

/**
 * myenvro - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int myenvro(info_t *info)
{
	printliststr(info->env);
	return (0);
}

/**
 * rmenvro - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @c: the string env c property
 */
int rmenvro(info_t *info, char *c)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !c)
		return (0);

	while (node)
	{
		p = beginwith(node->str, c);
		if (p && *p == '=')
		{
			info->env_changed = deletenodeatindex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * mysetenvro - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int mysetenvro(info_t *info)
{
	if (info->argc != 3)
	{
		erroputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setenvro(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * makeenvlist - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int makeenvlist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addnodeatend(&node, environ[i], 0);
	info->env = node;
	return (0);
}
