#include "shell.h"

void display_env_help(void);
void display_setenv_help(void);
void display_unsetenv_help(void);
void display_history_help(void);

/**
 * display_env_help - Displays information about the 'env' command in the shell.
 */
void display_env_help(void)
{
	char *message = "env: env\n\tDisplays the current environment.\n";

	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * display_setenv_help - Displays information about the 'setenv' command in the shell.
 */
void display_setenv_help(void)
{
	char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environment variable or modifies an existing one.\n\n";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tPrints a message to stderr upon failure.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

void display_unsetenv_help(void)
{
	char *message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environmental variable.\n\n\tPrints a ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "message to stderr upon failure.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
