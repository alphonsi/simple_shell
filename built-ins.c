#include "shell.h"

/**
 * _alias - replica of alias builtin
 * @input: argument to be used
 *
 * Return: Always 0
 */
int _alias(data_t *input)
{
	int m = 0;
	char *c = NULL;
	log_t *node = NULL;

	if (input->argc == 1)
	{
		node = input->alias;
		while (node)
		{
			print_thealias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; input->argv[m]; m++)
	{
		c = _strchr(input->argv[m], '=');
		if (c)
			set_the_alias(input, input->argv[m]);
		else
			print_thealias(node_starts_with(input->alias, input->argv[m], '='));
	}
	return (0);
}
/**
 * _myexit - terminates the calling process
 * @input: parameter structure
 *
 * Return: exits with a given exit status (0)
 */
int _myexit(data_t *input)
{
	int check;

	if (input->argv[1])
	{
		check = str2int(input->argv[1]);
		if (check == -1)
		{
			input->status = 2;
			print_errmsg(input, "Illegal number: ");
			_erputs(input->argv[1]);
			_erputchar('\n');
			return (1);
		}
		input->err_num = str2int(input->argv[1]);
		return (-2);
	}
	input->err_num = -1;
	return (-2);
}

/**
 * _help - describes the builtin funtions
 * @input: arguments to be used contained in structure
 *
 * Return: Always 0
 */
int _help(data_t *input)
{
	char **arg_array;

	arg_array = input->argv;
	_puts("help call works, not implemented yet \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * _cd - changes directory
 * @input: Parameter structure
 *
 * Return: Always 0
 */
int _cd(data_t *input)
{
	char *m, *d, buff[1024];
	int chdir_ret;

	m = getcwd(buff, 1024);
	if (!m)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!input->argv[1])
	{
		d = _mygetenv(input, "HOME=");
		if (!d)
			chdir_ret =
				chdir((d = _mygetenv(input, "PWD=")) ? d : "/");
		else
			chdir_ret = chdir(d);
																}
	else if (_strcmp(input->argv[1], "-") == 0)
	{
		if (!_mygetenv(input, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(_mygetenv(input, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((d = _mygetenv(input, "OLDPWD=")) ? d : "/");							}
	else
		chdir_ret = chdir(input->argv[1]);
	if (chdir_ret == -1)
	{
		print_errmsg(input, "there's a problem, cd not possible ");
		_erputs(input->argv[1]), _erputchar('\n');
	}
	else
	{
		_setmyenv(input, "OLDPWD", _mygetenv(input, "PWD="));
		_setmyenv(input, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _history - displays the history list
 * @input: argument to be used
 *
 * Return: Always 0
 */
int _history(data_t *input)
{
	print_str_list(input->history);
	return (0);
}
