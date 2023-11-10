#include "shell.h"

/**
 * sigintHandl - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandl(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * readbuff - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @i: size
 *
 * Return: c
 */
ssize_t readbuff(info_t *info, char *buff, size_t *i)
{
	ssize_t c = 0;

	if (*i)
		return (0);
	c = read(info->readfd, buff, READ_BUF_SIZE);
	if (c >= 0)
		*i = c;
	return (c);
}

/**
 * inputbuff - buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @leng: address of len var
 *
 * Return: bytes read
 */
ssize_t inputbuff(info_t *info, char **buff, size_t *leng)
{
	ssize_t c = 0;
	size_t len_p = 0;

	if (!*leng)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		c = getline(buff, &len_p, stdin);
#else
		c = getnextline(info, buff, &len_p);
#endif
		if (c > 0)
		{
			if ((*buff)[c - 1] == '\n')
			{
				(*buff)[c - 1] = '\0';
				c--;
			}
			info->linecount_flag = 1;
			rmcomments(*buff);
			addhistorylist(info, *buff, info->histcount++);
			{
				*leng = c;
				info->cmd_buf = buff;
			}
		}
	}
	return (c);
}

/**
 * getnextline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int getnextline(info_t *info, char **ptr, size_t *leng)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && leng)
		s = *leng;
	if (i == len)
		i = len = 0;

	r = readbuff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = findchar(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = realloct(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		compstr(new_p, buff + i, k - i);
	else
		copystr(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (leng)
		*leng = s;
	*ptr = p;
	return (s);
}

/**
 * getinput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getinput(info_t *info)
{
	static char *buff;
	static size_t i, j, leng;
	ssize_t c = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	c = inputbuff(info, &buff, &leng);
	if (c == -1)
		return (-1);
	if (leng)
	{
		j = i;
		p = buff + i;

		checkchain(info, buff, &j, i, leng);
		while (j < leng)
		{
			if (ischain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= leng)
		{
			i = leng = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (lenstr(p));
	}

	*buf_p = buff;
	return (c);
}
