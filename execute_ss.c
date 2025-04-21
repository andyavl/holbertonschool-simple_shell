#include "sshell.h"

/**
 * execute_command - forks and executes a command
 * @args: argument array
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args)
{
	char *valid_path;
	pid_t my_pid;

	valid_path = get_path(args[0]);
	if (!valid_path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (-1);
	}

	my_pid = fork();
	if (my_pid == 0)
	{
		execve(valid_path, args, environ);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else if (my_pid > 0)
	{
		waitpid(my_pid, NULL, 0);
	}
	else
	{
		perror("fork error");
	}

	free(valid_path);
	return (0);
}

/**
 * free_args - frees array of argument strings
 * @args: the array to free
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}
