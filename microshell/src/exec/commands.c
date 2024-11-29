/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:21:00 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/29 15:02:51 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	run_command_with_redirect(t_token *token, t_env *env_lst,
						t_file_descripter *fd, int *end_status)
{
	t_cmd_data	*until_redirection;
	char		**env_array;
	int			local_status;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (1);
	local_status = redirect(token, env_lst, *fd, end_status);
	if (local_status == 1 || local_status == -1)
		return (free_ptr_array(env_array), local_status);
	until_redirection = register_cmd_data(token, env_lst);
	if (until_redirection == NULL)
		return (free_ptr_array(env_array), 1);
	if (is_builtin(until_redirection->cmd))
		builtin_command(until_redirection->cmd, env_lst, *fd, end_status);
	else if (is_executable(until_redirection->cmd))
		execve_command(until_redirection, end_status, env_array);
	free_cmd_data(until_redirection);
	free_ptr_array(env_array);
	return (0);
}

static void	connect_pipe_middle_command(int fd_previn,
	int fd_nowin, int fd_nowout)
{
	dup2(fd_previn, STDIN_FILENO);
	close(fd_previn);
	close(fd_nowin);
	dup2(fd_nowout, STDOUT_FILENO);
	close(fd_nowout);
}

int	first_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		pipe_fd[2];
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	fd->prev_in = pipe_fd[0];
	fd->prev_out = pipe_fd[1];
	pid = fork();
	token->pid = pid;
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close_purefd(*fd);
		if (run_command_with_redirect(token, env_lst, fd, end_status) == 1)
			return (1);
		exit(*end_status);
	}
	return (0);
}

int	middle_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		pipe_fd[2];
	pid_t	pid;

	close(fd->prev_out);
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	fd->now_in = pipe_fd[0];
	fd->now_out = pipe_fd[1];
	token->pid = pid;
	if (pid == 0)
	{
		connect_pipe_middle_command(fd->prev_in, fd->now_in, fd->now_out);
		close_purefd(*fd);
		if (run_command_with_redirect(token, env_lst, fd, end_status) == 1)
			return (1);
		exit(*end_status);
	}
	fd->prev_in = pipe_fd[0];
	fd->prev_out = pipe_fd[1];
	return (0);
}

int	last_command(t_token *token, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		status;
	pid_t	pid;

	close(fd->prev_out);
	status = 0;
	pid = fork();
	token->pid = pid;
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		dup2(fd->prev_in, STDIN_FILENO);
		close(fd->prev_in);
		close_purefd(*fd);
		if (run_command_with_redirect(token, env_lst, fd, end_status) == 1)
			return (1);
		exit(*end_status);
	}
	close(fd->prev_in);
	return (status);
}
