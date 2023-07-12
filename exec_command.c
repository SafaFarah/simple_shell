#include "main.h"

/**
* execve_cmd - function to execute the command.
* @argv: array of strings holds commands
* Return: return 0 in success, -1
*/
int execve_cmd(char **argv)
{
	char *command = NULL;
	char *real_command = NULL;
	int pid;
	int i;

	if (argv)
	{
		command = argv[0];
		real_command = get_path(command);
		if (real_command == NULL)
		{
			perror("Error:");
			free(real_command);
			for (i = 0; argv[i]; i++)
				free(argv[i]);
			return (0);
		}
		if (real_command != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(real_command, argv, NULL) == -1)
				{
					for (i = 1; argv[i] != NULL; i++)
						free(argv[i]);
					free(real_command);
					perror("Error");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				wait(NULL);
			}
			free(real_command);
		}
	}
	return (1);
}
