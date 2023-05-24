/*
 * Main: getline.c
 * Auth: Salman Ahmed and Lugardo Sulley
 */

#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 * Return:If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memm;
	char *ptr_copy, *filler;
	unsigned int sign;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memm = malloc(new_size);
		if (memm == NULL)
			return (NULL);

		return (memm);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memm = malloc(sizeof(*ptr_copy) * new_size);
	if (memm == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = memm;

	for (sign = 0; sign < old_size && sign < new_size; sign++)
		filler[sign] = *ptr_copy++;

	free(ptr);
	return (memm);
}

/**
 * assign_lineptr - function to reassigns the lineptr variable for _getline.
 * @lineptr:  buffer to store an input string.
 * @n: lineptr size
 * @buffer:  string assigned to lineptr.
 * @b: buffer size
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - function to reads input from a stream.
 * @lineptr: buffer to store the input.
 * @n: lineptr size
 * @stream: stream
 * Return:  bytes number present
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t fill;
	ssize_t ret;
	char c = 'x', *buffer;
	int j;

	if (fill == 0)
		fflush(stream);
	else
		return (-1);
	fill = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		j = read(STDIN_FILENO, &c, 1);
		if (j == -1 || (j == 0 && fill == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && fill != 0)
		{
			fill++;
			break;
		}

		if (fill >= 120)
			buffer = _realloc(buffer, fill, fill + 1);

		buffer[fill] = c;
		fill++;
	}
	buffer[fill] = '\0';

	assign_lineptr(lineptr, n, buffer, fill);

	ret = fill;
	if (j != 0)
		fill = 0;
	return (ret);
}
