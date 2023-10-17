#include "shell.h"

char **copy_environment(void);
void free_environment(void);
char **get_environment_variable(const char *variable);

/**
 * copy_environment - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a double pointer to the new copy.
 */
char **copy_environment(void)
{
    char **new_environment;
    size_t size;
    int index;

    for (size = 0; environment[size]; size++)
        ;

    new_environment = malloc(sizeof(char *) * (size + 1));
    if (!new_environment)
        return (NULL);

    for (index = 0; environment[index]; index++)
    {
        new_environment[index] = malloc(_strlen(environment[index]) + 1);

        if (!new_environment[index])
        {
            for (index--; index >= 0; index--)
                free(new_environment[index]);
            free(new_environment);
            return (NULL);
        }
        _strcpy(new_environment[index], environment[index]);
    }
    new_environment[index] = NULL;

    return (new_environment);
}

/**
 * free_environment - Frees the environment copy.
 */
void free_environment(void)
{
    int index;

    for (index = 0; environment[index]; index++)
        free(environment[index]);
    free(environment);
}


char **get_environment_variable(const char *variable)
{
    int index, length;

    length = _strlen(variable);
    for (index = 0; environment[index]; index++)
    {
        if (_strncmp(variable, environment[index], length) == 0)
            return (&environment[index]);
    }

    return (NULL);
}
