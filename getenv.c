#include "shell.h"

/**
 * get_environ - returns string array copy of our environ
 * @info: struct that contains potential arguments
 * Return: Always 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes environment variable
 * @info: Structure with  potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete or 0 otherwise
 * @var: string env var property
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - this initializes a new environment variable,
 *             or modify an existing one
 * @info: structure that contains potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *duf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	duf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!duf)
		return (1);
	_strcpy(duf, var);
	_strcat(duf, "=");
	_strcat(duf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = duf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), duf, 0);
	free(duf);
	info->env_changed = 1;
	return (0);
}

