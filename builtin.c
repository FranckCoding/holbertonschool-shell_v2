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

	datas->builtinExecuted = 1;
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

/**
 * cdBuiltInCommand - The function to execute the Change Directory command
 *
 * @datas: All datas of the shell functionnement
*/
void cdBuiltInCommand(shellData *datas)
{
	char *path = datas->args[1];
	struct stat st;

	datas->builtinExecuted = 1;

	if (!path)
		path = _getenv("HOME", datas->env);
	else if (_strcmp("-", path) == 0)
	{
		if (datas->oldPwd)
			path = datas->oldPwd;
		else
		{
			datas->args[1] = "OLDPWD";
			error_arguments(datas, ENV_NOT_SET);
			datas->args[1] = path;
			return;
		}
	}

	if (stat(path, &st) == -1)
	{
		error_arguments(datas, NO_FILE_OR_DIR);
		return;
	}

	if (access(path, R_OK) == -1)
	{
		error_arguments(datas, PERM_DENIED);
		return;
	}

	datas->oldPwd = _getenv("PWD", datas->env);
	chdir(path);
}
