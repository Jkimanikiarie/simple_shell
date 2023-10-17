#include "shell.h"

/**
 * Print a string to standard error.
 * 
 * @param str The string to be printed
 * 
 * @return Nothing
 */
void printToStderr(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        writeCharToStderr(str[i]);
        i++;
    }
}

/**
 * Write a character to standard error.
 * 
 * @param c The character to be written
 * 
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToStderr(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * Write a character to a given file descriptor.
 * 
 * @param c The character to be written
 * @param fd The file descriptor to write to
 * 
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToFileDescriptor(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * Write a string to a given file descriptor.
 * 
 * @param str The string to be written
 * @param fd The file descriptor to write to
 * 
 * @return The number of characters written
 */
int writeStringToFileDescriptor(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += writeCharToFileDescriptor(*str++, fd);
    }
    return (i);
}
