#include "shell.h"

/**
 * add_env_node - add a new node in the linked list env
 *
 * @head: the first node of the linked list
 * @name: The name of the variable in the new node
 * @value: The value of the new node
 *
 * Return: the new node
 */
env_t *add_env_node(env_t *head, char *name, char *value)
{
	env_t *new;

	new = allocate_node_env(name, value, NULL);

	if (head != NULL)
	{
		while (head->next != NULL)
			head = head->next;

		head->next = new;
	}

	return (new);
}

/**
 * allocate_node_env - Allocate a new node for the linked list env
 *
 * @value: Value of the env node
 * @name: The name of the variable in the new node
 * @next: The next node
 *
 * Return: The new node or null if malloc failled
 */
env_t *allocate_node_env(char *name, char *value, env_t *next)
{
	env_t *new;

	new = (env_t *)malloc(sizeof(env_t));

	if (new == NULL)
		return (NULL);

	new->name = name;
	new->value = value;
	new->next = next;

	return (new);
}

/**
 * free_linked_env - Free the linked list env
 *
 * @head: The first node of the linked list
 */
void free_linked_env(env_t *head)
{
	env_t *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

/**
 * create_env_variable - Create the linked list variable
 * env using the environ
 *
 * Return: env
 */
env_t *create_env_variable(void)
{
	char *name, *value;
	env_t *env = NULL;
	int j = 0;

	while (environ[j] != NULL)
	{
		name = strtok(environ[j], "=");
		value = strtok(NULL, "=");

		if (j == 0)
			env = add_env_node(env, name, value);
		else
			add_env_node(env, name, value);

		j++;
	}

	return (env);
}
