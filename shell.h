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
int compstr (char *s1, char *s2);
char *dupstr(const char *s);
char *concat(char *s1, char *s2, int b);
char **stringtoword(char *str, char d);

/* Functions_5-8.c */
int lenstr(char *s);
char *copystr(char *dest, char *src);
char *cpystr(char *dest, char *src, int c);
char **strtoword(char *str, char *d);

/* Functions_9-11.c */
char *beginwith(const char *haystack, const char *needle);
void _puts(char *strn);
char *findchar(char *s, char c);

/* Functions_12-14.c */
char *catstr(char *dest, char *src)
int _putchar(char c)

/* end string functios*/

/* All of memory functios*/

/* memo_functions_1-2.c*/
void strfree(char **ss);
int panfree(void **p);

/*memo_functions_3-4.c*/
char *setmemo(char *p, char b, unsigned int c);
void *realloct(void *poi, unsigned int old_size, unsigned int new_size);

/* end of memory functios*/

/* Extra functions */

/* extra_functions_1-5.c*/
int strtoint(char *s);
int is_delim(char c, char *delm);
int print_deci(int input, int f);
int stoi(char *s);
void rmcomments(char *add);

/* extra_functions_6-9.c*/
int isinteractive(info_t *statement);
void printerror(info_t *info, char *errstr);
int isalphab(int c);
char *convenumber(long int num, int base, int arg);

/* end of extra functios */

/* All of list functions*/

/*Stringlist_1-5.c*/
size_t listlen(const list_t *head);
list_t *addnodeatend(list_t **head, const char *str, int c);
size_t print_list(const list_t *head);
int deletenodeatindex(list_t **head, unsigned int index);
ssize_t get_node_index(list_t *head, list_t *node);

/*Stringlist_6-10.c*/
list_t *addnode(list_t **head, const char *str, int num);
char **list_to_strings(list_t *head);
size_t printliststr(const list_t *head);
list_t *nodestartswith(list_t *node, char *prefix, char c);
void listfree(list_t **head_ptr);

/* end of list functions*/

/* All of error string functions*/

/*error_string_functions.c*/
int erroputchar(char c);
int prinput(char *str, int f);
void erroputs(char *str);
int prif(char c, int f);

/* end of error string functions*/

/* all of enviroments functions*/

/*enviro_1-4.c*/
int myenvro(info_t *info);
int rmenvro(info_t *info, char *c);
int mysetenvro(info_t *info);
int makeenvlist(info_t *info);

/*enviro_5-9*/
char **getenvirocopy(info_t *info);
char *getenvro(info_t *info, const char *name);
int setenvro(info_t *info, char *var, char *value);
int unsetenvro(info_t *info);

/* end of enviroments functions*/

/* all of inputoutput files functions*/

/*io_file_functions.c*/
int writehistory(info_t *info);
int addhistorylist(info_t *info, char *buff, int linecount);
char *gethistoryfile(info_t *info);
int readhistory(info_t *info);
int renumberhistory(info_t *info);

/* end of inputoutput files functions*/

/* all of chain functions*/

/*chain.c*/
int replacestring(char **old, char *new);
int replacealias(info_t *info);
void checkchain(info_t *info, char *buff, size_t *p, size_t i, size_t leng);
int replacevars(info_t *info);
int ischain(info_t *info, char *buff, size_t *p);

/* all of path functions*/

/*path.c*/
int iscmd(info_t *info, char *pat);
char *findpath(info_t *info, char *patstr, char *cmd);
char *duplichars(char *patstr, int start, int stop);

/* end of path functions*/

/* all of getlines functions*/

/*getlines.c*/

void sigintHandl(__attribute__((unused))int sig_num);
ssize_t readbuff(info_t *info, char *buff, size_t *i);
ssize_t inputbuff(info_t *info, char **buff, size_t *leng);
int getnextline(info_t *info, char **ptr, size_t *leng);
ssize_t getinput(info_t *info);

/* end of getlines functions*/

/* all of info functions*/

/*info.c*/
void clearinfo(info_t *info);
void setinfo(info_t *info, char **av);
void freeinfo(info_t *info, int all);

/* end of info functions*/

/* all of hs functions*/

/*hs.c*/
int hs(info_t *info, char **av);
void forkcmd(info_t *info);
void findcmd(info_t *info);
int findbuilt(info_t *info);

/* end of hs functions*/

/* all of builtin functions*/

/*bultin.c*/
int myexit(info_t *info);
int myhistory(info_t *info);
int setalias(info_t *info, char *strg);
int myalias(info_t *info);
int myhelp(info_t *info);
int mycd(info_t *info);
int printalias(list_t *node);
int unsetalias(info_t *info, char *strg);

/* end of builtin functions*/

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
