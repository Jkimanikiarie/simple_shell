#include "shell.h"


char *fillMemory(char *str, char value, unsigned int length)
{
	unsigned int i;

	for (i = 0; i < length; i++)
		str[i] = value;
	return (str);
}

/**
 * freeStringArray - frees an array of strings
 * @strArray: array of strings
 */
void freeStringArray(char **strArray)
{
	char **temp = strArray;

	if (!strArray)
		return;
	while (*strArray)
		free(*strArray++);
	free(temp);
}


void *reallocateMemory(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (newPtr);
}
