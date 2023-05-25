#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * _free - free a double char pointer and its strings
 * @list: the double char pointer to be free
 * @count: the number of single char pointers to free
 */
void _free(char **list, int count)
{
	for (; count >= 0; count--)
		do_mem(0, list[count]);
	do_mem(0, list);
}

/**
 * _strtok - split a string into a double char pointer
 * @str: the string to split
 * @delim: any characters to split the string by
 * Return: the double char pointer
 */
char **_strtok(char *str, char *delim)
{
	int i = 0, j = 0, d = 0, len = 0, counter = 0, x = 0;
	char **list = NULL;

	/* get count of words, if no words return NULL */
	while (!(counter = word_count(str, delim)))
		return (NULL);
	list = do_mem((counter + 1) * sizeof(char *), NULL);
	if (!list)
		return (NULL);
	/* tokenize str to individual words inside a double pointer*/
	for (i = 0, len = 0, counter = 0; str[i] || len;)
	{
		for (d = 0, x = 0; delim[d]; d++)
		{
			if (((str[i] == delim[d]) || (!str[i])))
			{
				x += 1;
				if (len)
				{
					list[counter] = do_mem(sizeof(char) * (len + 1), NULL);
					if (!list[counter])
					{
						_free(list, counter);
						return (NULL);
					}
					for (j = 0; len; len--, j++)
						list[counter][j] = str[i - len];
					list[counter][j] = '\0';
					counter++;
				}
			}

		}
		if (!x)
			len++;
		if (str[i])
			i++;
	}
	list[counter] = NULL;
	return (list);
}
