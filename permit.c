#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination string to be copied
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, e;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		e = i;
		while (e < n)
		{
			dest[e] = '\0';
			e++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes maximally used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, e;
	char *s = dest;

	i = 0;
	e = 0;
	while (dest[i] != '\0')
		i++;
	while (src[e] != '\0' && e < n)
	{
		dest[i] = src[e];
		i++;
		e++;
	}
	if (e < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates character in a string
 *@s: string being parsed
 *@c: character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
