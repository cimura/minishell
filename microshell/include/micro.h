#ifndef MICRO_H
#define MICRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../srcs/libft/include/libft.h"


// *** command ***
void  cd(char *path);
void  pwd(void);

// *** main ***
void  judge_command(char **command, char **envp);

// *** execute_command ***
bool	is_builtin(char **command);
void	do_builtin(char **command);
void	execute_command(char **command, char **envp);
void  do_command(char **command, char **envp);

char	*get_exec_path(char **paths, char **command, char **envp);
char	**setup_paths(char *envp[]);

// *** error ***
void	specific_error(char *command);
void	by_path(char *command);
void	error_exit(const char *message);


// *** redirect ***
void	redirect(char *line, char **envp);

#endif
