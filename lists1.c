#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t list_len(const list_t *h)

{
	size_t i = 0;
	const list_t *node = h;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	size_t i, j;
	char **strs;
	list_t *node;
	size_t len = list_len(head);
	if (len == 0)
		return (NULL);
	strs = malloc(sizeof(char *) * (len + 1));
	if (strs == NULL)
		return (NULL);
	node = head;
	for (i = 0; i < len; i++)
	{
		size_t str_len = strlen(node->str);
		strs[i] = malloc((str_len + 1) * sizeof(char));
		if (strs[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		strcpy(strs[i], node->str);
		node = node->next;
		strs[len] = NULL;
		return (strs);
}
/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list(const list_t *h)

{
	size_t i = 0;
	const list_t *node = h;

	while (node != NULL)
	{
		printf("%s\n", node->str);
		node = node->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or NULL
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)

{
	while (node != NULL)
	{
		if (strncmp(node->str, prefix, strlen(prefix)) == 0)
		{
			if (c == -1 || node->str[strlen(prefix)] == c)
				return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)

{
	size_t i = 0;
	list_t *current = head;

	while (current != NULL)
	{
		if (current == node)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}
