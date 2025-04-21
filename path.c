#include "sshell.h"

const char *search_path[] = {"/bin", "/usr/bin", NULL};

/**
 * get_path - checks for the command and its path
 * @command: user command
 * Return: commands path or NULL if failed
 */
char *get_path(char *command)
{
	size_t p;
	int i = 0;
	char *copy, *path;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
		{
			copy = malloc(strlen(command) + 1);
			if (copy)
				strcpy(copy, command);
			return (copy);
		}
		return (NULL);
	}
	while (search_path[i] != NULL)
	{
		p = strlen(search_path[i]) + strlen(command) + 2;
		path = malloc(p);
		if (!path)
			return (NULL);

		strcpy(path, search_path[i]);
		strcat(path, "/");
		strcat(path, command);

		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
