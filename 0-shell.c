#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


/**
 * linum - creates line at the end of static
 * @add: add lines to static
 * Return: the line number
 */

int linum(int add)
{
	static int line;

	line = line + add;
	return (line);
}

/**
 * get_prog_name - fetches the program name
 * @name: name of the program (first exec)
 * Return: the name of the program
 */
char *get_prog_name(char *name)
{
	static char *ret;

	if (!ret)
	{
	ret = name;
	}
	return (ret);
}

/**
 * my_error - clear error printing
 * @command: leave a command message
 * @status: error to print
 * @extra: any extra text
 */
void my_error(char *command, int status, char *extra)
{
	char *name = NULL;
	char *line = NULL;
	char *msg = NULL;

	name = get_prog_name(NULL);
	line = _itoa(linum(0));
	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, line, _strlen(line));

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);

	switch (status)
	{
	case 2:
		msg = "not found";
		break;
	case 126:
		msg = "Permission denied";
		break;
	case 127:
		msg = "not found";
		break;
	case 9000:
		msg = "Illegal number: ";
		break;
	default:
		msg = "Unknown error occured.";
	}
	write(STDERR_FILENO, msg, _strlen(msg));

	if (extra)
		write(STDERR_FILENO, extra, _strlen(extra));

	write(STDERR_FILENO, "\n", 1);
}


/**
  * main - simple_shell
  * @argc: number of arguments
  * @argv: list of arguments
  * @envp: environments printed
  * Return: 0 if successful
  */
int main(int argc, char **argv, char **envp)
{
	char *filename = NULL;

	get_prog_name(argv[0]);

	if (argc > 2)
		return (-1);

	if (argv && argv[1])
		filename = argv[1];

	signal(SIGINT, signal_handler);

	do_env((char *)envp, NULL);


	linum(1);


	main_loop(filename);

	return (0);
}
