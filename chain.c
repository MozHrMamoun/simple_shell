#include "shell.h"

/**
 * replacestring - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacestring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replacealias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacealias(info_t *info)
{
	int i;
	list_t *node;
	char *poi;

	for (i = 0; i < 10; i++)
	{
		node = nodestartswith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		poi = findchar(node->str, '=');
		if (!poi)
			return (0);
		poi = dupstr(poi + 1);
		if (!poi)
			return (0);
		info->argv[0] = poi;
	}
	return (1);
}

/**
 * checkchain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buff
 * @i: starting position in buff
 * @leng: length of buff
 *
 * Return: Void
 */
void checkchain(info_t *info, char *buff, size_t *p, size_t i, size_t leng)
{
	size_t j = *poi;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = leng;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			j = leng;
		}
	}

	*poi = j;
}

/**
 * replacevars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacevars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compstr(info->argv[i], "$?"))
		{
			replacestring(&(info->argv[i]),
				dupstr(convenumber(info->status, 10, 0)));
			continue;
		}
		if (!compstr(info->argv[i], "$$"))
		{
			dupstr(&(info->argv[i]),
				_strdup(convenumber(getpid(), 10, 0)));
			continue;
		}
		node = nodestartswith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replacestring(&(info->argv[i]),
				dupstr(findchar(node->str, '=') + 1));
			continue;
		}
		replacestring(&info->argv[i], dupstr(""));

	}
	return (0);
}

/**
 * ischain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ischain(info_t *info, char *buff, size_t *p)
{
	size_t j = *poi;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*poi = j;
	return (1);
}
