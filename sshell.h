#ifndef SSHELL_H
#define SSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

char *get_path(char *command);
char **parsing(char *input);
int execute_command(char **args);
void free_args(char **args);

#endif
