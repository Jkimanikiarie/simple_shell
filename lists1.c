#include "shell.h"


size_t count_nodes(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return count;
}


char **convert_list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t node_count = count_nodes(head);
	char **strings;
	char *string;

	if (!head || !node_count)
		return NULL;
	strings = malloc(sizeof(char *) * (node_count + 1));
	if (!strings)
		return NULL;
	for (size_t i = 0; current_node; current_node = current_node->next, i++)
	{
		string = malloc(_strlen(current_node->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return NULL;
		}

		string = _strcpy(string, current_node->str);
		strings[i] = string;
	}
	strings[node_count] = NULL;
	return strings;
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return count;
}

/**
 * find_node_starts_with - returns the node whose string starts with a given prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @next_char: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((next_char == -1) || (*p == next_char)))
			return head;
		head = head->next;
	}
	return NULL;
}


ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}
	return -1;
}
