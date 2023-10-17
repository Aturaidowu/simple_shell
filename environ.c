#include "shell.h"

/**
 * _myenv - this prints the present environment
 * @info: Struct that contains potential arguments. For maintaining
 *          constant function prototypes.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets value of an environ variable
 * @info: struct containing potential arguments.
 * @name: env var name
 * Return: a value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *m;

	while (node)
	{
		m = starts_with(node->str, name);
		if (m && *m)
			return (m);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,or changes an existing one
 * @info: this structure contains potential arguments.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - removes an environment variable
 * @info: struct containing potential arguments. Maintains function prototypes.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int q;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (q = 1; q <= info->argc; q++)
		_unsetenv(info, info->argv[q]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: struct containing potential arguments.To maintain function prototypes
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}

