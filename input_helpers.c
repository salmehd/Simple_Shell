/*
 * MAin: input_helpers.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
 * get_args - function that get cmd from stdd input
 * @line:  buffer to save cmd
 * @exe_ret: return value of last cmd executed
 * Return: NULL if there's error, else pointer to stored cmd.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t set;
	char *prompt = "$ ";

	if (line)
		free(line);

	set = _getline(&line, &n, STDIN_FILENO);
	if (set == -1)
		return (NULL);
	if (set == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[set - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, set);

	return (line);
}

/**
 * call_args - function that partitions operators from cmmd and calls them
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: return value of last executed cmmnd.
 * Return:  return value of the last executed cmmd
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int ret, sign;

	if (!args[0])
		return (*exe_ret);
	for (sign = 0; args[sign]; sign++)
	{
		if (_strncmp(args[sign], "||", 2) == 0)
		{
			free(args[sign]);
			args[sign] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++sign];
				sign = 0;
			}
			else
			{
				for (sign++; args[sign]; sign++)
					free(args[sign]);
				return (ret);
			}
		}
		else if (_strncmp(args[sign], "&&", 2) == 0)
		{
			free(args[sign]);
			args[sign] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++sign];
				sign = 0;
			}
			else
			{
				for (sign++; args[sign]; sign++)
					free(args[sign]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - function to calls the execution of command
 * @args:  array of arguments
 * @front:  double pointer to beginning of args.
 * @exe_ret: return of last executed command
 * Return:  return value of last executed cmd
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, j;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (j = 0; args[j]; j++)
		free(args[j]);

	return (ret);
}

/**
 * handle_args - function that gets, calls, and runs the execution of cmd
 * @exe_ret: return value last executed cmd
 * Return: input cant tokenized -1, if its read end of file - END_OF_FILE (-2),
 * or exit value of last executed cmd
 */
int handle_args(int *exe_ret)
{
	int ret = 0, sign;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (sign = 0; args[sign]; sign++)
	{
		if (_strncmp(args[sign], ";", 1) == 0)
		{
			free(args[sign]);
			args[sign] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++sign];
			sign = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - function that checks for leading ';', ';;', '&&', or '||'
 * @args:  tokenized cmd arguments
 * Return: 0 at success, or 2 if placed at invalid place ';', '&&', or '||'
 */
int check_args(char **args)
{
	size_t i;
	char *curr, *nxt;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (create_error(&args[i], 2));
			nxt = args[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
