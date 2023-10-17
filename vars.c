#include "shell.h"

/**
 * is_chain - test if char in buffer is a chain
 * @info: struct parameter
 * @buf: character buffer
 * @p: address of position in buf
 * Return: 1 or 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[b] == ';')
	{
		buf[b] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - continue chaining based on last status
 * @info: par struct
 * @buf: char buffer
 * @p: addr of current buf
 * @i: start pos in buf
 * @len: length of buf
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t mt = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			mt = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			mt = len;
		}
	}

	*p = mt;
}

/**
 * replace_alias - repla aliases in the tokenized string
 * @info: par struct
 * Return: 1 or 0 otherwise
 */

int replace_alias(info_t *info)
{
	int ip;
	list_t *node;
	char *p;

	for (ip = 0; ip < 10; ip++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 or 0
 */

int replace_vars(info_t *info)
{
	int im = 0;
	list_t *node;

	for (im = 0; info->argv[im]; im++)
	{
		if (info->argv[im][0] != '$' || !info->argv[im][1])
			continue;

		if (!_strcmp(info->argv[im], "$?"))
		{
			replace_string(&(info->argv[im]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[im], "$$"))
		{
			replace_string(&(info->argv[im]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[im][1], '=');
		if (node)
		{
			replace_string(&(info->argv[im]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[im], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replace str
 * @old: add of prev. string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

