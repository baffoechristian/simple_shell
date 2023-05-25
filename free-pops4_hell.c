#include "shell.h"
#include <stdio.h>

/**
 * list_len - Calculates the length of a linked list
 * @head: Pointer to the head node of the list
 *
 * Return: The number of nodes in the list
 */
size_t list_len(list_s *head)
{
	size_t count = 0;
	list_s *current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return (count);
}

/**
 * add_node - Adds a new node at the beginning of a linked list
 * @head: Pointer to the head node of the list
 * @ptr: The pointer data to be stored in the new node
 *
 * Return: Pointer to the new head node of the list
 */
list_s *add_node(list_s **head, char *ptr)
{
	list_s *new_node = NULL;

	new_node = do_mem(sizeof(list_s), NULL);
	if (new_node == NULL)
		return (NULL);

	new_node->ptr = ptr;
	new_node->next = *head;

	*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Adds a new node at the end of a linked list
 * @head: Pointer to the head node of the list
 * @ptr: The pointer data to be stored in the new node
 *
 * Return: Pointer to the new head node of the list
 */
list_s *add_node_end(list_s **head, char *ptr)
{
	list_s *new_node = NULL, *current = *head;

	new_node = do_mem(sizeof(list_s), NULL);
	if (new_node == NULL)
		return (NULL);

	new_node->ptr = ptr;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	while (current->next != NULL)
		current = current->next;

	current->next = new_node;

	return (new_node);
}

/**
 * free_list - Frees a linked list
 * @head: Pointer to the head node of the list
 */
void free_list(list_s *head)
{
	list_s *current = head, *next_node = NULL;

	while (current != NULL)
	{
		next_node = current->next;
		do_mem(0, current);
		current = next_node;
	}
}
