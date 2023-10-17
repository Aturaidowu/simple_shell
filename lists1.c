#include "shell.h"

/**
 * list_len - gets the length of linked list
 * @h: this points to first node
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t p = 0;

	while (h)
	{
		h = h->next;
		p++;
	}
	return (p);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: points to first node
 * Return: an array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t ik = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !ik)
		return (NULL);
	strs = malloc(sizeof(char *) * (ik + 1));
	if (!strs)
		return (NULL);
	for (ik = 0; node; node = node->next, ik++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < ik; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[ik] = str;
	}
	strs[ik] = NULL;
	return (strs);
}


/**
 * print_list - this prints all the elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t ik = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ik++;
	}
	return (ik);
}

/**
 * node_starts_with - returns node whose string starts prefix
 * @node: list head pointer
 * @prefix: the str we want to match
 * @c: the nxt char after prefix to match
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets a node index
 * @head: a pointer to list head
 * @node: a pointer to the node
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t m = 0;

	while (head)
	{
		if (head == node)
			return (m);
		head = head->next;
		m++;
	}
	return (-1);
}
