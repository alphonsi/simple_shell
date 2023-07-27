#include "shell.h"

/**
 * is_executable- determines if a file is an executable command
 * @input: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 *
 */
int is_executable(data_t *input, char *path)
{
	struct stat st;

	(void)input;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * *dup_charss - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 *
 */
char *dup_charss(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path- finds this cmd in the PATH string
 * @input: the info struct
 * @pathstr: the PATH string
 * @c: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 *
 */
char *find_path(data_t *input, char *pathstr, char *c)
{
	int i = 0, curr_pos = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(c) > 2) && starts_with(c, "./"))
	{
		if (is_executable(input, c))
			return (c);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			p = dup_charss(pathstr, curr_pos, i);
			if (!*p)
				_strcat(p, c);
			else
			{
				_strcat(p, "/");
				_strcat(p, c);
			}
			if (is_executable(input, p))
				return (p);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

