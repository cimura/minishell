/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:21:00 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/10 17:58:18 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handler.h"
#include "utils.h"

static int	run_command_with_redirect(t_command_lst *per_pipe, t_env *env_lst,
						t_file_descripter *fd, t_mobile *mobile)
{
	t_cmd_data	*until_redirection;
	char		**env_array;
	int			local_status;

	env_array = env_lst_to_array(env_lst);
	if (env_array == NULL)
		return (close_purefd(*fd), 1);
	local_status = redirect(per_pipe, env_lst, *fd, &mobile->status);
	if (local_status != 0)
		return (free_ptr_array(env_array), close_purefd(*fd), local_status);
	until_redirection = register_cmd_data(per_pipe, env_lst, &mobile->status);
	if (until_redirection == NULL)
		return (free_ptr_array(env_array), close_purefd(*fd), mobile->status);
	if (is_builtin(until_redirection->cmd))
		execute_builtin_command(until_redirection->cmd,
			env_lst, *fd, mobile);
	else if (is_executable(until_redirection, env_lst, &mobile->status))
		execve_command(until_redirection, &mobile->status, env_array);
	free_cmd_data(until_redirection);
	free_ptr_array(env_array);
	return (0);
}

static void	connect_pipe_middle_command(t_file_descripter *fd)
{
	if (dup2(fd->prev_in, STDIN_FILENO) == -1)
		perror("dup2");
	close(fd->prev_in);
	close(fd->now_in);
	if (dup2(fd->now_out, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd->now_out);
}

int	first_command(t_command_lst *per_pipe,
	t_env *env_lst, t_file_descripter *fd,
	t_mobile *mobile)
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
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(pipe_fd[1]);
		if (run_command_with_redirect(per_pipe, env_lst, fd, mobile) == 1)
			return (1);
		close_purefd(*fd);
		exit(mobile->status);
	}
	return (0);
}

int	middle_command(t_command_lst *per_pipe,
	t_env *env_lst, t_file_descripter *fd,
	t_mobile *mobile)
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
		if (run_command_with_redirect(per_pipe, env_lst, fd, mobile) == 1)
			return (1);
		close_purefd(*fd);
		exit(mobile->status);
	}
	close(fd->prev_in);
	fd->prev_in = pipe_fd[0];
	fd->prev_out = pipe_fd[1];
	return (0);
}

int	last_command(t_command_lst *per_pipe, t_env *env_lst, t_file_descripter *fd,
	t_mobile *mobile)
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
		if (dup2(fd->prev_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(fd->prev_in);
		if (dup2(fd->pure_stdout, STDOUT_FILENO) == -1)
			perror("dup2");
		if (run_command_with_redirect(per_pipe, env_lst, fd, mobile) == 1)
			return (1);
		close_purefd(*fd);
		exit(mobile->status);
	}
	close(fd->prev_in);
	return (status);
}
