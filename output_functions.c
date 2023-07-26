#include "shell.h"

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @n: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char n)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (n == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(1, buf, p);
		p = 0;
	}
	if (n != BUF_FLUSH)
		buf[p++] = n;
	return (1);
}
