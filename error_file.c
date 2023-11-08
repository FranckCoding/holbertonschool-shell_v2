#include "shell.h"

/**
 * error_file - handle error when file cannot be found or
 * if the file name is too long or the user haven't the permission to
 * open the file
 *
 * @chaine: Arguments passes by the user, that occur an error
 * @i: The iteration number of program's infinite loop
 * @argv: Argument value passes at the launch of the program to catch program
 * name
 * @nerr: The number of the error occured:
 * 0 for file not found
 * 1 for File name too long
 * 2 for Permission denied
 *
 * Return: EKEYEXPIRED
 */
int error_file(char *chaine, int i, char *argv[], int nerr)
{
	char *merr[3] = {	": not found\n",
						": File name too long\n",
						": Permission denied\n"};

	fprintf(stderr, "%s: %d: %s%s", argv[0], i, chaine, merr[nerr]);

	return (-EKEYEXPIRED);
}

/**
 * int_to_string - Convert an int to string
 *
 * @i: The integer needed to convert
 *
 * Return: str or NULL if the malloc failled
 */
char *int_to_string(int i)
{
	int power = 10, loop = 1;
	unsigned int number;
	char *str;

	if (i < 0)
		number = i * (-1);
	else
		number = i;

	while ((number / power) > 0)
	{
		power *= 10;
		loop++;
	}

	str = malloc(sizeof(char) * loop + 1);
	if (str == NULL)
		return (NULL);
	str[loop] = '\0';
	loop--;
	while (number > 0)
	{
		str[loop] = number % 10 + '0';
		number /= 10;
		loop--;
	}

	return (str);
}
