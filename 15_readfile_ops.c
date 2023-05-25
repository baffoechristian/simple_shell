#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
  * read_textfile - reads a text file returns back
  * @filename: name of file to read to return
  * Return: return 0 if unsuccessful
  */
char *read_textfile(char *filename)
{
	char *buffer;
	int of;
	ssize_t lRead;

	if (!filename)
		return (NULL);
	buffer = do_mem(4096, NULL);
	/* open file */
	of = open(filename);
	if (of == -1)
	{
	do_mem(0, buffer);
	do_exit(2, _strcat("Can't open ", filename), 127);
	}

	lRead = read(of, buffer, 4096);
	if (lRead < 1)
	{
	do_mem(0, buffer);
	close(of);
		return (NULL);
	}

	close(of);

	return (buffer);
}
