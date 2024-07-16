#include "main.h"

/**
 * my_exit - exits the shell
 * @info: info struct
 *  Return: exits with a given exit status
 */
int my_exit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = _erratoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @info: info Struct
 *
 *  Return: Always 0
 */
int _cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int _chdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("failure\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			_chdir = 
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			_chdir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		_chdir = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		_chdir = chdir(info->argv[1]);
	if (_chdir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - display information about cmd
 * @info: info Struct
 *
 *  Return: Always 0
 */
int _help(info_t *info)
{
	char **array;

	array = info->argv;
	_puts("help call works \n");
	if (0)
		_puts(*array);
	return (0);
}
