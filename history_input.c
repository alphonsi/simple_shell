#include "shell.h"

/**
 * renumber_hist_list - update the list of history after changes
 * @input: parameter used
 *
 * Return: history count
 */
int renumber_hist_list(data_t *input)
{
	log_t *node = input->history;
	int m = 0;

	while (node)
	{
		node->num = m++;
		node = node->next;
	}
	return (input->histcount = m);
}

/**
 * find_hist_file - searches for the history file
 * @input: parameter used
 *
 * Return: string pointer containing the file
 */

char *find_hist_file(data_t *input)
{
	char *b, *dir;

	dir = _mygetenv(input, "HOME=");
	if (!dir)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, dir);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}

/**
 * write_the_hist - creates new file or append if file exists
 * @input: the argument to be used
 *
 * Return: 1 on success, -1 on failure
 */
int write_the_hist(data_t *input)
{
	ssize_t fd;
	char *filename = find_hist_file(input);
	log_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = input->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * build_hist - add an entry to the linked list file
 * @input: parameter used
 * @b: buffer to be used
 * @lc: history count
 *
 * Return: 0 on success
 */
int build_hist(data_t *input, char *b, int lc)
{
	log_t *node = NULL;

	if (input->history)
		node = input->history;
	add_node_at_end(&node, b, lc);

	if (!input->history)
		input->history = node;
	return (0);
}

/**
 * read_hist - reads file history
 * @input: argument to be used
 *
 * Return: count on success, 0 on failure
 */
int read_hist(data_t *input)
{
	int m, last = 0, lc = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *b = NULL, *filename = find_hist_file(input);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (fsize + 1));
	if (!b)
		return (0);
	rdlen = read(fd, b, fsize);
	b[fsize] = 0;
	if (rdlen <= 0)
		return (free(b), 0);
	close(fd);
	for (m = 0; m < fsize; m++)
		if (b[m] == '\n')
		{
			b[m] = 0;
			build_hist(input, b + last, lc++);
			last = m + 1;
		}
	if (last != m)
		build_hist(input, b + last, lc++);
	free(b);
	input->histcount = lc;
	while (input->histcount-- >= HIST_MAX)
		delete_node_at_index(&(input->history), 0);
	renumber_hist_list(input);
	return (input->histcount);
}
