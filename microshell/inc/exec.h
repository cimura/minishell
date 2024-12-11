/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:28:31 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/10 15:43:32 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

typedef struct s_mobile
{
	int		status;
	char	*cwd;
}	t_mobile;

// *** command_executor.c ***
int			executor(t_command_lst *per_pipe, t_env *env_lst, t_mobile *mobile);

// *** command_executor_util.c ***
void		close_purefd(t_file_descripter fd);
void		initialize_fd(t_file_descripter *fd);
int			command_lstsize(t_command_lst *per_pipe);
void		wait_all_commands(t_command_lst *head, int *end_status);
void		print_error_msg_non_shellname(char *cmd_name, char *err_msg);

// *** commands.c ***
int			first_command(t_command_lst *per_pipe, t_env *env_lst,
				t_file_descripter *fd, t_mobile *mobile);
int			middle_command(t_command_lst *per_pipe, t_env *env_lst,
				t_file_descripter *fd, t_mobile *mobile);
int			last_command(t_command_lst *per_pipe, t_env *env_lst,
				t_file_descripter *fd, t_mobile *mobile);

// *** register_cmd_data.c ***
t_cmd_data	*register_cmd_data(t_command_lst *per_pipe, t_env *env_lst,
				int *status);

// *** redirect.c ***
int			redirect(t_command_lst *per_pipe, t_env *env_lst,
				t_file_descripter fd, int *end_status);

// *** heredoc.c ***
int			here_doc(char *eof, t_env *env_lst,
				t_file_descripter fd, int *end_status);

// *** check_permission.c
int			check_permission(char **command_line);

// *** exec_and_bltin.c ***
bool		is_executable(t_cmd_data *until_redirection, t_env *env_lst,
				int *end_status);
bool		is_builtin(char **cmd);
void		execute_external_command(t_cmd_data *until_redirection,
				t_file_descripter fd, int *end_status, char **envp);
void		execve_command(t_cmd_data *until_redirection,
				t_file_descripter fd, int *end_status, char **envp);
void		execute_builtin_command(char **cmd, t_env *env_lst,
				t_file_descripter fd, t_mobile *mobile);

#endif
