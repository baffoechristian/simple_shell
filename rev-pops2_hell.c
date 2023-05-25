#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * free_list_full - Frees list_s and all contained pointers.
 * @head: Linked list (list_s) to be freed.
 *
 * Description: This function frees the memory allocated for a linked list
 * of type list_s, including all the pointers contained within each node.
 */
void free_list_full(list_s *head)
{
	list_s *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		do_mem(0, hold->ptr);
		do_mem(0, hold);
	}
}

/**
 * get_node_at_index - Returns the nth node of a linked list.
 * @head: Pointer to the start of the linked list.
 * @index: Index of the node to be returned.
 *
 * Return: On success, returns the nth node of the linked list.
 *         On failure or if the index is out of range, returns NULL.
 */
list_s *get_node_at_index(list_s *head, unsigned int index)
{
	unsigned int i = 0;

	for (i = 0; head; i++, head = head->next)
	{
		if (i == index)
			return (head);
	}

	return (NULL);
}

/**
 * insert_node_at_index - Inserts a new node at a given position.
 * @head: Pointer to the beginning of the linked list.
 * @idx: Index where the new node should be inserted.
 * @ptr: Value for ptr.
 *
 * Return: On success, returns the address of the new node.
 *         On failure or if the index is out of range, returns NULL.
 */
list_s *insert_node_at_index(list_s **head, unsigned int idx, char *ptr)
{
	list_s *new = NULL, *hold = *head;
	unsigned int i = 0;

	if (!idx)
	{
		new = do_mem(sizeof(list_s), NULL);
		if (!new)
			return (NULL);

		new->ptr = ptr;
		new->next = *head;

		*head = new;

		return (*head);
	}

	while (hold)
	{
		if (i == (idx - 1))
		{
			new = do_mem(sizeof(list_s), NULL);
			if (!new)
				return (NULL);

			new->ptr = ptr;
			new->next = hold->next;
			hold->next = new;
			return (new);
		}
		hold = hold->next;
		i++;
	}

	return (NULL);
}

/**
 * delete_node_at_index - Deletes a node at a given pointer
 * @head: Pointer to begin the linked list.
 * @index: Index of the node to be deleted.
 *
 * Return: On success, returns 1. On failure or if the index is out of range,
 *         returns -1.
 */
int delete_node_at_index(list_s **head, unsigned int index)
{
	list_s *hold = NULL, *delete = NULL;
	unsigned int i = 0, action = 0;

	if (!*head)
		return (-1);

	for (i = 0, hold = *head; hold && index; i++, hold = hold->next)
	{
		if (i == (index - 1))
		{
			action = 1;
			break;
		}
	}

	if (action)
	{
		delete = hold->next;
		hold->next = delete->next;
		do_mem(0, delete);
		return (1);
	}
	else if (!index && (**head).next)
	{
		delete = *head;
		*head = (*delete).next;
		do_mem(0, delete);
		return (1);
	}
	else if (!index && *head)
	{
		*head = NULL;
		do_mem(0, *head);
		return (1);
	}
	return (-1);
}
