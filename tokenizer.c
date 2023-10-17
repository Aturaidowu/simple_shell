#include "shell.h"

/**
 * **strtow -breaks a string into letters
 * @str: string inputted
 * @d: delim string
 * Return: a pointer or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, l, Numwd = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			Numwd++;

	if (Numwd == 0)
		return (NULL);
	s = malloc((1 + Numwd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < Numwd; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - breaks string into words
 * @str: inputted string
 * @d: delim
 * Return: a pointer or NULL on failure
 */

char **strtow2(char *str, char d)
{
	int i, j, k, l, Numwd = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			Numwd++;
	if (Numwd == 0)
		return (NULL);
	s = malloc((1 + Numwd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < Numwd; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

