#include "shell.h"

/**
 * clear_info - initializes feed_t struct
 * @input: struct address
 *
 */
void clear_info(data_t *input)
{
	input->arg = NULL;
	input->argv = NULL;
	input->path = NULL;
	input->argc = 0;
}

/**
 * set_info - initializes feed_t struct
 * @input: struct address
 * @av: argument vector
 *
 */
void set_info(data_t *input, char **av)
{
	int i = 0;

	input->fname = av[0];
	if (input->arg)
	{
		input->argv = _strtok(input->arg, " \t");
		if (!input->argv)
		{

			input->argv = malloc(sizeof(char *) * 2);
			if (input->argv)
			{
				input->argv[0] = _strdup(input->arg);
				input->argv[1] = NULL;
			}
		}
		for (i = 0; input->argv && input->argv[i]; i++)
			;
		input->argc = i;

		replace_analias(input);
		replace_var(input);
	}
}

/**
 * free_info - frees feed_t struct fields
 * @input: struct address
 * @all: true if freeing all fields
 *
 */
void free_info(data_t *input, int all)
{
	ffree(input->argv);
	input->argv = NULL;
	input->path = NULL;
	if (all)
	{
		if (!input->cmd_buf)
			free(input->arg);
		if (input->env)
			free_list(&(input->env));
		if (input->history)
			free_list(&(input->history));
		if (input->alias)
			free_list(&(input->alias));
		ffree(input->environ);
			input->environ = NULL;
		bfree((void **)input->cmd_buf);
		if (input->readfd > 2)
			close(input->readfd);
		_putchar(BUF_FLUSH);
	}
}

