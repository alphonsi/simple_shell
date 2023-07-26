#include "shell.h"

#include "shell.h"

/**
 * _shell_loop - the main shell loop
 * @input: parameter used in the loop
 * @av: the argument array in the main function
 *
 * Return: 0 if successfull, 1 on error
 */
int _shell_loop(data_t *input, char **av)
{
	ssize_t p = 0;
	int builtin_ret = 0;

	while (p != -1 && builtin_ret != -2)
	{
		clear_info(input);
		if (interactive(input))
			_puts("$ ");
		_erputchar(BUF_FLUSH);
		p = get_input(input);
		if (p != -1)
		{
			set_info(input, av);
			builtin_ret = builtin_search(input);
			if (builtin_ret == -1)
				_findthecmd(input);
		}
		else if (interactive(input))
			_putchar('\n');
		free_info(input, 0);
	}
	write_history(input);
	free_info(input, 1);
	if (!interactive(input) && input->status)
		exit(input->status);
	if (builtin_ret == -2)
	{
		if (input->err_num == -1)
			exit(input->status);
		exit(input->err_num);
	}
	return (builtin_ret);
}

/**
 * builtin_search - searches for a builtin command
 * @input: argument to be used
 *
 * Return: -1 if successfull, 0 if failure
 */
int builtin_search(data_t *input)
{
	int m, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _Shellyexit},
		{"env", _myenv},
		{"help", _Shellyhelp},
		{"history", _Shellyhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _Shellycd},
		{"alias", _Shellyalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(input->argv[0], builtintbl[i].type) == 0)
		{
			input->line_count++;
			built_in_ret = builtintbl[i].func(input);
			break;
		}
	return (built_in_ret);
}

/**
 * _forkthecmd - creates a child process for exec to run command
 * @input: parameter used
 *
 * Return: void
 */
void _forkthecmd(data_t *input)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(input->path, input->argv, _environ(input)) == -1)
		{
			free_info(input, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(input->status));
		if (WIFEXITED(input->status))
		{
			input->status = WEXITSTATUS(input->status);
			if (input->status == 126)
				print_error(input, "Permission denied\n");
		}
	}
}

/**
 * _findthecmd - searches for a command in the PATH
 * @input: Parameter to be used in searching
 *
 * Return: void
 */

void _findthecmd(data_t *input)
{
	char *path = NULL;
	int p, n;

	input->path = input->argv[0];
	if (input->linecount_flag == 1)
	{
		input->line_count++;
		input->linecount_flag = 0;
	}
	for (p = 0, n = 0; input->arg[p]; n++)
		if (!is_delim(input->arg[p], " \t\n"))
			n++;
	if (!n)
		return;

	path = find_path(input, _mygetenv(input, "PATH="), input->argv[0]);
	if (path)
	{
		input->path = path;
		_forkthecmd(input);
	}
	else
	{
		if ((interactive(input) || _getenv(input, "PATH=")
			|| input->argv[0][0] == '/') && is_cmd(input, input->argv[0]))
			_forkthecmd(input);
		else if (*(input->arg) != '\n')
		{
			input->status = 127;
			print_error(input, "not found\n");
		}
	}
}
