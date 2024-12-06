/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:21:00 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/06 17:00:37 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handler.h"
#include "utils.h"

static int	run_command_with_redirect(t_command_lst *per_pipe, t_env *env_lst,
						t_file_descripter *fd, int *end_status)
{
	t_cmd_data	*until_redirection;
	char		**env_array;
	int			local_status;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (close_purefd(*fd), 1);
	local_status = redirect(per_pipe, env_lst, *fd, end_status);
	if (local_status != 0)
		return (free_ptr_array(env_array), local_status);
	until_redirection = register_cmd_data(per_pipe, env_lst, end_status);
	if (until_redirection == NULL)
		return (free_ptr_array(env_array), close_purefd(*fd), *end_status);
	if (is_builtin(until_redirection->cmd))
		execute_builtin_command(until_redirection->cmd,
			env_lst, *fd, end_status);
	else if (is_executable(until_redirection, end_status))
		execve_command(until_redirection, end_status, env_array);
	free_cmd_data(until_redirection);
	free_ptr_array(env_array);
	return (0);
}

static void	connect_pipe_middle_command(t_file_descripter *fd)
{
	dup2(fd->prev_in, STDIN_FILENO);
	close(fd->prev_in);
	close(fd->now_in);
	dup2(fd->now_out, STDOUT_FILENO);
	close(fd->now_out);
}

int	first_command(t_command_lst *per_pipe,
	t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_child_signal();
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	fd->prev_in = pipe_fd[0];
	fd->prev_out = pipe_fd[1];
	pid = fork();
	per_pipe->pid = pid;
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close_purefd(*fd);
		if (run_command_with_redirect(per_pipe, env_lst, fd, end_status) == 1)
			return (1);
		exit(*end_status);
	}
	return (0);
}

int	middle_command(t_command_lst *per_pipe,
	t_env *env_lst, t_file_descripter *fd,
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
	per_pipe->pid = pid;
	if (pid == 0)
	{
		connect_pipe_middle_command(fd);
		close_purefd(*fd);
		if (run_command_with_redirect(per_pipe, env_lst, fd, end_status) == 1)
			return (1);
		exit(*end_status);
	}
	close(fd->prev_in);
	fd->prev_in = pipe_fd[0];
	fd->prev_out = pipe_fd[1];
	return (0);
}

int	last_command(t_command_lst *per_pipe, t_env *env_lst, t_file_descripter *fd,
	int *end_status)
{
	int		status;
	pid_t	pid;

	close(fd->prev_out);
	status = 0;
	pid = fork();
	per_pipe->pid = pid;
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		dup2(fd->prev_in, STDIN_FILENO);
		close(fd->prev_in);
		dup2(fd->pure_stdout, STDOUT_FILENO);
		close_purefd(*fd);
		if (run_command_with_redirect(per_pipe, env_lst, fd, end_status) == 1)
			return (1);
		exit(*end_status);
	}
	close(fd->prev_in);
	return (status);
}
