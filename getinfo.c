#include "shell.h"

/**
 * initialize_info - initializes the info_t struct
 * @info: pointer to the struct
 */
void initialize_info(info_t *info)
{
	info->argument = NULL;
	info->argument_vector = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * set_info - sets the values of the info_t struct
 * @info: pointer to the struct
 * @arguments: argument vector
 */
void set_info(info_t *info, char **arguments)
{
	int i = 0;

	info->filename = arguments[0];
	if (info->argument)
	{
		info->argument_vector = strtow(info->argument, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->argument);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_variables(info);
	}
}

/**
 * free_info - frees the fields of the info_t struct
 * @info: pointer to the struct
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->argument);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environment_variables);
		info->environment_variables = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUFFER_FLUSH);
	}
}
