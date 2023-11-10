#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				erroputs(av[0]);
				erroputs(": 0: Can't open ");
				erroputs(av[1]);
				erroputchar('\n');
				erroputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = f;
	}
	makeenvlist(info);
	readhistory(info);
	hs(info, av);
	return (EXIT_SUCCESS);
}
