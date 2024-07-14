#include "main.h"

/**
* _strtok - function that slipts a string into words.
* @str: string
* @d: delimeter
*
* Return: pointer to array of words
*/
char *_strtok(char *str, const char *d)
{
	static char *s;
	char *result;

	if (!str)
		str = s;
	if (!str)
		return (NULL);
	while (1)
	{
		if (d_isdelim(*str, d))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}
	result = str;
	while (1)
	{
		if (*str == '\0')
		{
			s = str;
			return (result);
		}
		if (d_isdelim(*str, d))
		{
			*str = '\0';
			s = str + 1;
			return (result);
		}
		str++;
	}
}


/**
* d_isdelim - function checks if the character is delimeter.
* @c: character
* @d: delimeter
*
* Return: 1 on success, or 0 on failure
*/
unsigned int d_isdelim(char c, const char *d)
{
	while (*d != '\0')
	{
		if (c == *d)
			return (1);
		d++;
	}
	return (0);
}
