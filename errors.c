#include "shell.h"

int calculateDigitLength(int num);
char *convertToString(int num);
int displayErrorMessage(char **args, int err);

/**
 * calculateDigitLength - Counts the number of digits in a given number.
 * @num: The number to calculate the digit length for.
 *
 * Return: The digit length of the number.
 */
int calculateDigitLength(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}

	return (length);
}

/**
 * convertToString - Converts an integer to a string.
 * @num: The integer to convert.
 *
 * Return: The converted string.
 */
char *convertToString(int num)
{
	char *buffer;
	int length = calculateDigitLength(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * displayErrorMessage - Writes a custom error message to the standard error output.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int displayErrorMessage(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = getEnvironmentError(args);
		break;
	case 1:
		error = getError1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = getError2Exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = getError2Syntax(args);
		else
			error = getError2Cd(args);
		break;
	case 126:
		error = getError126(args);
		break;
	case 127:
		error = getError127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
