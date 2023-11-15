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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for looping command */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for number_ convertion () */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

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
 * struct passcue - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
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
typedef struct passcue
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} cue_t;

#define CUE_INIT \
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
	int (*func)(cue_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(cue_t *, char **);
int find_builtin(cue_t *);
void find_cmd(cue_t *);
void fork_cmd(cue_t *);

/* toem_parser.c */
int is_cmd(cue_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(cue_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* ourerrors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* ourstring.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* ourstring_one.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* ourexits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* ourtokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* ourrealloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* ourmemory.c */
int bfree(void **);

/* ouratoi.c */
int interactive(cue_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* ourerrors1.c */
int _erratoi(char *);
void print_error(cue_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*oubuiltin.c */
int _myexit(cue_t *);
int _mycd(cue_t *);
int _myhelp(cue_t *);

/* toem_builtin1.c */
int _myhistory(cue_t *);
int _myalias(cue_t *);

/*ourgetline.c */
ssize_t get_input(cue_t *);
int _getline(cue_t *, char **, size_t *);
void sigintHandler(int);

/* ourgetcue.c */
void clear_cue(cue_t *);
void set_cue(cue_t *, char **);
void free_cue(cue_t *, int);

/* ourenviron.c */
char *_getenv(cue_t *, const char *);
int _myenv(cue_t *);
int _mysetenv(cue_t *);
int _myunsetenv(cue_t *);
int populate_env_list(cue_t *);

/* ourgetenv.c */
char **get_environ(cue_t *);
int _unsetenv(cue_t *, char *);
int _setenv(cue_t *, char *, char *);

/* ourhistory.c */
char *get_history_file(cue_t *cue);
int write_history(cue_t *cue);
int read_history(cue_t *cue);
int build_history_list(cue_t *cue, char *buf, int linecount);
int renumber_history(cue_t *cue);

/* ourlists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* ourlists_one.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* ourvars.c */
int is_chain(cue_t *, char *, size_t *);
void check_chain(cue_t *, char *, size_t *, size_t, size_t);
int replace_alias(cue_t *);
int replace_vars(cue_t *);
int replace_string(char **, char *);

#endif

