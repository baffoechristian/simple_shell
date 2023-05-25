#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * do_mem - frees all  malloc with a static record
 * @size: prints the size the malloc if 0
 * @ptr: the pointer to free if 0
 * Return: the malloc'd pointer if malloc, otherwise the result of free
 */

void *do_mem(size_t size, void *ptr)
{
	static list_t *all;
	void *ret = NULL;
	int x = 0, len = 0;

	if (size)
	{
		ret = malloc(size);
		if (!ret)
			do_exit(2, "malloc failed", EXIT_FAILURE);
		for (x = 0; (unsigned int)x < size; x++)
			((char *)ret)[x] = 0;
		__add_node_end(&all, ret);
		return (ret);
	}
	else if (ptr)
	{
		len = __list_len(all);
		for (x = 0; x < len; x++)
		{
			if (__get_node_at_index(all, x)->ptr == ptr)
			{
				__delete_node_at_index(&all, x);
				break;
			}
		}
		free(ptr);
		return (NULL);
	}
	else
	{
	__free_list_full(all);
	return (NULL);
	}
	return (NULL);
}

/**
 * do_exit - custom exit with error message.
 * @fd: the file descriptor to write the message
 * @msg: the message to print custom exit
 * @code: the numerical exit code
 */

void do_exit(int fd, char *msg, int code)
{
	if (*msg)
	{
	write(fd, msg, _strlen(msg));
	}
	do_mem(0, NULL);

	exit(code);
}
