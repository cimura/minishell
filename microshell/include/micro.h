#ifndef MICRO_H
#define MICRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../srcs/libft/include/libft.h"


// *** command ***
void  cat(char **command, char **envp);
void  cd(char *path);
void  echo(char **command, char **envp);
void  env(char **command, char **envp);
void  ls(char **command, char **envp);
void  pwd(void);

// *** main ***
void  judge_command(char **command, char **envp);

#endif
