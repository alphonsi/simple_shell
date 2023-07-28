#include "shell.h"

/**
 * **_strtok - splits a string into words
 * @string: the input string
 * @lim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok(char *string, char *lim)
{
	int i, e, k, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!lim)
		lim = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!issadelim(string[i], lim) && (issadelim(string[i + 1], lim) ||
			!string[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, e = 0; e < numwords; e++)
	{
		while (issadelim(string[i], lim))
			i++;
		k = 0;
		while (!issadelim(string[i + k], lim) && string[i + k])
			k++;
		s[e] = malloc((k + 1) * sizeof(char));
		if (!s[e])
		{
			for (k = 0; k < e; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[e][m] = string[i++];
		s[e][m] = 0;
	}
	s[e] = NULL;
	return (s);
}

/**
 * **_strtok2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtok2(char *str, char d)
{
	int i, e, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, e = 0; e < numwords; e++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[e] = malloc((k + 1) * sizeof(char));
		if (!s[e])
		{
			for (k = 0; k < e; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[e][m] = str[i++];
		s[e][m] = 0;
	}
	s[e] = NULL;
	return (s);
}
