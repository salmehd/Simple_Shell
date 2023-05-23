/*
 * Main: builtin.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Builtin command to either prints all aliases
 * @args:  array of arguments
 * @front:  double pointer to the beginning of args
 * Return: error -1, 0 at success
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp = aliases;
	int i, retrn = 0;
	char *value;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (retrn);
	}
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (tmp)
			{
				if (_strcmp(args[i], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				retrn = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (retrn);
}

/**
 * set_alias -  either set an existing alias 'name' with a new value
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int len, x, y;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (x = 0, y = 0; value[x]; x++)
	{
		if (value[x] != '\'' && value[x] != '"')
			new_value[y++] = value[x];
	}
	new_value[y] = '\0';
	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - find arguments and replace any matching alias
 * @args: 2D pointer to the arguments
 * Return: 2D pointer to the arguments
 */
char **replace_aliases(char **args)
{
	alias_t *tmp;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[i], tmp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, tmp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}

