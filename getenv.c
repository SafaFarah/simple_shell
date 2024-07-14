#include "main.h"

/**
* _getenv - a function that Get an environment variable.
* @name: Variable to look for
* Return: The environnment variable, if not found NULL
*/
char *_getenv(const char *name)
{
	int i = 0;
	int n;
	int count = 0;
	int len;
	char *name_copy = (char *)name;

	if (name == NULL || !name[i])
		return (NULL);
	len = _strlen(name_copy);
	while (*(environ + i))
	{
		n = 0;
		while (*(*(environ + i) + n) != '=')
		{
			if (*(*(environ + i) + n) == name[n])
				count++;
			n++;
		}
		if (count == len)
		{
			n++;
			return (*(environ + i) + n);
		}
		i++;
		count = 0;
	}
	return (NULL);
}
