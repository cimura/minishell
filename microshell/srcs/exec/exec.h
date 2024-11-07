/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/07 10:20:38 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "../lexer/lexer.h"
#include "../env/env_lst.h"
#include "../expander/expander.h"
#include "../builtin/builtin.h"

#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>

#define RESET   "\033[0m"   // リセット
#define RED     "\033[31m"  // 赤
#define GREEN   "\033[32m"  // 緑
#define YELLOW  "\033[33m"  // 黄
#define BLUE    "\033[34m"  // 青

// typedef struct s_fd
// {
//   int tmp_fd[2];
//   int in_fd;
//   int out_fd;
// } t_fd;

typedef struct s_cmd_data
{
  char  *path;
  char  **cmd;
} t_cmd_data;


// *** command_executor.c ***
void	command(t_cmd_data *until_redirection, char **envp, bool last, int fd[2]);
// void  last_command(t_token *token, char **envp);
void	execute_command_line(t_token *token, t_env *env_lst);

// *** util.c ***
int count_until_redirection(char **cmdline);
void	print_commands(char **commands);
bool  is_builtin(char **until_redirection);
void	builtin_command(char **cmd, t_env *env_lst, bool last, int fd[2]);

t_cmd_data  *redirect(t_token *token, char **envp);

// env
char	**env_lst_to_array(t_env *env_lst);

#endif