#include "shell.h"

/**
 * _erratoi - changes string to an integer
 * @s: string to change
 * Return: 0 or -1 on error
 */
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			res *= 10;
			res += (s[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - dispalys an error message
 * @info: parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 * print_d - function prints a decimal or base 10 number
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters to print
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int ji, scount = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		scount++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (ji = 1000000000; ji > 1; ji /= 10)
	{
		if (_abs_ / ji)
		{
			__putchar('0' + current / ji);
			scount++;
		}
		current %= ji;
	}
	__putchar('0' + current);
	scount++;

	return (scount);
}

/**
 * convert_number - a clone of itoa, it converts numbers
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: a string
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
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to change
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}

