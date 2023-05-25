#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
  * read_textfile - reads a text file and returns its contents as a string
  * @filename: name of the file to read
  * Return: pointer to the allocated buffer containing the file contents,
  *         or NULL if unsuccessful
  */
char *read_textfile(char *filename)
{
	char *buffer;
	int fd;
	ssize_t bytes_read;

	if (!filename)
		return (NULL);

	buffer = malloc(4096 * sizeof(char));
	if (buffer == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		free(buffer);
		exit(EXIT_FAILURE);
	}

	bytes_read = read(fd, buffer, 4096);
	if (bytes_read < 0)
	{
		perror("read");
		free(buffer);
		close(fd);
		exit(EXIT_FAILURE);
	}

	close(fd);

	return (buffer);
}

