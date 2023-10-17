#include "shell.h"

int execute_alias_command(char **arguments, char __attribute__((__unused__)) **front);
void set_alias_value(char *alias_name, char *value);
void print_alias_info(alias_t *alias);


int execute_alias_command(char **arguments, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!arguments[0])
	{
		while (temp)
		{
			print_alias_info(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; arguments[i]; i++)
	{
		temp = aliases;
		value = _strchr(arguments[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(arguments[i], temp->name) == 0)
				{
					print_alias_info(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(arguments + i, 1);
		}
		else
			set_alias_value(arguments[i], value);
	}
	return (ret);
}


void set_alias_value(char *alias_name, char *value)
{
	alias_t *temp = aliases;
	int length, j, k;
	char *new_value;

	*value = '\0';
	value++;
	length = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (length + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(alias_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, alias_name, new_value);
}


void print_alias_info(alias_t *alias)
{
	char *alias_string;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (length + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, length);
	free(alias_string);
}

char **replace_aliases(char **arguments)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (_strcmp(arguments[0], "alias") == 0)
		return (arguments);
	for (i = 0; arguments[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(arguments[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_arguments(arguments, arguments);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(arguments[i]);
				arguments[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (arguments);
}
