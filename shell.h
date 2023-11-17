#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

extern char **environ;

/**
 * struct linked_path - Do a linked list for environment variable PATH
 *
 * @value: The value of the PATH
 * @next: The next node
 *
 */
typedef struct linked_path
{
	char *value;
	struct linked_path *next;
} path_t;

/**
 * struct linked_env - Do a linked list for all environment variables
 *
 * @name: Name of the current environment variable
 * @value: Value of the current environment variable
 * @next: The next environment variable
 *
 */
typedef struct linked_env
{
	char *name;
	char *value;
	struct linked_env *next;

} env_t;

/**
 * struct shell_data - All the data for shell
 *
 * @loopCount: The count of the shell loop
 * @path: The linked list of the Path
 * @pathExecuted: See if path is tested correctly 0 to false and 1 otherwise
 * @env: The linked list of the env
 * @envExecuted: See if the env built-in is executed 0 to false and 1 otherwise
 * @buffer: Buffer where the arguments passes by the user is stored
 * @args: Array of String of arguments passes by the user
 * @status: The last status of the program when error is occur
 * @argv: All arguments passes at the launch of the program
*/
typedef struct shell_data
{
	int loopCount;
	path_t *path;
	int pathExecuted;
	env_t *env;
	int envExecuted;
	char *buffer;
	char **args;
	int status;
	char **argv;
} shellData;


/* Functions in shell.c */
void loop_asking(shellData *datas);
int _execute(char *cmd, shellData *datas);
shellData *_shellDataInitialisation(char *argv[]);

int _strlen(char *s);
char **strtow(char *str, char sep);
int strwlen(char *s);
void _puts(char *str);
char **separate_av(char *str, char *sep);
void free_separate_av(char **str);
int print_int(int n);
int _putchar(char c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);
int count_word(char *s, char *sep);
int _strcmp(char *s1, char *s2);
path_t *linked_lp(path_t *head, char *value);
path_t *create_linked_lp(char *the_path);
void free_node(path_t *head);

void _prompt(void);
char *_getline(shellData *datas);

int error_file(shellData *datas, int nerr);

path_t *add_path_node(path_t *head, char *value);
path_t *allocate_node(char *value, path_t *next);
char **separate_path(char *str);
char *_getenv(const char *name, env_t *env);
void free_linked_path(path_t *head);
path_t *create_path_variable(env_t *env);
void last_c_linked_path(path_t *path);
char *_strcat(char *dest, char *src);
void test_with_path(shellData *datas);
char *_strdup(char *str);

void _printenv(shellData *datas);
env_t *create_env_variable(void);
void free_linked_env(env_t *head);
env_t *allocate_node_env(char *name, char *value, env_t *next);
env_t *add_env_node(env_t *head, char *name, char *value);

void exit_procedure(shellData *datas);
void sigint_handle(__attribute__((unused))int i);

#endif
