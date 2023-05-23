/*
 * Main: helper.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */

void free_args(char **args, char **front)
{
	size_t j;

	for (j = 0; args[j] || args[j + 1]; j++)
		free(args[j]);

	free(front);
}

/**
 * get_pid - function to gets the current process ID.
 * Return: The current process ID or NULL on failure.
 */

char *get_pid(void)
{
	size_t j = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[j] != ' ')
		j++;
	buffer[j] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - function to gets the value corresponding to variable
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 * Return: If no variable - an empty string or value of environment variable
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		tmp = *var_addr;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replacement = malloc(_strlen(tmp) + 1);
		if (replacement)
			_strcpy(replacement, tmp);
	}

	return (replacement);
}

/**
 * variable_replacement - function that handles variable replacement.
 * @line:  double pointer containing the command and arguments.
 * @exe_ret:  pointer return value of the last executed command
 */

void variable_replacement(char **line, int *exe_ret)
{
	int x, y = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (x = 0; old_line[x]; x++)
	{
		if (old_line[x] == '$' && old_line[x + 1] &&
				old_line[x + 1] != ' ')
		{
			if (old_line[x + 1] == '$')
			{
				replacement = get_pid();
				y = x + 2;
			}
			else if (old_line[x + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				y = x + 2;
			}
			else if (old_line[x + 1])
			{
				/* extract the variable name to search for */
				for (y = x + 1; old_line[y] &&
						old_line[y] != '$' &&
						old_line[y] != ' '; y++)
					;
				len = y - (x + 1);
				replacement = get_env_value(&old_line[x + 1], len);
			}
			new_line = malloc(x + _strlen(replacement)
					  + _strlen(&old_line[y]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, x);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[y]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			x = -1;
		}
	}
}
