#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * exec_single - exec a single cmd
 * @tokens: tokens to be executed
 * Return: 0 if unsuccessful
 */

int exec_single(char **tokens)
{
	char **builtins = NULL;
	int works = 1, i = 0, checkBuiltIn = 0;

	if (!tokens || !tokens[0])
		return (0);
	builtins = get_builtins();
	for (i = 0; builtins[i]; i++)
		if (_strcmp(builtins[i], tokens[0]) == 0)
		{
		checkBuiltIn = i + 1;
		break;
		}

	if (checkBuiltIn && tokens)
		works = exec_builtin(tokens, checkBuiltIn);
	else if (tokens)
		works = exec_nb(tokens);
	return (works);
}

/**
 * get_next_commands - gets the tokens for the next cmds
 * @tokens: tokens for current cmd segment
 * Return: 0 if unsuccessfull
 */

char **get_next_commands(char **tokens)
{
	char **extokens = NULL;
	int commandSize = 0, retSize = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);
	commandSize = sizeof_command(tokens);
	if (!(tokens[commandSize]) || !(tokens[commandSize + 1]))
		return (NULL);
	while (tokens[commandSize + 1 + retSize])
		retSize++;

	extokens = do_mem(sizeof(char *) * (retSize + 1), NULL);
	for (i = 0; i < retSize; i++)
	{
		extokens[i] = do_mem(_strlen(tokens[commandSize + 1 + i]) + 1, NULL);
		_strcpy(extokens[i], tokens[commandSize + 1 + i]);
	}
	extokens[i] = NULL;
	return (extokens);
}

/**
 * get_current_command - gets currrent command
 * @tokens: the tokens for current cmd segment
 * Return: the command up until the first occurence of && || ; or NULL
 */

char **get_current_command(char **tokens)
{
	char **extokens = NULL;
	int commandSize = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);
	commandSize = sizeof_command(tokens);
	if (!commandSize)
		return (NULL);
	extokens = do_mem(sizeof(char *) * (commandSize + 1), NULL);
	for (i = 0; i < commandSize; i++)
	{
	extokens[i] = do_mem(_strlen(tokens[i]) + 1, NULL);

	_strcpy(extokens[i], tokens[i]);
	}
	extokens[i] = NULL;

	return (extokens);
}

/**
  * execute - execute the main function
  * @tokens: command now tokenized
  * Return: int if succesful otherwise 0 if unsuccessful
  */

int execute(char **tokens)
{
	int works = 0, op = 0;
	char **head = NULL;
	char **tail = NULL;

	op = search_ops(tokens);
	head = get_current_command(tokens);
	tail = get_next_commands(tokens);

	while (1)
	{
	if (!head || !(head[0]))
		return (works);

	works = exec_single(head);

	if (op == 3 && !works)
		return (works);
	if (op == 2 && works)
		return (works);

	op = search_ops(tail);
	head = get_current_command(tail);
	tail = get_next_commands(tail);

	}
	return (1);
}
