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
 * handleDash - Handle the dash character when passed at argument of cd
 *				built-in function
 *
 * @datas: All the datas of the shell program
 * @path: The path passes at argument of the the cd built-in
 *
 * Return: 0 if OLDPWD is not set, return 1 otherwise
 */
int handleDash(shellData *datas, char **path)
{
	if (_strcmp("-", *path) == 0)
	{
		if (datas->oldPwd)
			*path = datas->oldPwd;
		else
		{
			datas->args[1] = "OLDPWD";
			error_arguments(datas, ENV_NOT_SET);
			datas->args[1] = *path;
			return (0);
		}
	}

	return (1);
}

/**
 * checkPathValidity -	Check the validity of the path passed at the argument
 *						of the cd function built-in
 *
 * @datas: All the datas of the shell program
 * @path: The path passes at argument of the cd built-in
 *
 * Return: 0 if the file/directory set at the path doesn't exist, if the path
 * is a file or if the user doesn't have the permission to change the directory
 * to this path
 * Otherwise, return 1
 */
int checkPathValidity(shellData *datas, char *path)
{
	struct stat st;

	if (_strlen(path) > 255)
	{
		error_arguments(datas, FILE_NAME_LONG);
		return (0);
	}

	if (stat(path, &st) == -1)
	{
		error_arguments(datas, NO_FILE_OR_DIR);
		return (0);
	}

	if (S_ISREG(st.st_mode))
	{
		error_arguments(datas, NOT_A_DIR);
		return (0);
	}

	if (access(path, R_OK) == -1)
	{
		error_arguments(datas, PERM_DENIED);
		return (0);
	}

	return (1);
}

/**
 * cdBuiltInCommand - The function to execute the Change Directory command
 *
 * @datas: All datas of the shell functionnement
*/
void cdBuiltInCommand(shellData *datas)
{
	char *path = datas->args[1];

	datas->builtinExecuted = 1;

	if (!path)
		path = _getenv("HOME", datas->env);

	if (!handleDash(datas, &path) || !checkPathValidity(datas, path))
		return;

	datas->oldPwd = _getenv("PWD", datas->env);
	chdir(path);
}
