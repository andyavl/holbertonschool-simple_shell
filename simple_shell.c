#include "sshell.h"

/**
 * _prompt - prints prompt
 */
void _prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("notSoSimpleShell> ");
}

/**
 * is_spaces - handle input with many spaces
 * @input: user input
 * Return: 1 if spaces, else 0
 */
int is_spaces(char *input)
{
	size_t i;

	for (i = 0; input[i]; i++)
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
	}
	return (1);
}

/**
 * remove_tabs - removes tabs from input
 * @input: users input
 */
void remove_tabs(char *input)
{
	size_t i, j = 0;

	for (i = 0; input[i]; i++)
	{
		if (input[i] != '\t')
			input[j++] = input[i];
	}
	input[j] = '\0';
}

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
		_prompt();
		get = getline(&input, &size, stdin);
		if (get == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (is_spaces(input))
			continue;
		if (strlen(input) == 0)
			continue;
		if (strcmp(input, "exit") == 0)
			break;
		remove_tabs(input);
		args = parsing(input);
		if (!args)
			continue;
		if (execute_command(args) == -1)
			continue;
		free_args(args);
	}
	free(input);
	return (0);
}
