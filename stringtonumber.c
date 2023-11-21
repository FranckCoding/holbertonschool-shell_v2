#include "shell.h"

/**
 * _atoi - Convert a String to a in
 *
 * @str: The string to convert
 *
 * Return: The string converted to int
*/
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ')
		str++;

	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (sign * result);
}

/**
 * _isNumber - Check if an string is a number
 *
 * @str: The string to check if this is a number
 *
 * Return: 1 if this is a number, 0 otherwise
*/
int _isNumber(const char *str)
{
	while (*str == ' ')
		str++;

	if (*str == '-' || *str == '+')
		str++;

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
		{
			return (0);
		}
		str++;
	}

	return (1);
}
