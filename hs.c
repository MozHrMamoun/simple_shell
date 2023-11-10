#include "shell.h"

/**
 * hs - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hs(info_t *info, char **av)
{
	ssize_t c = 0;
	int builtin_ret = 0;

	while (c != -1 && builtin_ret != -2)
	{
		clearinfo(info);
		if (isinteractive(info))
			_puts("$ ");
		erroputchar(BUF_FLUSH);
		c = getinput(info);
		if (c != -1)
		{
			setinfo(info, av);
			builtin_ret = findbuilt(info);
			if (builtin_ret == -1)
				findcmd(info);
		}
		else if (isinteractive(info))
			_putchar('\n');
		freeinfo(info, 0);
	}
	writehistory(info);
	freeinfo(info, 1);
	if (!isinteractive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getenvirocopy(info)) == -1)
		{
			freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerror(info, "Permission denied\n");
		}
	}
}

/**
 * findcmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findcmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isdelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findpath(info, getenvro(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkcmd(info);
	}
	else
	{
		if ((isinteractive(info) || getenvro(info, "PATH=")
			|| info->argv[0][0] == '/') && iscmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerror(info, "not found\n");
		}
	}
}

/**
 * findbuilt - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int findbuilt(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (compstr(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
