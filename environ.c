#include "shell.h"

/**
 * _mygetenv - searches the environment for variables
 * @input: Arguments to be used
 * @name: name of the variable
 *
 * Return: value of the variable
 */

char *_mygetenv(data_t *input, const char *name)
{
	log_t *node = input->env;
	char *m;

	while (node)
	{
		m = starts_with(node->str, name);
		if (m && *m)
			return (m);
		node = node->next;
	}
	return (NULL);
}

/**
 * _myenv - creates the environment
 * @input: Arguments to be used
 *
 * Return: 0
 */

int _myenv(data_t *input)
{
		print_list_str(input->env);
			return (0);
}

/**
 * _mysetenv - sets the environment variables
 * @input: arguments to be used, contained in the structure
 *
 * Return: 0
 */
int _mysetenv(data_t *input)
{
	if (input->argc != 3)
	{
		_erputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setmyenv(input, input->argv[1], input->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - unsets the environment variable
 * @input: arguments to be used
 *
 * Return: 0
 */
int _myunsetenv(data_t *input)
{
	int n;

	if (input->argc == 1)
	{
		_erputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= input->argc; i++)
		_unsetmyenv(input, input->argv[i]);

	return (0);
}

/**
 *_env_populate - adds information to the environment
 * @input: contains potential arguments
 *
 * Return: 0
 */
int _env_populate(data_t *input)
{
	log_t *node = NULL;
	ssize_t m;

	for (m = 0; environ[m]; m++)
		add_node_at_end(&node, environ[m], 0);
	input->env = node;
	return (0);
}
