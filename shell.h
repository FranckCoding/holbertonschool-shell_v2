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
 * enum ErrorFile -		Enumeration to represent error cases related to
 *						file/command passes at argument in the shell
 *
 * @FILE_NOT_FOUND:	Indicates that the specified command was not found
 *						This error typically occurs when attempting to pass unknow
 *						argument.
 *
 * @FILE_NAME_LONG:		Indicates that the file name provided is too long.
 *						This error may occur if the length of the file name
 *						exceeds system limits.
 *
 * @PERM_DENIED:		Indicates a permission denied error.
 *						This error occurs when the program does not have the
 *						necessary permission to open or access the specified file
 *
 */
enum ErrorFile
{
	FILE_NOT_FOUND,
	FILE_NAME_LONG,
	PERM_DENIED
};

/**
 * enum ErrorArg -		Enumeration to represent error cases related to
 *						arguments commands passes in the shell
 *
 * @NUMERIC_ARG_ISSUE:	Indicates the arguments passes for a built-in function
 *						is not a numeric argument. This error occur when the
 *						passes is not an Int.
 *
 * @NO_FILE_OR_DIR:		Indicates the argument is not a file or directory
 *
 * @ENV_NOT_SET:		Indicates that one environment is not set
 *
 * @NOT_A_DIR:			Indicates that argument is not a directory
 */
enum ErrorArg
{
	NUMERIC_ARG_ISSUE,
	NO_FILE_OR_DIR,
	ENV_NOT_SET = 3,
	NOT_A_DIR
};

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
 * @builtinExecuted: See if a built-in function is executed
 * 0 to false and 1 otherwise
 * @buffer: Buffer where the arguments passes by the user is stored
 * @args: Array of String of arguments passes by the user
 * @status: The last status of the program when error is occur
 * @argv: All arguments passes at the launch of the program
 * @oldPwd: The previous directory
*/
typedef struct shell_data
{
	int loopCount;
	path_t *path;
	int pathExecuted;
	env_t *env;
	int builtinExecuted;
	char *buffer;
	char **args;
	int status;
	char **argv;
	char *oldPwd;
} shellData;

/**
 * struct built_in_function_pointer - Structure for a pointer function
 * to choose the correct built-in function that the user wants
 *
 * @command: The command to test with strcmp
 * @function: The pointer of function with the adress of the correct function
*/
typedef struct built_in_function_pointer
{
	char *command;
	void (*function)(shellData *datas);
} builtIn;

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
int error_arguments(shellData *shellData, int nerr);

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
void exitBuiltIn(shellData *datas);
void cdBuiltInCommand(shellData *datas);

env_t *create_env_variable(void);
void free_linked_env(env_t *head);
env_t *allocate_node_env(char *name, char *value, env_t *next);
env_t *add_env_node(env_t *head, char *name, char *value);

void exit_procedure(shellData *datas);
void sigint_handle(__attribute__((unused))int i);

int _atoi(const char *str);
int _isNumber(const char *str);

#endif
