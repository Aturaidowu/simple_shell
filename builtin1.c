#include "shell.h"

/**
 * _myhistory - shows the history list, one command by line
 * @info: struct containing potential arguments.
 *  Return: 0 on sucess
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - chnages alias to string
 * @info: struct parameter
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *s, c;
	int resett;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	c = *s;
	*s = 0;
	resett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = c;
	return (resett);
}

/**
 * set_alias - sets alias to a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - this will print an alias to a  string
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *s = NULL, *a = NULL;

	if (node)
	{
		s = _strchr(node->str, '=');
		for (a = node->str; a <= s; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - this function mimics the alias builtin
 * @info: this struct contains potential argument
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		s = _strchr(info->argv[j], '=');
		if (s)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}

