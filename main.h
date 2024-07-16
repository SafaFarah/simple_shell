#ifndef _MAIN_H_
#define _MAIN_H_

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


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo -  into a function,
 *@arg: a string generated from getline
 *@argv: an array of strings from arg
 *@path: path of the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code
 *@line_flag: line count flag of input
 *@fname: the filename
 *@env: linked list copy of environ
 *@environ: environ from env
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf
 *@cmd_buf_type: ||, &&, ;
 *@readfd: read line input
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int line_flag;
	char *fname;
	list_t *env;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0}

/**
 *struct builtin - a builtin string
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int shell(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
void _eputs(char *);
int _eputchar(char);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
int print_dec(int n, int fd);
char *_memset(char *s, char b, unsigned int n);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _erratoi(char *);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
void sigintHandler(int);
void remove_comments(char *);
int my_exit(info_t *);
int _cd(info_t *);
int _help(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int env_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *h);
int delete_node(list_t **, unsigned int);
size_t list_len(const list_t *);
void free_list(list_t **head_ptr);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
