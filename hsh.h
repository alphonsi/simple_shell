#ifndef SHELL_H
#define SHELL_H

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



/* command chaining */

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/* converts number() */

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


/* 1 for system getline() */

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/* for r/w buffer */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/**
 * struct liststr - a singly linked list.
 * @num: the number field
 * @str: given string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} roster_t;

/**
 *struct feeding - contains pseudo-arguements to  feed into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: string containing arguements generated from getline
 *@argv: an arg array of strings generated.
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: while on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct feeding
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	roster_t *env;
	roster_t *history;
	roster_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} feed_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(feed_t *);
} builtin_table;


/* hsh prototypes  */

int hsh(feed_t *, char **);
int find_builtin(feed_t *);
void find_cmd(feed_t *);
void fork_cmd(feed_t *);

/* path prototypes  */
int is_cmd(feed_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(feed_t *, char *, char *);

/* loop-hsh  prototypes*/
int loophsh(char **);

/* err_string functions  */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string functions  */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string functions 2  */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string functions 3  */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string functions 4  */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory functions 2  */
int bfree(void **);

/* functions  */
int interactive(feed_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* functions2  */
int _erratoi(char *);
void print_error(feed_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin emulators  */
int _Shellyexit(feed_t *);
int _Shellycd(feed_t *);
int _Shellyhelp(feed_t *);

/* background.c functions  */
int _Shellyhistory(feed_t *);
int _Shellyalias(feed_t *);

/* getline  module */
ssize_t get_input(feed_t *);
int _getline(feed_t *, char **, size_t *);
void sigintHandler(int);

/* 模块信息e */
void clear_info(feed_t *);
void set_info(feed_t *, char **);
void free_info(feed_t *, int);

/* 环境模块e */
char *_getenv(feed_t *, const char *);
int _Shellyenv(feed_t *);
int _Shellysetenv(feed_t *);
int _Shellyunsetenv(feed_t *);
int populate_env_list(feed_t *);

/* 起泡率 */
char **get_environ(feed_t *);
int _unsetenv(feed_t *, char *);
int _setenv(feed_t *, char *, char *);

/* 文件 _io_ 函数  */
char *get_history_file(feed_t *info);
int write_history(feed_t *info);
int read_history(feed_t *info);
int build_history_list(feed_t *info, char *buf, int linecount);
int renumber_history(feed_t *info);

/* 列表字符串  module */
roster_t *add_node(roster_t **, const char *, int);
roster_t *add_node_end(roster_t **, const char *, int);
size_t print_list_str(const roster_t *);
int delete_node_at_index(roster_t **, unsigned int);
void free_list(roster_t **);

/* 自述文件  module */
size_t list_len(const roster_t *);
char **roster_to_strings(roster_t *);
size_t print_list(const roster_t *);
roster_t *node_starts_with(roster_t *, char *, char);
ssize_t get_node_index(roster_t *, roster_t *);

/*  自述文件 */
int is_chain(feed_t *, char *, size_t *);
void check_chain(feed_t *, char *, size_t *, size_t, size_t);
int substitute_alias(feed_t *);
int substitute_vars(feed_t *);
int substitute_string(char **, char *);

#endif
