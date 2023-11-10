#include "shell.h"

/**
 * clearinfo - initializes info_t struct
 * @info: struct address
 */
void clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setinfo - prepare info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtoword(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = (info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replacealias(info);
		replacevars(info);
	}
}

/**
 * freeinfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeinfo(info_t *info, int all)
{
	strfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			listfree(&(info->env));
		if (info->history)
			listfree(&(info->history));
		if (info->alias)
			listfree(&(info->alias));
		strfree(info->environ);
			info->environ = NULL;
		panfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
