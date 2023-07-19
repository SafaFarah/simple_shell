#include "main.h"
/**
 * parsing_cmd -  Parsing commands typed into the shell
 * @buff: The address of the buffer holding command
 * @buff_copy: copy of the buffer holding command
 *
 * Return: array of strings holds commands
 */
char **parsing_cmd(char *buff, char *buff_copy)
{
	const char *s = " \n";
	int token_count = 0;
	char *token;
	int i;
	char **argv;

	token = _strtok(buff, s);
	while (token != NULL)
	{
		token_count++;
		token = _strtok(NULL, s);
	}
	token_count++;
	argv = malloc(sizeof(char *) * token_count);
	token = _strtok(buff_copy, s);
	if (argv == NULL)
	{
		free(buff);
		for (i = 1 ; argv[i] ; i++)
			free(argv[i]);
		free(argv);
	}
	for (i = 0; i < token_count - 1; i++)
	{
		argv[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (argv[i] == NULL )
			for (i = 1 ; argv[i] ; i++)
				free(argv[i]);
		_strcpy(argv[i], token);
		token = _strtok(NULL, s);
	}
	argv[i] = NULL;
	free(buff_copy);
	return (argv);
}
