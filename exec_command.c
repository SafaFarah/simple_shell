#include "main.h"

/**
 * execve_cmd - function that executes a command
 * @argv: NULL terminated array of strings
 *
 * Return: 1 on success, or 0 on failure
 */
int execve_cmd(char **argv)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (0);
    }
    if (pid == 0)
    {
        if (execve(argv[0], argv, NULL) == -1)
        {
            perror(argv[0]);
            exit(2);
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            return (WEXITSTATUS(status));
        }
    }
    return (0);
}
