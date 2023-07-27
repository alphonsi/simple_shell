#include "shell.h"

/**
 * print_str_list- prints only the str element of a log_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_str_list(const log_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * add_node_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
log_t *add_node_start(log_t **head, const char *str, int num)
{
	log_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(log_t));
	if (!new_head)
		return (NULL);
	fillsmem((void *)new_head, 0, sizeof(log_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * delete_node_at_index - deletes node at a given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(log_t **head, unsigned int index)
{
	log_t *node, *old_node;
	unsigned int m = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (m == index)
		{
			old_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		m++;
		old_node = node;
		node = node->next;
	}
	return (0);
}


/**
 * add_node_at_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: string in the node
 * @num: node index used by history
 *
 * Return: size
 */
log_t *add_node_at_end(log_t **head, const char *str, int num)
{
	log_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(log_t));
	if (!new_node)
		return (NULL);
	fillsmem((void *)new_node, 0, sizeof(log_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(log_t **head_ptr)
{
	log_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
