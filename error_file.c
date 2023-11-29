#include "shell.h"

/**
 * error_file - handle error when file cannot be found or
 * if the file name is too long or the user haven't the permission to
 * open the file
 *
 * @datas: Structure with all data of the shell
 * @nerr: The number of the error occured:
 * 0 for file not found
 * 1 for File name too long
 * 2 for Permission denied
 *
 * Return: EKEYEXPIRED
 */
int error_file(shellData *datas, int nerr)
{
	char *merr[3] = {	": not found\n",
						": Permission denied\n"};

	fprintf(stderr, "%s: %d: %s%s", datas->argv[0], datas->loopCount,
			 datas->args[0], merr[nerr]);

	return (-EKEYEXPIRED);
}

/**
 * error_arguments - handle error when argument is wrong
 *
 * @shellData: Structure with all data of the shell
 * @nerr: The number of the error occured:
 * 0 for numeric argument required
 *
 * Return: EKEYEXPIRED
 */
int error_arguments(shellData *shellData, int nerr)
{
	char *merr[] = {	": numeric argument required\n",
						": Permission denied\n",
						": No such file or directory\n",
						": File name too long\n",
						" not set\n",
						": Not a directory\n"
	};

	fprintf(stderr, "%s: %d: %s: %s%s", shellData->argv[0], shellData->loopCount,
			 shellData->args[0], shellData->args[1], merr[nerr]);

	return (1);
}
