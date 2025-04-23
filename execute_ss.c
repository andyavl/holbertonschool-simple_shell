#include "sshell.h"

/**
 * execute_command - forks and executes a command
 * @args: argument array
 * @file_name: file that executes the shell
 * @line_number: some number
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args, char *file_name, int line_number)
{
	char *valid_path;
	int wstatus;
	pid_t my_pid;

	valid_path = get_path(args[0]);
	if (!valid_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", file_name, line_number, args[0]);
		return (127);
	}
	my_pid = fork();
	if (my_pid == 0)
	{
		execve(valid_path, args, environ);
		perror("execve failed");
		free(valid_path);
		exit(EXIT_FAILURE);
	}
	else if (my_pid > 0)
	{
		waitpid(my_pid, &wstatus, 0);
		free(valid_path);

		if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		else
			return (1);
	}
	else
	{
		perror("fork error");
		free(valid_path);
		return (1);
	}
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
