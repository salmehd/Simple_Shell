/*
 * Main: environ.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment
 * Return: If error occurs - NULL, at success O/w
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int sign;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (sign = 0; environ[sign]; sign++)
	{
		new_environ[sign] = malloc(_strlen(environ[sign]) + 1);

		if (!new_environ[sign])
		{
			for (sign--; sign >= 0; sign--)
				free(new_environ[sign]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[sign], environ[sign]);
	}
	new_environ[sign] = NULL;

	return (new_environ);
}

/**
 * free_env - function to frees the the environment copy.
 */
void free_env(void)
{
	int sign;

	for (sign = 0; environ[sign]; sign++)
		free(environ[sign]);
	free(environ);
}

/**
 * _getenv - function to gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 * Return: if no environment variable NULL or a pointer to environment variable
 */
char **_getenv(const char *var)
{
	int sign, len;

	len = _strlen(var);
	for (sign = 0; environ[sign]; sign++)
	{
		if (_strncmp(var, environ[sign], len) == 0)
			return (&environ[sign]);
	}

	return (NULL);
}
