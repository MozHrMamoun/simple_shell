#include "shell.h"

/**
 * writehistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writehistory(info_t *info)
{
	ssize_t f;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (f == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		prinput(node->str, f);
		prif('\n', f);
	}
	prif(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * addhistorylist - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int addhistorylist(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	addnodeatend(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * gethistoryfile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *gethistoryfile(info_t *info)
{
	char *buff, *dire;

	dir = getenvro(info, "HOME=");
	if (!dire)
		return (NULL);
	buff = malloc(sizeof(char) * (lenstr(dire) + lenstr(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	copystr(buff, dire);
	catstr(buff, "/");
	catstr(buff, HIST_FILE);
	return (buff);
}

/**
 * readhistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readhistory(info_t *info)
{
	int i, last = 0, c = 0;
	ssize_t f, readlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethistoryfile(info);

	if (!filename)
		return (0);

	f = open(filename, O_RDONLY);
	free(filename);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	readlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(f);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			addhistorylist(info, buf + last, c++);
			last = i + 1;
		}
	if (last != i)
		addhistorylist(info, buf + last, c++);
	free(buf);
	info->histcount = c;
	while (info->histcount-- >= HIST_MAX)
		deletenodeatindex(&(info->history), 0);
	renumberhistory(info);
	return (info->histcount);
}

/**
 * renumberhistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberhistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
