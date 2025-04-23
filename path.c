#include "sshell.h"

/**
 * handle_env - handles the env built-in command
 * @args: the parsed command arguments
 * @shell_name: name of the shell executable (argv[0])
 * @line_number: the current input line number (argc)
 * Return: 1 if env was handled, 0 otherwise
 */
int _env_builtin(char **args, char *shell_name, int line_number)
{
	int i;

	if (strcmp(args[0], "env") == 0)
	{
		if (args[1])
		{
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
				shell_name, line_number, args[1]);
			return (127);
		}
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (0);
	}
	return (-1); /* Not an env command */
}

/**
 * _getenv - searches for key in the extern environ
 * @path: the key to read
 * Return: key value or NULL if not found
 */
char *_getenv(const char *path)
{
	int i;
	size_t len;

	if (!path || !environ)
		return (NULL);

	len = strlen(path);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], path, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}

	return (NULL);
}

/**
 * get_path - checks for the command and its path
 * @command: user command
 * Return: commands path or NULL if failed
 */
char *get_path(char *command)
{
	size_t len;
	char *path_env, *path_dup, *dir, *full_path;

	if (!command)
		return (NULL);

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env || *path_env == '\0')
		return (NULL);
	path_dup = strdup(path_env);
	if (!path_dup)
		return (NULL);
	dir = strtok(path_dup, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_dup);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_dup);
	return (NULL);
}
