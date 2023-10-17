#include "shell.h"

char *create_permission_denied_error_message(char **args);
char *create_command_not_found_error_message(char **args);

/**
 * This function creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *create_permission_denied_error_message(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(hist);
	if (!hist_str)
		return (NULL);

	len = calculate_string_length(name) + calculate_string_length(hist_str) + calculate_string_length(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	concatenate_string(error, ": ");
	concatenate_string(error, hist_str);
	concatenate_string(error, ": ");
	concatenate_string(error, args[0]);
	concatenate_string(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * This function creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *create_command_not_found_error_message(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = convert_int_to_string(hist);
	if (!hist_str)
		return (NULL);

	len = calculate_string_length(name) + calculate_string_length(hist_str) + calculate_string_length(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	concatenate_string(error, ": ");
	concatenate_string(error, hist_str);
	concatenate_string(error, ": ");
	concatenate_string(error, args[0]);
	concatenate_string(error, ": not found\n");

	free(hist_str);
	return (error);
}
