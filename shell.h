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
} log_t;

/**
 * struct feeding - contains pseudo-arguements to  feed into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: string containing arguements generated from getline
 * @argv: an arg array of strings generated.
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: while on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
	log_t *env;
	log_t *history;
	log_t *alias;
	char **environ;
	int env_changed;
															int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} data_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;


/* shell_loop prototypes  */

int _shell_loop(data_t *input, char **av);
int builtin_search(data_t *input);
void _findthecmd(data_t *input);
void _forkthecmd(data_t *input);

/* path.c prototypes  */
int is_executable(data_t *input, char *path);
char *dup_charss(char *pathstr, int start, int stop);
char *find_path(data_t *input, char *pathstr, char *c);

/* loop-hsh  prototypes*/
int loophsh(char **);

/* err_string functions  */
void _erputs(char *str);
int _erputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string functions  */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string functions 2  */
void _puts(char *);
int _putchar(char);

/* string_functions prototypes  */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);

/* string functions 4  */
char **_strtok(char *, char *);
char **_strtok2(char *, char);

/* memp.c  functions */
void free_info(data_t *input, int all);
void set_info(data_t *input, char **av);
void clear_info(data_t *input);
int bfree(void **ptr);

/* pipe.c functions  */
char *convert_number(long int num, int base, int flags);
int print_dec(int input, int fd);
void print_errmsg(data_t *input, char *estr);
void remov_cmts(char *buf);

/* re-routing.c functions */
 
char *fillsmem(char *s, char b, unsigned int n);
void ffree(char **pp);
void *reallocmem(void *ptr, unsigned int old_size, unsigned int new_size);


/* utilis.c functions */
int issachain_delim(data_t *input, char *buf, size_t *p);
void checkchaining(data_t *input, char *buf, size_t *p, size_t i, size_t len);
int replace_analias(data_t *input);
int replace_var(data_t *input);
int sub_string(char **old, char *new);


/* functions  */
int issaninteractive(data_t *input);
int issadelim(char b, char *delim);
int issalpha(int b);
int str2int(char *s);

/* built-ins prototypes */
int _myexit(data_t *input);
int _cd(data_t *input);
int _help(data_t *input);
int _history(data_t *input);
int _alias(data_t *input);

/* getline  prototype */
ssize_t get_input(data_t *);
int _getlyn(data_t *, char **, size_t *);
void sigintHandler(int);

/* environ prototypes*/
char *_mygetenv(data_t *input, const char *name);
int _myenv(data_t *input);
int _mysetenv(data_t *input);
int _myunsetenv(data_t *input);
int _env_populate(data_t *input);

/* environ2 prototypes */
char **_environ(data_t *input);
int _unsetmyenv(data_t *input, char *value);
int _setmyenv(data_t *input, char *varia, char *value);

/* history_input prototypes  */
char *find_hist_file(data_t *input);
int write_the_hist(data_t *input);
int read_hist(data_t *input);
int build_hist(data_t *input, char *b, int lc);
int renumber_hist_list(data_t *input);

/* linked_lists  prototype */
size_t list_len(const log_t *head);
char **log_to_strings(log_t *h);
size_t print_str_list(const log_t *head);
log_t *node_starts_with(log_t *node, char *prefix, char ch);
ssize_t get_node_at_index(log_t *h, log_t *n);

/* linked_lists2 prototypes */
log_t *add_node_start(log_t **head, const char *str, int num);
log_t *add_node_at_end(log_t **head, const char *str, int num);
size_t print_list_str(const log_t *h);
int delete_node_at_index(log_t **head, unsigned int index);
void free_list(log_t **head_ptr);

/*setting_aliase prototypes */
int _unsetalias(data_t *input, char *str);
int set_the_alias(data_t *input, char *str);
int print_thealias(log_t *node);
#endif

