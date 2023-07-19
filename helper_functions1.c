#include "main.h"

/**
 * _strdup - duiplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	for (len++; len--;)
		dup[len] = *--str;
	return (dup);
}

/**
 * _strlen -  a function that returns the length of a string.
 *@s: char pointer
 *
 * Return: the length of a string
 */
int _strlen(char *s)
{
	int count = 0;
	int i = 0;

	while (*(s + i) != '\0')
	{
		i++;
		count++;
	}
	return (count);
}


/**
 * _strcpy - Write a function that copies the string pointed
 * @dest: string pointer
 * @src: steing pointer
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	int count = 0;
	int j;

	while (*(src + i) != '\0')
	{
		i++;
		count++;
	}
	for (j = 0 ; j <= count; j++)
	{
		dest[j] = src[j];
	}
	return (dest);
}


/**
 * *_strcat - a function that concatenates two strings.
 * @dest: string
 *@src: string
 *
 * Return: string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int count = 0;
	int j = 0;
	int length = 0;
	int k;
	int l = 0;


	while (*(dest + i) != '\0')
	{
		i++;
		count++;
	}
	while (*(src + j) != '\0')
	{
		j++;
		length++;
	}
	for (k = count; k < (count + length); k++)
	{
		dest[k] = src[l];
		l++;
	}
	dest[k] = '\0';
	return (dest);
}
