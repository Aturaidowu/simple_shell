#include "shell.h"

/**
 * input_buf - contains buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t ret = 0;
	size_t len_s = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		ret = getline(buf, &len_s, stdin);
#else
		ret = _getline(info, buf, &len_s);
#endif
		if (ret > 0)
		{
			if ((*buf)[ret - 1] == '\n')
			{
				(*buf)[ret - 1] = '\0'; /* remove trailing newline */
				ret--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = ret;
				info->cmd_buf = buf;
			}
		}
	}
	return (ret);
}

/**
 * get_input - gets a line
 * @info: parameter struct
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t res = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	res = input_buf(info, &buf, &len);
	if (res == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf;
	return (res); /* returns the length of buffer from _getline() */
}

/**
 * read_buf - reads  buffer
 * @info: parameter structure
 * @buf: buffer
 * @i: size
 * Return: returns x
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _getline - gets the next line of input
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t kay;
	ssize_t ray = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	ray = read_buf(info, buf, &len);
	if (ray == -1 || (ray == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	kay = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + kay : kay + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, kay - i);
	else
		_strncpy(new_p, buf + i, kay - i + 1);

	s += kay - i;
	i = kay;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: signal number
 * Return: nothing
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

