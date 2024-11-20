/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/20 14:59:44 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "lexer.h"
# include "env_lst.h"
# include "expander.h"
# include "builtin.h"
# include "signal_handler.h"
# include "util.h"

# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# define RESET   "\033[0m"   // リセット
# define RED     "\033[31m"  // 赤
# define GREEN   "\033[32m"  // 緑
# define YELLOW  "\033[33m"  // 黄
# define BLUE    "\033[34m"  // 青

// typedef struct s_fd
// {
//   int tmp_fd[2];
//   int in_fd;
//   int out_fd;
// } t_fd;

typedef struct s_cmd_data
{
	char	*path;
	char	**cmd;
}	t_cmd_data;

typedef struct	s_file_descripter
{
	int	pure_stdin;
	int	pure_stdout;
	int	read_from;
	int	write_to;
}	t_file_descripter;


// *** command_executor.c ***
void	execve_command(t_cmd_data *until_redirection, char **envp, t_file_descripter fd,
			int *end_status);
int		execute_command_line(t_token *token, t_env *env_lst, int *end_status);

// *** util.c ***
int 	count_until_redirection(char **cmdline);
void	print_commands(char **commands);
void	free_cmd_data(t_cmd_data *data);
bool  is_builtin(char **cmd);
void	builtin_command(char **cmd, t_env *env_lst, t_file_descripter fd, int *end_status);

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe, int end_status);

// *** helper.c ***
t_cmd_data	*register_cmd_data(t_token *token, t_env *env_lst);
int  		redirect(t_token *token, t_env *env_lst, t_file_descripter fd, int end_status);

// *** env/env_lst.c ***
char	**env_lst_to_array(t_env *env_lst);

#endif
