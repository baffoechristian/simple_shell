#include "shell.h"
#include <stdio.h>

/**
 * do_env - Add or remove environment variables
 * @add: A string representing the env variable to add
 * @delete: A string representing the env variable to delete
 * Return: A pointer to the current environment after any changes
 */

char **do_env(char *add, char *delete)
{
	static list_s *my_env;
	char *tmp = NULL;
	int len = 0, i = 0, j = 0;

	/* If the environment is empty, create a new list with the 'add' variable */
	if (!my_env)
	{
		my_env = listify((char **)add);
		return (NULL);
	}

	/* If 'add' is not NULL, add the variable to the environment */
	if (add)
		add_node_end(&my_env, add);

	/* If 'delete' is not NULL, remove the variable from the environment */
	else if (delete)
	{
		len = list_len(my_env);
		for (i = 0; i < len; i++)
		{
			j = 0;
			tmp = get_node_at_index(my_env, i)->ptr;
			while (delete && tmp && delete[j] && tmp[j] != '=')
			{
				if (delete[j] != tmp[j])
					break;
				j++;
			}

			if (!(delete[j]) && tmp[j] == '=')
			{
				delete_node_at_index(&my_env, i);
				break;
			}
		}
	}
	return (arrayify(my_env));
}
