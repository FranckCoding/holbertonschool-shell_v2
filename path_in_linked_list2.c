#include "shell.h"

/**
 * separate_path - Separate a string when the char ':' is present
 *
 * @str: The string we separate
 *
 * Return: j
 */
char **separate_path(char *str)
{
	char *y, **j;
	int i = 0, length;

	length = count_word(str, ":");
	y = strtok(str, ":");

	j = (char **)malloc(sizeof(char *) * (length + 1));
	j[length] = NULL;

	while (y != NULL)
	{
		j[i++] = y;
		y = strtok(NULL, ":");
	}

	return (j);
}

/**
 * create_path_variable - Create the linked list variable
 * path using the environ
 *
 * @env: Linked list of all environment variable
 *
 * Return: path
 */
path_t *create_path_variable(env_t *env)
{
	char *str;
	char **the_path;
	path_t *path = NULL;
	int j = 0;

	str = _getenv("PATH", env);
	the_path = separate_path(str);

	while (the_path[j] != NULL)
	{
		if (j == 0)
			path = add_path_node(path, the_path[j]);
		else
			add_path_node(path, the_path[j]);
		j++;
	}

	free(the_path);
	return (path);
}

/**
 * test_with_path - Test if an command exist in one path of path
 *
 * @datas: The data structure with all data of the shell
 *
 * Return: buffer if no command exist in path, otherwise path + command
 */
void test_with_path(shellData *datas)
{
	int lenValue;
	char *tmp_value, *tmp_buffer;
	int loop = 0;
	struct stat st;
	path_t *path = datas->path;

	while (path != NULL)
	{
		lenValue = _strlen(path->value);
		tmp_buffer = (char *)malloc(sizeof(char) * (256 + lenValue + 1));
		*tmp_buffer = '\0';

		if (path->value[lenValue - 1] != '/')
		{
			tmp_value = _strdup(path->value);
			tmp_buffer = _strcat(tmp_buffer, tmp_value);
			tmp_buffer[lenValue] = '/';
			while (datas->args[0][loop] != '\0')
			{
				tmp_buffer[lenValue + 1 + loop] = datas->args[0][loop];
				loop++;
			}
			tmp_buffer[lenValue + 1 + loop] = '\0';
		}

		if (_strcmp(datas->args[0], "..") != 0 && stat(tmp_buffer, &st) == 0)
		{
			free(tmp_value);
			_execute(tmp_buffer, datas);
			free(tmp_buffer);
			datas->pathExecuted = 1;
			return;
		}

		free(tmp_value);
		free(tmp_buffer);
		path = path->next;
		loop = 0;
	}
}
