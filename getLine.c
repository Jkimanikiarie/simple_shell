#include "shell.h"


ssize_t read_input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t result = 0;
	size_t length_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		result = getline(buffer, &length_p, stdin);
#else
		result = _getline(info, buffer, &length_p);
#endif
		if (result > 0)
		{
			if ((*buffer)[result - 1] == '\n')
			{
				(*buffer)[result - 1] = '\0'; /* remove trailing newline */
				result--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = result;
				info->cmd_buf = buffer;
			}
		}
	}
	return (result);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t result = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	result = read_input_buffer(info, &buffer, &length);
	if (result == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		p = buffer + i; /* get pointer for return */

		check_chain(info, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p; 
		return (_strlen(p)); 
	}

	*buffer_p = buffer; 
	return (result); 
}


ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t result = 0;

	if (*i)
		return (0);
	result = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (result >= 0)
		*i = result;
	return (result);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t result = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	result = read_buffer(info, buffer, &len);
	if (result == -1 || (result == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * interruptHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void interruptHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
