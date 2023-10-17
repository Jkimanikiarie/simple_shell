#include "shell.h"

char **get_environment_variables(info_t *info)
{
	if (!info->environment || info->environment_changed)
	{
		info->environment = convert_list_to_strings(info->env_list);
		info->environment_changed = 0;
	}

	return (info->environment);
}


int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env_list;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->env_list), index);
			index = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->environment_changed);
}


int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env_list;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_list), buffer, 0);
	free(buffer);
	info->environment_changed = 1;
	return (0);
}
