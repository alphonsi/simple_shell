#include "shell.h"

/**
 * _environ - copys the environment and returns a string array
 * @input: Arguments contained in the structure
 * Return: Always 0
 */
char **_environ(data_t *input)
{
	if (!input->environ || input->env_changed)
	{
		input->environ = log_to_strings(input->env);
		input->env_changed = 0;
	}

	return (input->environ);
}

/**
 * _unsetmyenv - delete environment variables
 * @input: arguments used
 *  Return: 1 on delete, 0 otherwise
 * @value: string in the env
 */
int _unsetmyenv(data_t *input, char *value)
{
	log_t *node = input->env;
	size_t m = 0;
	char *n;

	if (!node || !value)
		return (0);

	while (node)
	{
		n = starts_with(node->str, value);
		if (n && *n == '=')
		{
			input->env_changed = delete_node_at_index(&(input->env), m);
			m = 0;
			node = input->env;
			continue;
		}
		node = node->next;
		m++;
	}
	return (input->env_changed);
}

/**
 * _setmyenv - intitializes new environment var or modifys it
 * @input: arguments used
 * @varia: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setmyenv(data_t *input, char *varia, char *value)
{
	char *buf = NULL;
	log_t *node;
	char *t;

	if (!varia || !value)
		return (0);

	buf = malloc(_strlen(varia) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, varia);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = input->env;
	while (node)
	{
		t = starts_with(node->str, varia);
		if (t && *t == '=')
		{
			free(node->str);
			node->str = buf;
			input->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(input->env), buf, 0);
	free(buf);
	input->env_changed = 1;
	return (0);
}
