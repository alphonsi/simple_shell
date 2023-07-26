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
 *  * struct liststr - a singly linked list.
 *   * @num: the number field
 *    * @str: given string
 *     * @next: points to the next node
 *      */
typedef struct liststr
{
		int num;
			char *str;
				struct liststr *next;
} log_t;

/**
 *  *struct feeding - contains pseudo-arguements to  feed into a function,
 *   *					allowing uniform prototype for function pointer struct
 *    *@arg: string containing arguements generated from getline
 *     *@argv: an arg array of strings generated.
 *      *@path: a string path for the current command
 *       *@argc: the argument count
 *        *@line_count: the error count
 *         *@err_num: the error code for exit()s
 *          *@linecount_flag: while on count this line of input
 *           *@fname: the program filename
 *            *@env: linked list local copy of environ
 *             *@environ: custom modified copy of environ from LL env
 *              *@history: the history node
 *               *@alias: the alias node
 *                *@env_changed: on if environ was changed
 *                 *@status: the return status of the last exec'd command
 *                  *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *                   *@cmd_buf_type: CMD_type ||, &&, ;
 *                    *@readfd: the fd from which to read line input
 *                     *@histcount: the history line number count
 *                      */
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
 *  *struct builtin - contains a builtin string and related function
 *   *@type: the builtin command flag
 *    *@func: the function
 *     */
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

/* path prototypes  */
int is_cmd(data_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(data_t *, char *, char *);

/* loop-hsh  prototypes*/
int loophsh(char **);

/* err_string functions  */
void _erputs(char *);
int _erputchar(char);
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
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory functions 2  */
int bfree(void **);

/* functions  */
int interactive(data_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* functions2  */
int _erratoi(char *);
void print_error(data_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* built-ins prototypes */
int _exit(data_t *input);
int _cd(data_t *input);
int _help(data_t *input);
int _history(data_t *input);
int _alias(data_t *input);

/* getline  module */
ssize_t get_input(data_t *);
int _getline(data_t *, char **, size_t *);
void sigintHandler(int);

/* 模块信息e */
void clear_info(data_t *);
void set_info(data_t *, char **);
void free_info(data_t *, int);

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
size_t print_list(const log_t *head);
log_t *node_starts_with(log_t *node, char *prefix, char ch);
ssize_t get_node_index(log_t *h, log_t *n);

/* linked_lists2 prototypes */
log_t *add_node(log_t **head, const char *str, int num);
log_t *add_node_end(log_t **head, const char *str, int) num;
size_t print_list_str(const log_t *h);
int delete_node_at_index(log_t **head, unsigned int index);
void free_list(log_t **head_ptr);


/*  自述文件 */
int is_chain(data_t *, char *, size_t *);
void check_chain(data_t *, char *, size_t *, size_t, size_t);
int substitute_alias(data_t *);
int substitute_vars(data_t *);
int substitute_string(char **, char *);

#endif

