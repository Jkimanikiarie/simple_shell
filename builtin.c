#include "shell.h"


int exitShell(info_t *info)
{
	int exitCode;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitCode = _erratoi(info->argv[1]);
		if (exitCode == -1)
		{
			info->status = 2;
			printErrorMessage(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->errorNumber = _erratoi(info->argv[1]);
		return (-2);
	}
	info->errorNumber = -1;
	return (-2);
}


int changeDirectory(info_t *info)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		newDir = _getenv(info, "HOME=");
		if (!newDir)
			chdirResult = /* TODO: what should this be? */
				chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirResult = /* TODO: what should this be? */
			chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(info->argv[1]);
	if (chdirResult == -1)
	{
		printErrorMessage(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

int showHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temp att_unused workaround */
	return (0);
}
