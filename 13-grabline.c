#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
 * else_handle_input - if buffer does not include \n or EOF
 * @lineptr: pointer to the buffer where the input is stored
 * @stream: the input stream
 * @input: buffer
 * @filled: size of buffer
 * Return: _getline function
 */
ssize_t else_handle_input(char *lineptr, int stream, char *input, int filled)
{
	int red;
	char hold;

	if (filled == 4096)
	{
	red = 1;
	while (red && hold != '\n')
	{
		hold = 0;
		red = read(stream, &hold, 1);
	}
	input[4095] = '\n';
	return (_getline(lineptr, stream));
	}
	else
	{
		red = read(stream, input + filled, 4096 - filled);
		if (red < (4096 - filled))
			input[filled + red] = '\n';
		filled = filled + red + 1;
		return (_getline(lineptr, stream));
	}
}

/**
 * _getline - reads a line of input from a stream
 * @lineptr: pointer to the buffer where the input is stored
 * @stream: the input stream
 * Return: the number of characters read, or -1 on error
 */
ssize_t _getline(char *lineptr, int stream)
{
	static char input[4096];
	static int filled;
	int newline_index = -1, i = 0, red = 0;
	ssize_t ret = 0;

	if (!filled)
	{
		while ((red = read(stream, input, 4096)) < 0)
		{
			perror("Read Error\n");
			return (-1);
		}
		filled = red;
		if (!red)
			return (0);
	}

	newline_index = has_newline(input);
	if (newline_index != -1)
	{
		for (i = 0; i <= newline_index; i++)
			lineptr[i] = input[i];
		ret = newline_index;
		if (input[ret] == '\n')
			ret = ret + 1;
		shiftbuffer(input, newline_index + 1, filled);
		filled = filled - ret;
		return (ret);
	}
	else
		else_handle_input(lineptr, stream, input, filled);
	return (-1);
}
