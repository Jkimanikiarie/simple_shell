#include "shell.h"
int (*get_builtin_command(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_change_directory(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);


int (*get_builtin_command(char *command))(char **args, char **front)
{
	builtin_t commands[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_change_directory },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; commands[i].name; i++)
	{
		if (_strcmp(commands[i].name, command) == 0)
			break;
	}
	return (commands[i].f);
}


int shell_exit(char **args, char **front)
{
	int i, int_length = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			int_length++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= int_length && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}


int shell_change_directory(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}


int shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		display_all_help();
	else if (_strcmp(args[0], "alias") == 0)
		display_alias_help();
	else if (_strcmp(args[0], "cd") == 0)
		display_cd_help();
	else if (_strcmp(args[0], "exit") == 0)
		display_exit_help();
	else if (_strcmp(args[0], "env") == 0)
		display_env_help();
	else if (_strcmp(args[0], "setenv") == 0)
		display_setenv_help();
	else if (_strcmp(args[0], "unsetenv") == 0)
		display_unsetenv_help();
	else if (_strcmp(args[0], "help") == 0)
		display_help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
