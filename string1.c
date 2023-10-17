#include "shell.h"

/**
 * _strcpy - copies String
 * @dest: the desti
 * @src: the sourc
 * Return: a pointer
 */

char *_strcpy(char *dest, char *src)
{
	int ink = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[ink])
	{
		dest[ink] = src[ink];
		ink++;
	}
	dest[ink] = 0;
	return (dest);
}

/**
 * _strdup - duplicates Stri
 * @str: the string to duplicate
 * Return: a pointer
 */

char *_strdup(const char *str)
{
	int lengt = 0;
	char *rett;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lengt++;
	rett = malloc(sizeof(char) * (lengt + 1));
	if (!rett)
		return (NULL);
	for (lengt++; lengt--;)
		rett[lengt] = *--str;
	return (rett);
}

/**
 *_puts - prints inputted string
 *@str: the string to print
 * Return: void
 */

void _puts(char *str)
{
	int ip = 0;

	if (!str)
		return;
	while (str[ip] != '\0')
	{
		_putchar(str[ip]);
		ip++;
	}
}

/**
 * _putchar - writes char c to stdout
 * @c: char to print
 * Return: 1 or -1.
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

