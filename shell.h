#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

/*
 * File: my_shell.h
 * Auth: Alex Smith
 *       Brennan Johnson
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environment */
extern char **my_environment;
/* Global program name */
char *program_name;
/* Global history counter */
int history_counter;

/**
 * struct directory_list - A new struct type defining a linked list.
 * @path: A directory path.
 * @next: A pointer to another struct directory_list.
 */
typedef struct directory_list
{
	char *path;
	struct directory_list *next;
} directory_t;

/**
 * struct builtin_command - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @function: A function pointer to the builtin command's function.
 */
typedef struct builtin_command
{
	char *name;
	int (*function)(char **arguments, char **front);
} builtin_command_t;

/**
 * struct alias - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias.
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_t;

/* Global aliases linked list */
alias_t *alias_list;

/* Main Helpers */
ssize_t get_input_line(char **lineptr, size_t *n, FILE *stream);
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size);
char **tokenize_string(char *line, char *delimiter);
char *get_command_location(char *command);
directory_t *get_directory_path(char *path);
int execute_command(char **arguments, char **front);
void free_directory_list(directory_t *head);
char *integer_to_string(int number);

/* Input Helpers */
void handle_input_line(char **line, ssize_t read);
void replace_variables(char **arguments, int *execution_return);
char *get_arguments(char *line, int *execution_return);
int call_arguments(char **arguments, char **front, int *execution_return);
int run_arguments(char **arguments, char **front, int *execution_return);
int handle_arguments(int *execution_return);
int check_arguments(char **arguments);
void free_arguments(char **arguments, char **front);
char **replace_aliases(char **arguments);

/* String functions */
int string_length(const char *string);
char *string_concatenate(char *destination, const char *source);
char *string_concatenate_n(char *destination, const char *source, size_t n);
char *string_copy(char *destination, const char *source);
char *string_character(const char *string, char character);
int string_span(const char *string, const char *accept);
int string_compare(const char *string1, const char *string2);
int string_compare_n(const char *string1, const char *string2, size_t n);

/* Builtins */
int (*get_builtin_command(char *command))(char **arguments, char **front);
int my_shell_exit(char **arguments, char **front);
int my_shell_env(char **arguments, char __attribute__((__unused__)) **front);
int my_shell_setenv(char **arguments, char __attribute__((__unused__)) **front);
int my_shell_unsetenv(char **arguments, char __attribute__((__unused__)) **front);
int my_shell_cd(char **arguments, char __attribute__((__unused__)) **front);
int my_shell_alias(char **arguments, char __attribute__((__unused__)) **front);
int my_shell_help(char **arguments, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **copy_environment(void);
void free_environment(void);
char **get_environment(const char *variable);

/* Error Handling */
int create_error(char **arguments, int error);
char *error_environment(char **arguments);
char *error_1(char **arguments);
char *error_2_exit(char **arguments);
char *error_2_cd(char **arguments);
char *error_2_syntax(char **arguments);
char *error_126(char **arguments);
char *error_127(char **arguments);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
directory_t *add_node_end(directory_t **head, char *path);
void free_directory_list(directory_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int process_file_commands(char *file_path, int *execution_return);
#endif /* _MY_SHELL_H_ */
