#include "shell.h"

/**
 *_eputs - to print an inputted string
 * @str: string to print
 * Return: void
 */
void _eputs(char *str)
{
	int h = 0;

	if (!str)
		return;
	while (str[h] != '\0')
	{
		_eputchar(str[h]);
		h++;
	}
}

/**
 * _eputchar - writes a character to stderr
 * @c: character to be output
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int ti;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ti >= WRITE_BUF_SIZE)
	{
		write(2, buf, ti);
		ti = 0;
	}
	if (c != BUF_FLUSH)
		buf[ti++] = c;
	return (1);
}

/**
 * _putfd - output the character c to a given file descriptor
 * @c: character to print
 * @fd: the file descriptor we want to write to
 * Return: 1 if successful
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int ti;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ti >= WRITE_BUF_SIZE)
	{
		write(fd, buf, ti);
		ti = 0;
	}
	if (c != BUF_FLUSH)
		buf[ti++] = c;
	return (1);
}

/**
 *_putsfd - prints an inputted string
 * @str: the string to print
 * @fd: filedescriptor to write to
 * Return: chars put
 */
int _putsfd(char *str, int fd)
{
	int ti = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ti += _putfd(*str++, fd);
	}
	return (ti);
}

