#include "shell.h"


char *copy_string(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 **concatenate_strings - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@n: the maximum number of bytes to be used
 *Return: the concatenated string
 */
char *concatenate_strings(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (result);
}

/**
 **find_character - locates a character in a string
 *@string: the string to be searched
 *@character: the character to look for
 *Return: a pointer to the memory area containing the character
 */
char *find_character(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
