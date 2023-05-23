/*
 * main: env_builtins.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - function to prints the current environment.
 * @args:  array of arguments passed to the shell.
 * @front:  double pointer to the beginning of args
 * Return: If an error -1, 0 at sucsess
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int sign;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (sign = 0; environ[sign]; sign++)
	{
		write(STDOUT_FILENO, environ[sign], _strlen(environ[sign]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - function that changes or adds an envr variable to the PATH
 * @args:  array of arguments passed to the shell.
 * @front:  double pointer to the beginning of args
 * Return: If error -1, 0 at success
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int sign;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (sign = 0; environ[sign]; sign++)
		new_environ[sign] = environ[sign];

	free(environ);
	environ = new_environ;
	environ[sign] = new_value;
	environ[sign + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - function that deletes an envr variable from the PATH
 * @args:  array of arguments passed to the shell.
 * @front:  double pointer to the beginning of args.
 * Return: If error -1, 0 at success
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int sign, sign2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (sign = 0, sign2 = 0; environ[sign]; sign++)
	{
		if (*env_var == environ[sign])
		{
			free(*env_var);
			continue;
		}
		new_environ[sign2] = environ[sign];
		sign2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
