#include "shell.h"

/**
 * _prompt - Write the prompt
 *
 */
void _prompt(void)
{
	if (isatty(0) == 1)
		_puts("$ ");
}

/**
 * _getline - Ask to the user what command he want
 *
 * @path: The linked list path, if EOF or exit, it's free
 * @env: The linked list of all environment variable
 * @status: The status of the execute
 *
 * Return: Buffer, or NULL if EOF or exit
 */
char *_getline(path_t *path, env_t *env, int status)
{
	size_t size = 256;
	ssize_t charactersGet;
	char *buffer;

	buffer = _calloc(sizeof(char), size);

	charactersGet = getline(&buffer, &size, stdin);

	if (charactersGet == EOF)
	{
		if (isatty(0) == 1)
			_putchar('\n');
		exit_procedure(buffer, path, env, status);
	}

	buffer[charactersGet - 1] = '\0';
	charactersGet -= 1;

	if (charactersGet == 0)
	{
		free(buffer);
		return (NULL);
	}

	return (buffer);
}

/**
 * exit_procedure - Free all variable when EOF or exit
 *
 * @buffer: The buffer of getline
 * @path: The linked list path
 * @env: The linked list of all environment variable
 * @status: The status for exit
 */
void exit_procedure(char *buffer, path_t *path, env_t *env, int status)
{
	free_linked_env(env);
	free_linked_path(path);
	free(buffer);
	if (status < 0)
		status = -status;
	exit(status);
}

/**
 * _printenv - Print all environment variables
 *
 * @env: Linked list of all environment variables
 * @sep: All options for printenv
 *
 * Return: 0
 */
int _printenv(env_t *env, __attribute__((unused))char **sep)
{

	while (env != NULL)
	{
		_puts(env->name);
		_puts("=");

		if (env->value != NULL)
			_puts(env->value);

		_putchar('\n');

		env = env->next;
	}

	return (0);
}

/**
 * sigint_handle - Handle the CTRL+D signal
 * print a new line and a new prompt
 *
 * @i: Unused variable
 */
void sigint_handle(__attribute__((unused))int i)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
