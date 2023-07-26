#include "shell.h"

/**
 * main - main function of the program
 * @ac: number of arguments
 * @av: array of the arguments
 *
 * Return: 0 if successfull, 1 on error
 */
int main(int ac, char **av)
{
	data_t input[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_erputs(av[0]);
				_erputs(": 0: Can't open ");
				_erputs(av[1]);
				_erputchar('\n');
				_erputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		input->readfd = fd;
	}
	_env_populate(input);
	read_history(input);
	_shell_loop(input, av);
	return (EXIT_SUCCESS);
}
