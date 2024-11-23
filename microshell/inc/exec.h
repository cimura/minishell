/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/23 15:16:57 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "lexer.h"
# include "env_lst.h"
# include "expander.h"
# include "builtin.h"
# include "signal_handler.h"
# include "utils.h"

# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# define RESET   "\033[0m"   // リセット
# define RED     "\033[31m"  // 赤
# define GREEN   "\033[32m"  // 緑
# define YELLOW  "\033[33m"  // 黄
# define BLUE    "\033[34m"  // 青

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
int		execute_command_line(t_token *token, t_env *env_lst, int *end_status);

// *** register_cmd_data.c ***
t_cmd_data	*register_cmd_data(t_token *token, t_env *env_lst);

// *** redirect.c ***
int		redirect(t_token *token, t_env *env_lst,
			t_file_descripter fd, int *end_status);

// *** heredoc.c ***
int		here_doc(char *eof, t_env *env_lst,
			t_file_descripter fd, int end_status);

// *** exec_and_bltin.c ***
bool	is_executable(char **cmd);
void	execve_command_create_process(t_cmd_data *until_redirection,
			t_file_descripter fd, int *end_status, char **envp);
void	execve_command(t_cmd_data *until_redirection, int *end_status, char **envp);
bool	is_builtin(char **cmd);
void	builtin_command(char **cmd, t_env *env_lst, t_file_descripter fd, int *end_status);

// *** env_lst_to_array.c ***
char	**env_lst_to_array(t_env *env_lst);

// *** utils.c ***
void	print_commands(char **commands);
void	free_cmd_data(t_cmd_data *data);

#endif
