/*
 * Main: helpers_2.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - function to partitions a line read from stdd input as needed
 * @line:  pointer to a line read from standard input.
 * @read: length of line.
 */

void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next;
	size_t x, y;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	y = 0;
	old_line = *line;
	for (x = 0; old_line[x]; x++)
	{
		current = old_line[x];
		next = old_line[x + 1];
		if (x != 0)
		{
			previous = old_line[x - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[y++] = ' ';
					new_line[y++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[y++] = ';';
					new_line[y++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[y++] = ' ';
				new_line[y++] = ';';
				if (next != ' ')
					new_line[y++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[y++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[y++] = '&';
					new_line[y++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[y++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[y++] = '|';
					new_line[y++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (x != 0 && old_line[x - 1] != ' ')
				new_line[y++] = ' ';
			new_line[y++] = ';';
			if (next != ' ' && next != ';')
				new_line[y++] = ' ';
			continue;
		}
		new_line[y++] = old_line[x];
	}
	new_line[y] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - function to get new length line partitioned
 * @line:  line to check
 * Return:  new length of the line
 */

ssize_t get_new_len(char *line)
{
	size_t x;
	ssize_t new_len = 0;
	char current, nxt;

	for (x = 0; line[x]; x++)
	{
		current = line[x];
		nxt = line[x + 1];
		if (current == '#')
		{
			if (x == 0 || line[x - 1] == ' ')
			{
				line[x] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (current == ';')
			{
				if (nxt == ';' && line[x - 1] != ' ' && line[x - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[x - 1] == ';' && nxt != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[x - 1] != ' ')
					new_len++;
				if (nxt != ' ')
					new_len++;
			}
			else
				logical_ops(&line[x], &new_len);
		}
		else if (current == ';')
		{
			if (x != 0 && line[x - 1] != ' ')
				new_len++;
			if (nxt != ' ' && nxt != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - function that checks a line for logical operators "||" or "&&"
 * @line: A pointer to the character to check in the line
 * @new_len: Pointer to new_len in get_new_len function
 */

void logical_ops(char *line, ssize_t *new_len)
{
	char prev, current, nxt;

	prev = *(line - 1);
	current = *line;
	nxt = *(line + 1);

	if (current == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && nxt != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && nxt != ' ')
			(*new_len)++;
	}
}
