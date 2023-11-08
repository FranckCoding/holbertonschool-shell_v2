#include "shell.h"

/**
 * add_path_node - add a new node in the linked list path
 *
 * @head: the first node of the linked list
 * @value: The value of the new node
 *
 * Return: the new node
 */
path_t *add_path_node(path_t *head, char *value)
{
	path_t *new;

	new = allocate_node(value, NULL);

	if (head != NULL)
	{
		while (head->next != NULL)
			head = head->next;

		head->next = new;
	}

	return (new);
}

/**
 * allocate_node - Allocate a new node for the linked list path
 *
 * @value: Value of the node
 * @next: The next node
 *
 * Return: The new node or null if malloc failled
 */
path_t *allocate_node(char *value, path_t *next)
{
	path_t *new;

	new = malloc(sizeof(path_t));

	if (new == NULL)
		return (NULL);

	new->value = value;
	new->next = next;

	return (new);
}

/**
 * free_linked_path - Free the linked list path
 *
 * @head: The first node of the linked list
 */
void free_linked_path(path_t *head)
{
	path_t *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

/**
 * _getenv - Get an environment variable
 *
 * @name: Name of the variable we want
 * @env: The linked list of the environment variable
 * Return: The value of the variable find, or (null) if no variable
 */
char *_getenv(const char *name, env_t *env)
{
	int i = 0;

	while (env != NULL)
	{
		if (strcmp(env->name, name) == 0)
			return (env->value);

		env = env->next;
		i++;
	}

	return ("(null)");
}
