#include "main.h"

/**
 * main - entry point
 * @argc: count of arguments
 * @argv: list of arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	env_list(info);
	shell(info, argv);
	return (EXIT_SUCCESS);
}


/**
 * shell - main shell loop
 * @info:  info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell(info_t *info, char **argv)
{
	ssize_t r = 0;
	int ret = 0;

	while (r != -1 && ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, argv);
			ret = find_builtin(info);
			if (ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: info struct
 *
 * Return: -1 if builtin not found,or 0 success
 */
int find_builtin(info_t *info)
{
	int i, built_ret = -1;
	builtin_table builtin_tb[] = {
		{"exit", my_exit},
		{"env", _env},
		{"help", _help},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", _cd},
		{NULL, NULL}
	};

	for (i = 0; builtin_tb[i].type; i++)
		if (_strcmp(info->argv[0], builtin_tb[i].type) == 0)
		{
			info->line_count++;
			built_ret = builtin_tb[i].func(info);
			break;
		}
	return (built_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info:  info struct
 *
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, n;

	info->path = info->argv[0];
	if (info->line_flag == 1)
	{
		info->line_count++;
		info->line_flag = 0;
	}
	for (i = 0, n = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			n++;
	if (!n)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: info struct
 *
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
