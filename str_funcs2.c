/*
 * Main: str_funcs2.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - function to locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 * Return: NULL if c not found or a pointer to the first occurence
 */
char *_strchr(char *s, char c)
{
	int sign;

	for (sign = 0; s[sign]; sign++)
	{
		if (s[sign] == c)
			return (s + sign);
	}

	return (NULL);
}

/**
 * _strspn - functions to gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int sign;

	while (*s)
	{
		for (sign = 0; accept[sign]; sign++)
		{
			if (*s == accept[sign])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - function to compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 * Return: Positive byte if s1 > s2, 0 if s1 = s2, Negative byte if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - functionto compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n:  first n bytes of the strings to compare.
 * Return: < 0 if s1 is short than s2,0 if s1&s2 match,> 0if s1 is long.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
