#include "main.h"
void _strfun(char *fpath, char *path_token, char *command);
/**
 * get_path - function gets the path for the given command
 * @command: The given command
 * Return: The path for the given command
 */
char *get_path(char *command)
{
	char *path, *fpath, *path_copy, *path_token;
	int len, dir_len;
	struct stat buffer;

	path = _getenv("PATH");
	if (path)
	{
		path_copy = _strdup(path);
		len = _strlen(command);
		path_token = _strtok(path_copy, ":");
		while (path_token != NULL)
		{
			dir_len = _strlen(path_token);
			fpath = malloc(len + dir_len + 2);
			if (fpath == NULL)
			{
				free(fpath);
				return (NULL);
			}
			_strfun(fpath, path_token, command);
			if (stat(fpath, &buffer) == 0)
			{
				free(path_copy);
				return (fpath);
			}
			else
			{
				free(fpath);
				path_token = _strtok(NULL, ":");
			}
		}
		if (command[0] == '/')
		{
			free(path_copy);
			if (stat(command, &buffer) == 0)
				return (_strdup(command));
		}
		free(path_copy);
		return (NULL);
	}
	return (NULL);
}

/**
 * _strfun - function to make string processing
 * @fpath: path to cut astring
 * @path_token: cutted string at path
 * @command: The given command
 */
void _strfun(char *fpath, char *path_token, char *command)
{
	_strcpy(fpath, path_token);
	_strcat(fpath, "/");
	_strcat(fpath, command);
	_strcat(fpath, "\0");
}
