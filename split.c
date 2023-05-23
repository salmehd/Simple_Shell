/*
 * Main: Split.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter index marking the end
 * @str: The string to be searched.
 * @delim: The delimiter character.
 * Return: The delimiter index marking the end
 */
int token_len(char *str, char *delim)
{
	int sign = 0, len = 0;

	while (*(str + sign) && *(str + sign) != *delim)
	{
		len++;
		sign++;
	}

	return (len);
}

/**
 * count_tokens - Counts the number of delimited within string
 * @str: The string to be searched.
 * @delim: The delimiter character.
 * Return: The number of words contained within string.
 */
int count_tokens(char *str, char *delim)
{
	int sign, tokens = 0, len = 0;

	for (sign = 0; *(str + sign); sign++)
		len++;

	for (sign = 0; sign < len; sign++)
	{
		if (*(str + sign) != *delim)
		{
			tokens++;
			sign += token_len(str + sign, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line:  string.
 * @delim:  delimiter character to tokenize the string
 * Return:  pointer to an array containing the tokenized words.
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int sign = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[sign] == *delim)
			sign++;

		letters = token_len(line + sign, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (sign -= 1; sign >= 0; sign--)
				free(ptr[sign]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[sign];
			sign++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
