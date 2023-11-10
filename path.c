#include "shell.h"

/**
 * iscmd - determines if a file is an executable command
 * @info: the info struct
 * @pat: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int iscmd(info_t *info, char *pat)
{
	struct stat st;

	(void)info;
	if (!pat || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * findpath - finds this cmd in the PATH string
 * @info: the info struct
 * @patstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findpath(info_t *info, char *patstr, char *cmd)
{
	int i = 0, currnt_pos = 0;
	char *pat;

	if (!patstr)
		return (NULL);
	if ((lenstr(cmd) > 2) && beginwith(cmd, "./"))
	{
		if (iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!patstr[i] || patstr[i] == ':')
		{
			path = duplichars(patstr, currnt_pos, i);
			if (!*pat)
				catstr(pat, cmd);
			else
			{
				catstr(pat, "/");
				catstr(pat, cmd);
			}
			if (iscmd(info, pat))
				return (pat);
			if (!patstr[i])
				break;
			currnt_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * duplichars - duplicates characters
 * @patstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplichars(char *patstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (patstr[i] != ':')
			buff[k++] = patstr[i];
	buff[k] = 0;
	return (buff);
}

