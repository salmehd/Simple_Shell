/*
 * Main: str_funcs1.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - function to returns the length of a string
 * @s:  pointer to the characters string
 * Return: length of character string
 */

int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - function to copies the string pointed to by src,
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string
 * Return: Pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - function to concantenates two strings
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 * Return: Pointer to destination string.
 */

char *_strcat(char *dest, const char *src)
{
	char *desttemp;
	const char *srctemp;

	desttemp = dest;
	srctemp =  src;

	while (*desttemp != '\0')
		desttemp++;

	while (*srcttemp != '\0')
		*desttemp++ = *srctemp++;
	*desttemp = '\0';
	return (dest);
}

/**
 * _strncat - function to concantenates two strings where n number
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: n bytes to copy from src
 * Return: pointer to destination string
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
