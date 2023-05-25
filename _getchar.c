#include "stdio.h"
#include <unistd.h>

/**
 * _getchar - get a character from standard input
 *
 * Return: integer value of the character or EOF
 */
int _getchar(void)
{
	char c;

	return (read(STDIN_FILENO, &c, 1) == 1 ? (unsigned char)c : EOF);
}
