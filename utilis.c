#include "shell.h"

/**
 * issachain_delim - test if current char in buffer is a chain delimeter
 * @input: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int issachain_delim(data_t *input, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		input->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		input->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		input->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * checkchaining - checks we should continue chaining based on last status
 * @input: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: len of buf
 *
 * Return: Void
 *
 */
void checkchaining(data_t *input, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (input->cmd_buf_type == CMD_AND)
	{
		if (input->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (input->cmd_buf_type == CMD_OR)
	{
		if (!input->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_analias - substitutes an aliases in the tokenized string
 * @input: the parameter struct
 *
 * Return: 1 if substituted, 0 otherwise
 *
 */
int replace_analias(data_t *input)
{
	int i;
	log_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(input->alias, input->argv[0], '=');
		if (!node)
			return (0);
		free(input->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		input->argv[0] = p;
	}
	return (1);
}

/**
 * replace_var - substitutes variables in the tokenized string
 * @input: the parameter struct
 *
 * Return: 1 if substituted, 0 otherwise
 *
 */
int replace_var(data_t *input)
{
	int i = 0;
	log_t *node;

	for (i = 0; input->argv[i]; i++)
	{
		if (input->argv[i][0] != '$' || !input->argv[i][1])
			continue;

		if (!_strcmp(input->argv[i], "$?"))
		{
			sub_string(&(input->argv[i]),
				_strdup(convert_number(input->status, 10, 0)));
			continue;
		}
		if (!_strcmp(input->argv[i], "$$"))
		{
			sub_string(&(input->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(input->env, &input->argv[i][1], '=');
		if (node)
		{
			sub_string(&(input->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		sub_string(&input->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * sub_string - substitutes string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if substituted, 0 otherwise
 *
 */
int sub_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
