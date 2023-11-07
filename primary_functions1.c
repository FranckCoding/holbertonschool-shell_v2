#include "shell.h"

/**
 * _strlen - Return the length of a string
 *
 * @s: The String we want to know the length
 *
 * Return: length
 */
int _strlen(char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		s++;
		length++;
	}

	return (length);
}

/**
 * strtow - Splits a string into words
 *
 * @str: The string we split
 * @sep: The separator needed for separate the string
 *
 * Return: str
 */
char **strtow(char *str, char __attribute__((unused))sep)
{
	char **aled;
	int numberWords, i, iWord, iAled = 0;

	if (str == NULL || *str == '\0')
		return (NULL);

	numberWords = count_word(str, " ");
	if (numberWords == 0)
		return (NULL);

	aled = malloc(sizeof(char *) * numberWords + 8);
	if (aled == NULL)
		return (NULL);
	aled[numberWords] = NULL;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != sep)
		{
			aled[iAled] = (char *)malloc(sizeof(char) * strwlen((str + i)) + 1);
			if (aled[iAled] == NULL)
			{
				for (iAled = 0; iAled < numberWords; iAled++)
					free(aled[iAled]);

				free(aled);
				return (NULL);
			}

			for (iWord = 0; str[i + iWord] != sep && str[i + iWord]; iWord++)
				aled[iAled][iWord] = str[i + iWord];
			aled[iAled][iWord] = '\0';
			if (iWord > 0)
				iAled++;
			i += strwlen((str + i)) - 1;
		}
	}
	return (aled);
}

/**
 * count_word - Return the number of word in the strings
 *
 * @s: The String we want to know the words
 * @sep: The separator for the count
 *
 * Return: length
 */
int count_word(char *s, char *sep)
{
	int length, i = 0, isep = 0;

	if (s == NULL)
		return (0);

	while (*s != sep[isep] && sep[isep] != '\0')
		isep++;

	if (sep[isep] == '\0')
		length = 1;
	else
		length = 0;

	isep = 0;
	while (s[i] != '\0')
	{
		while (s[i] != sep[isep] && sep[isep] != '\0')
			isep++;

		if (sep[isep] != '\0' && sep[isep] >= 21)
			length++;

		i++;
		isep = 0;
	}
	return (length);
}

/**
 * strwlen - Return the length of a word in the current string
 *
 * @s: The String we want to know the length
 *
 * Return: length
 */
int strwlen(char *s)
{
	int length = 0;

	while (*(s + length) != ' ' && *(s + length))
		length++;

	return (length);
}

/**
 * _puts - Print in standard output a string
 *
 * @str: The string we want to print
 */
void _puts(char *str)
{
	int length;

	if (str != NULL)
	{
		length = _strlen(str);

		write(STDOUT_FILENO, str, length);
	}
}
