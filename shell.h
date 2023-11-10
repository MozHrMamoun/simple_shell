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

/* All of strings functions*/

/* Functions_1-4.c */
int compstr(char *, char *);
char *dupstr(const char *);
char *concat((char *, char *, int);
char *strtow2(char *, char);

/* Functions_5-8.c */
int lenstr(char *);
char *copystr(char *dest, char *src);
char *cpystr(char *, char *, int);
char **strtow(char *, char *);

/* Functions_9-11.c */
char *beginwith(const char *, const char *);
void _puts(char *);
char *findchar(char *, char);

/* Functions_12-14.c */
char *catstr(char *, char *);
int _putchar(char);

/* end string functios*/

/* All of memory functios*/

/* memo_functions_1-2.c*/
void strfree(char **);
int panfree(void **);

/*memo_functions_3-4.c*/
char *setmemo(void *, unsigned int, unsigned int);
void *realloct(void *, unsigned int, unsigned int);

/* end of memory functios*/

/* Extra functions */

/* extra_functions_1-5.c*/
int strtoint(char *s);
int is_delim(char, char *);
int print_deci(int, int);
int stoi(char *);
void rmcomments(char *);

/* extra_functions_6-9.c*/
int isinteractive(info_t *);
void printerror(info_t *, char *);
int isalphab(int);
char *convenumber(long int, int, int);

/* end of extra functios */

/* All of list functions*/

/*Stringlist_1-5.c*/
size_t listlen(const list_t *)
list_t *addnodeatend(list_t **, const char *, int);
size_t print_list(const list_t *);
int deletenodeatindex(list_t **, unsigned int);
ssize_t getnodeindex(list_t *, list_t *);

/*Stringlist_6-10.c*/
list_t *addnode(list_t **, const char *, int);
char **list_to_strings(list_t *);
size_t printliststr(const list_t *);
list_t *nodestartswith(list_t *, char *, char);
void listfree(list_t **);

/* end of list functions*/

/* All of error string functions*/

/*error_string_functions.c*/
int erroputchar(char);
int prinput(char *str, int fd);
void erroputs(char *)
int prif(char c, int fd);

/* end of error string functions*/

/* all of enviroments functions*/

/*enviro_1-4.c*/
int myenvro(info_t *);
int rmenvro(info_t *, char *);
int mysetenvro(info_t *);
int makeenvlist(info_t *);

/*enviro_5-9*/
char **getenvirocopy(info_t *);
char *getenvro(info_t *, const char *);
int setenvro(info_t *, char *, char *);
int unsetenvro(info_t *);

/* end of enviroments functions*/

/* all of inputoutput files functions*/

/*io_file_functions.c*/
int writehistory(info_t *info);
int addhistorylist(info_t *info, char *buff, int linecount);
char *(info_t *info);
int readhistory(info_t *info);
int renumberhistory(info_t *info);

/* end of inputoutput files functions*/

/* all of chain functions*/

/*chain.c*/
int replacestring(char **, char *);
int replacealias(info_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int replacevars(info_t *);
int ischain(info_t *, char *, size_t *);

/* all of path functions*/

/*path.c*/
int iscmd(info_t *, char *);
char *findpath(info_t *, char *, char *);
char *duplichars(char *, int, int);

/* end of path functions*/

/* all of getlines functions*/

/*getlines.c*/

void sigintHandl(int);
int getnextline(info_t *, char **, size_t *);
ssize_t getinput(info_t *);

/* end of getlines functions*/

/* all of info functions*/

/*info.c*/
void clearinfo(info_t *);
void setinfo(info_t *, char **);
void freeinfo(info_t *, int);

/* end of info functions*/

/* all of hs functions*/

/*hs.c*/
int hs(info_t *info, char **);
void forkcmd(info_t *;
void findcmd(info_t *);
int findbuilt(info_t *);

/* end of hs functions*/

/* all of builtin functions*/

/*bultin.c*/
int myexit(info_t *);
int myhistory(info_t *);
int myalias_myalias(info_t *);
int myhelp(info_t *);
int mycd(info_t *);

/* end of builtin functions*/

/* loophsh.c */
int loophsh(char **);

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;

/**
 *struct builin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
	
/**
 *struct passinginfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
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
typedef struct passinginfo
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
} info_t;

#endif
