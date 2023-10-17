#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for reading and writing */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining types */
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Conversion options for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag for using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * A singly linked list structure
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * Structure containing pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * Structure containing a builtin command string and its related function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function declarations */
int shell(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int shell_loop(char **);

void error_puts(char *);
int error_putchar(char);
int putfd(char c, int fd);
int putsfd(char *str, int fd);

int string_length(char *);
int string_compare(char *, char *);
char *starts_with(const char *, const char *);
char *string_concatenate(char *, char *);

char *string_copy(char *, char *);
char *string_duplicate(const char *);
void normal_puts(char *);
int normal_putchar(char);

char *string_copy_n(char *, char *, int);
char *string_concatenate_n(char *, char *, int);
char *string_character(char *, char);

char **string_to_words(char *, char *);
char **string_to_words2(char *, char);

char *memory_set(char *, char, unsigned int);
void free_memory(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

int free_block(void **);

int interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_integer(char *);

int error_to_integer(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int exit_builtin(info_t *);
int cd_builtin(info_t *);
int help_builtin(info_t *);

int history_builtin(info_t *);
int alias_builtin(info_t *);

ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sigint_handler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *_getenv(info_t *, const char *);
int env_builtin(info_t *);
int setenv_builtin(info_t *);
int unsetenv_builtin(info_t *);
int populate_env_list(info_t *);

char **get_environment(info_t *);
int unset_environment(info_t *, char *);
int set_environment(info_t *, char *, char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_length(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif
