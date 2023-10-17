#include "shell.h"

/**
 * interactive - this function returns true if shell is in interactive mode
 *
 * @info: structure address
 *
 * Return: 1 if interactive mode or 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - this checks if a given char is a delimeter
 *
 * @c: the character to be checked
 *
 * @delim: this is the delimeter string
 *
 * Return: 1 if true, otherwise 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - this checks for an alphabetic character
 *@c: char to be inputted
 *Return: 1 if char is alphabetic and 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - it converts a string to an integer
 *@s: this is the str we want to convert
 *Return: 0 if there's no numbers in str
 */

int _atoi(char *s)
{
	int k, sign = 1, flagg = 0, printout;
	unsigned int res = 0;

	for (k = 0;  s[k] != '\0' && flagg != 2; k++)
	{
		if (s[k] == '-')
			sign *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			flagg = 1;
			res *= 10;
			res += (s[k] - '0');
		}
		else if (flagg == 1)
			flagg = 2;
	}

	if (sign == -1)
		printout = -res;
	else
		printout = res;

	return (printout);
}

