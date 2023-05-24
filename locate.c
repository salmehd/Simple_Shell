/*
 * Main: locate.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - function that locates a command in the path
 * @command:  command to locate.
 * Return:  full pathname or NULL
 */
char *get_location(char *command)
{
	char **path, *tmp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		tmp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!tmp)
			return (NULL);

		_strcpy(tmp, dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, command);

		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}

		dirs = dirs->next;
		free(tmp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - function that replaces colons with working direct
 * @path: The colon-separated list of directories.
 * Return: a path with any colons replaced
 */

char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - function that tokenizes a colon-separated list of directories
 * @path: The colon-separated list of directories.
 * Return:  pointer to initialized linked list
 */

list_t *get_path_dir(char *path)
{
	int sign;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (sign = 0; dirs[sign]; sign++)
	{
		if (add_node_end(&head, dirs[sign]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
