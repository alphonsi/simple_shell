#include "shell.h"

/**
 * _unsetalias - sets an alias to a string
 * @input: argument to be used
 * @str: the string alias
 *
 * Return: 0 if successfull, 1 on error
 **/
int _unsetalias(data_t *input, char *str)
{
	char *m, ch;
	int ret;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	ch = *m;
	*m = 0;
	ret = delete_node_at_index(&(input->alias),
		get_node_at_index(input->alias, node_starts_with(input->alias, str, -1)));
	*m = ch;
	return (ret);
}

/**
 * set_the_alias - sets an  alias to a string
 * @input: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 **/
int set_the_alias(data_t *input, char *str)
{
	char *ch;

	ch = _strchr(str, '=');
	if (!ch)
		return (1);
	if (!*++ch)
		return (_unsetalias(input, str));

	_unsetalias(input, str);
	return (add_node_at_end(&(input->alias), str, 0) == NULL);
}

/**
 * print_thealias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_thealias(log_t *node)
{
	char *m = NULL, *a = NULL;

	if (node)
	{
		m = _strchr(node->str, '=');
		for (a = node->str; a <= m; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(m + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
