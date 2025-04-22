#ifndef SSHELL_H
#define SSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

void _prompt(void);
int is_spaces(char *input);
void remove_tabs(char *input);
char **parsing(char *input);
char *get_path(char *command);
char *_getenv(const char *path);
int execute_command(char **args, char *file_name, int line_number);
void free_args(char **args);

#endif
