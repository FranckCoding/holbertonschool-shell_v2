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
 * @datas: The pointer with all data of Shell
 *
 * Return: Buffer, or NULL if EOF or exit
 */
char *_getline(shellData *datas)
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
		free(buffer);
		exit_procedure(datas);
	}

	buffer[charactersGet - 1] = '\0';
	datas->charactersGet = charactersGet--;

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
 * @datas: The pointer with all the data of the shell
 */
void exit_procedure(shellData *datas)
{
	int status = datas->status;

	if (status < 0)
		status = -status;

	if (datas->buffer != NULL)
		free(datas->buffer);

	if (datas->args != NULL)
		free_separate_av(datas->args);

	free_linked_env(datas->env);
	free_linked_path(datas->path);
	free(datas);

	exit(status);
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
