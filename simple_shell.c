#include "sshell.h"

/**
 * parsing - parses the users input
 * @input: users input
 * Return: parsed input
 */
char **parsing(char *input)
{
	char *command, *copy = malloc(strlen(input + 1));
	char **arr;
	int i = 0, cap = 0;

	strcpy(copy, input);
	command = strtok(copy, " ");

	while (command != NULL)
	{
		cap++;
		command = strtok(NULL, " ");
	}
	free(copy);
	command = strtok(input, " ");
	arr = malloc(cap + 1 * sizeof(char *));
	if (!arr)
	{
		perror("malloc error");
		return (NULL);
	}
	while (command != NULL)
	{
		arr[i++] = command;
		command = strtok(NULL, " ");
	}
	if (arr != NULL)
		arr[i] = NULL;
	return (arr);
}

/**
 * main - Simple UNIX command line interpreter
 * Return: 0
 */
int main(void)
{
	char *valid_path, *input = NULL;
	char **arr = NULL;
	ssize_t get;
	size_t size = 0;
	pid_t my_pid;

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
		arr = parsing(input);
		if (!arr)
			continue;
		valid_path = get_path(arr[0]);
		if (valid_path == NULL)
			continue;
		my_pid = fork();
		if (my_pid == 0)
			execve(valid_path, arr, environ);
		else if (my_pid > 0)
			waitpid(my_pid, NULL, 0);
		else
			perror("fork error");
		free(arr);
	}
	free(input);
	return (0);
}
