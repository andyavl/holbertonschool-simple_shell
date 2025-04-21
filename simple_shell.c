#include "sshell.h"

/**
 * parsing - parses the users input
 * @input: users input
 * Return: parsed input
 */
char **parsing(char *input)
{
	char *command, *copy;
	char **arr;
	int i = 0, cap = 0;

	/* count tokens */
	copy = malloc(strlen(input) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, input);
	command = strtok(copy, " ");
	while (command != NULL)
	{
		cap++;
		command = strtok(NULL, " ");
	}
	free(copy);
	/* allocate array of pointers */
	arr = malloc((cap + 1) * sizeof(char *));
	if (!arr)
	{
		perror("malloc error");
		return (NULL);
	}
	/* tokenize and duplicate string */
	command = strtok(input, " ");
	while (command != NULL)
	{
		arr[i++] = strdup(command);
		command = strtok(NULL, " ");
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * main - Simple UNIX command line interpreter
 * Return: 0
 */
int main(void)
{
	char *input = NULL;
	char **args = NULL;
	ssize_t get;
	size_t size = 0;

	while (1)
	{
		printf("tunishell> ");
		get = getline(&input, &size, stdin);
		if (get == -1)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';
		if (strlen(input) == 0)
			continue;
		if (strcmp(input, "exit") == 0)
			break;

		args = parsing(input);
		if (!args)
			continue;

		execute_command(args);
		free_args(args);
	}

	free(input);
	return (0);
}
