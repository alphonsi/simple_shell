#include "shell.h"

/**
 * issaninteractive - returns true if shell is interactive mode
 * @input: this is struct address
 *
 * Return: 1 if it is interactive mode, 0 otherwise
 *
 */
int issaninteractive(data_t *input)
{
	return (isatty(STDIN_FILENO) && input->readfd <= 2);
}

/**
 * issadelim - checks if character is a delimeter
 * @b: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 *
 */
int issadelim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 *issalphabe - checks for alphabetic character
 *@b: The character to input
 *Return: 1 if b is alphabetic, 0 otherwise
 *
 */

int issalphabe(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str2int - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, otherwise return converted number
 *
 */

int str2int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

