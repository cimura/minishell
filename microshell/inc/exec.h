/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/02 13:39:03 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "parser.h"
# include "env_lst.h"

typedef struct s_cmd_data
{
	char	*path;
	char	**cmd;
}	t_cmd_data;

typedef struct s_file_descripter
{
	int	pure_stdin;
	int	pure_stdout;
	int	prev_out;
	int	prev_in;
	int	now_in;
	int	now_out;
}	t_file_descripter;

// *** command_executor.c ***
int			executor(t_token *token, t_env *env_lst, int *end_status);

// *** command_executor_util.c ***
void		close_purefd(t_file_descripter fd);
void		initialize_fd(t_file_descripter *fd);
int			token_lstsize(t_token *token);
void		wait_all_commands(t_token *head, int *end_status);

// *** commands.c ***
int			first_command(t_token *token, t_env *env_lst,
				t_file_descripter *fd, int *end_status);
int			middle_command(t_token *token, t_env *env_lst,
				t_file_descripter *fd, int *end_status);
int			last_command(t_token *token, t_env *env_lst,
				t_file_descripter *fd, int *end_status);
int			run_command_with_redirect(t_token *token, t_env *env_lst,
				t_file_descripter *fd, int *end_status);

// *** register_cmd_data.c ***
t_cmd_data	*register_cmd_data(t_token *token, t_env *env_lst);

// *** redirect.c ***
int			redirect(t_token *token, t_env *env_lst,
				t_file_descripter fd, int *end_status);

// *** heredoc.c ***
int			here_doc(char *eof, t_env *env_lst,
				t_file_descripter fd, int *end_status);

// *** exec_and_bltin.c ***
bool		is_executable(char **cmd);
bool		is_builtin(char **cmd);
void		execute_external_command(t_cmd_data *until_redirection,
				t_file_descripter fd, int *end_status, char **envp);
void		execve_command(t_cmd_data *until_redirection,
				int *end_status, char **envp);
void		execute_builtin_command(char **cmd, t_env *env_lst,
				t_file_descripter fd, int *end_status);

// *** env_lst_to_array.c ***
char		**env_lst_to_array(t_env *env_lst);

// *** utils.c ***
void		free_cmd_data(t_cmd_data *data);

#endif
