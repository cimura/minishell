#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../srcs/libft/libft.h"


// *** command ***
void  cat(char **command, char **envp);
void  cd(char **command, char **envp);
void  echo(char **command, char **envp);
void  env(char **command, char **envp);
void  ls(char **command, char **envp);
void  pwd(char **command, char **envp);

// *** main ***
void  judge_command(char **command, char **envp);