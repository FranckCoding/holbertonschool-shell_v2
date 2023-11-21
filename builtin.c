#include "shell.h"

/**
 * _printenv - Print all environment variables
 *
 * @datas:The pointer with all the data of the shell
 *
 */
void _printenv(shellData *datas)
{
	env_t *env = datas->env;

	while (env != NULL)
	{
		_puts(env->name);
		_puts("=");

		if (env->value != NULL)
			_puts(env->value);

		_putchar('\n');

		env = env->next;
	}

	datas->envExecuted = 1;
}

/**
 * exitBuiltIn - Execute the Built In command Exit with the first
 * argument for the exit code
 *
 * @datas: All the datas for the shell program
*/
void exitBuiltIn(shellData *datas)
{
	if (datas->args[1])
	{
		if (_isNumber(datas->args[1]))
			datas->status = _atoi(datas->args[1]);
		else
			datas->status = error_arguments(datas, NUMERIC_ARG_ISSUE);
	}

	exit_procedure(datas);
}
