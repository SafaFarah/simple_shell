#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>


/* Functions */
char **parsing_cmd(char *buff, char *buff_copy);
int execve_cmd(char **argv);
char *get_path(char *command);
char *_getenv(const char *name);
unsigned int d_isdelim(char c, const char *d);
char *_strtok(char *str, const char *d);

/* Helper Functions */
char *_strdup(const char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

extern char **environ;

#endif
