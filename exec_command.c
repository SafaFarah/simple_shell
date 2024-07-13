#include "main.h"

/**
 * execve_cmd - function that executes a command
 * @argv: NULL terminated array of strings
 *
 * Return: status of the executed command
 */
int execve_cmd(char **argv)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (127);  /* Common exit code for command not found*/
    }
    if (pid == 0)
    {
        if (execve(argv[0], argv, NULL) == -1)
        {
            perror(argv[0]);
            exit(2);  /* Exit with status 2 if execve fails*/
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            return (WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            return (128 + WTERMSIG(status));  /*Return signal number plus 128*/
        }
    }
    return (0);
}

