#include "shell.h"

/**
 * list_length - calculates the length of the list
 * @head: pointer to first node
 *
 * Return: size
 */
size_t list_length(const log_t *head)
{
	size_t m = 0;

	while (head)
	{
		head = head->next;
		m++;
	}
	return (m);
}

/**
 * log_to_strings - returns an array of strings of the list
 * @h: pointer to first node
 *
 * Return: array of strings
 */

char **log_to_strings(log_t *h)
{
	log_t *node = h;
	size_t m = list_len(h), n;
	char **strs;
	char *str;

	if (!h || !m)
		return (NULL);
	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);
	for (m = 0; node; node = node->next, m++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < m; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}
																	str = _strcpy(str, node->str);
		strs[m] = str;
																	}
	strs[m] = NULL;
	return (strs);
}

/**
 * get_node_at_index - gets the index of a node
 * @h: pointer to list head
 * @n: pointer to the node
 *
 * Return: index of node
 */

ssize_t get_node_at_index(log_t *h, log_t *n)
{
	size_t m = 0;

	while (h)
	{
		if (h == n)
			return (m);
		h = h->next;
		m++;
	}
	return (-1);
}


/**
 * print_list - prints all elements of a log_t linked list
 * @head: pointer to first node
 *
 * Return: number of elements
 */

size_t print_list(const log_t *head)
{
	size_t m = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: letter to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */

log_t *node_starts_with(log_t *head, char *prefix, char ch)
{
	char *m = NULL;

	while (head)
	{
		m = starts_with(head->str, prefix);
		if (m && ((ch == -1) || (*m == ch)))
			return (head);
		head = head->next;
	}
	return (NULL);
}
