#include "shell.h"

/**
 * addnode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addnode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	setmemo((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * listtostrings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listtostrings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **pstrs;
	char *pstr;

	if (!head || !i)
		return (NULL);
	pstrs = malloc(sizeof(char *) * (i + 1));
	if (!pstrs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		pstr = malloc(_strlen(node->pstr) + 1);
		if (!pstr)
		{
			for (j = 0; j < i; j++)
				free(pstrs[j]);
			free(pstrs);
			return (NULL);
		}

		pstr = _strcpy(pstr, node->pstr);
		pstrs[i] = pstr;
	}
	pstrs[i] = NULL;
	return (pstrs);
}

/**
 * printliststr - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t printliststr(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * nodestartswith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodestartswith(list_t *node, char *prefix, char c)
{
	char *poi = NULL;

	while (node)
	{
		poi = starts_with(node->str, prefix);
		if (poi && ((c == -1) || (*poi == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * listfree - frees all nodes of a list from the momery
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void listfree(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
