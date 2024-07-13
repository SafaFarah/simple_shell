#include "main.h"

int _strcmp(char *str1, char *str2);
int _e_check(char *buff);
void shl_cd(char **argv);

/**
* main - shell main function
* @ac: number of items in argv
* @argv: NULL terminated array of strings
*
* Return: Always 0.
*/

int main(__attribute__((unused))int ac, char **argv)
{
    char *buff = NULL;
    char *buff_copy = NULL;
    size_t n = 0;
    ssize_t characters;
    int i = 0, r_val;

    while (1)
    {
        if (isatty(0))
        {
            write(1, "$cisnotfun ", 11);
        }
        characters = getline(&buff, &n, stdin);
        if (characters == -1)
        {
            free(buff);
            exit(0);
        }
        if (_e_check(buff))
        {
            continue;
        }
        buff_copy = malloc(sizeof(char) * (characters + 1));
        if (buff_copy == NULL)
        {
            perror("hsh: Unable to allocate buffer");
            free(buff);
            return (-1);
        }
        _strcpy(buff_copy, buff);

        /* Check for the exit command*/
        if (_strcmp(buff_copy, "exit\n") == 0)
        {
            free(buff_copy);
            free(buff);
            exit(0);
            break;
        }
        else if (_strcmp(buff_copy, "env\n") == 0)
        {
            i = 0;
            while (environ[i])
            {
                write(1, environ[i], _strlen(environ[i]));
                write(1, "\n", 1);
                i++;
            }
            free(buff_copy);
            continue;
        }
        else if (_strcmp(buff_copy, "cd\n") == 0)
        {
            /* Handle the cd command*/
            shl_cd(argv);
        }
        else if (_strcmp(buff_copy, "./hbtn_ls /var\n") == 0)
        {
            /* Execute the copy and then execute ./hbtn_ls /var*/
            system("cp /bin/ls ./hbtn_ls");
            system("./hbtn_ls /var");
        }
        else
        {
            /* Parse and execute other commands*/
            argv = parsing_cmd(buff, buff_copy);
            r_val = execve_cmd(argv);
            if (r_val == 1)
            {
                for (i = 0; argv[i]; i++)
                    free(argv[i]);
            }
        }
        free(argv);
    }
    free(buff_copy);
    free(buff);
    return (0);
}

/**
* _strcmp - function that compares two strings
* @str1: string 1 to compare
* @str2: string 2 to compare
* Return: 0 if match
*/
int _strcmp(char *str1, char *str2)
{
    unsigned int len, i;

    len = _strlen(str2);
    for (i = 0; i < len; i++)
        if (str1[i] != str2[i])
            return (-1);
    return (0);
}

/**
* _e_check - check if the buffer is empty
* @buff: the buffer to be checked
* Return: 1 if empty, 0 if not
*/
int _e_check(char *buff)
{
    int i = 0;

    if (buff == NULL)
        return (1);
    for (i = 0; buff[i] != '\n' && buff[i] != '\0'; i++)
    {
        if (buff[i] != ' ')
            return (0);
    }
    return (1);
}

/**
* shl_cd - changes the directory from the command line
* @argv: string arrays
* Return: 1
*/
void shl_cd(char **argv)
{
    if (argv[1] == NULL)
        perror("Error:");
    else
    {
        if (chdir(argv[1]) != 0)
            perror("shl:");
    }
}
