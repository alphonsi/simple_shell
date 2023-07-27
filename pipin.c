#include "shell.h"

/**
 * print_errmsg - prints an error message
 * @input: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 *
 */
void print_errmsg(data_t *input, char *estr)
{
	_erputs(input->fname);
	_erputs(": ");
	print_dec(input->line_count, STDERR_FILENO);
	_erputs(": ");
	_erputs(input->argv[0]);
	_erputs(": ");
	_erputs(estr);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 *
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _erputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number- converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 *
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remov_cmts - function substitutes first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 *
 */
void remov_cmts(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

