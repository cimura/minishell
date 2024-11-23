/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_bltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/11/23 15:22:34 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_executable(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
		return (false);
	return (true);
}

void	execve_command_create_process(t_cmd_data *until_redirection,
								t_file_descripter fd, int *end_status, char **envp)
{
	pid_t	pid;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		close(fd.pure_stdin);
		close(fd.pure_stdout);
		execve_command(until_redirection, end_status, envp);
		exit(*end_status);
	}
	else
	{
		waitpid(pid, end_status, 0);
		ft_signal();
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
	}
}

void	execve_command(t_cmd_data *until_redirection, int *end_status, char **envp)
{
	if (execve(until_redirection->path, until_redirection->cmd, envp) == -1)
	{
		ft_putstr_fd(until_redirection->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	*end_status = 127;
//	exit(127);
}

bool	is_builtin(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
		return (false);
	return (ft_strncmp(cmd[0], "cd", 3) == 0
		||ft_strncmp(cmd[0], "echo", 5) == 0
		||ft_strncmp(cmd[0], "env", 4) == 0
		||ft_strncmp(cmd[0], "exit", 5) == 0
		||ft_strncmp(cmd[0], "export", 6) == 0
		||ft_strncmp(cmd[0], "pwd", 4) == 0
		||ft_strncmp(cmd[0], "unset", 6) == 0);
}

void	builtin_command(char **cmd, t_env *env_lst,
				t_file_descripter fd, int *end_status)
{
	if (fd.write_to != STDOUT_FILENO)
		dup2(fd.write_to, STDOUT_FILENO);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		*end_status = cd(&cmd[1], env_lst);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		*end_status = echo(&cmd[1]);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		*end_status = env(env_lst);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		*end_status = ft_exit(&cmd[1], end_status);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		*end_status = export(&cmd[1], env_lst);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		*end_status = pwd();
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		*end_status = unset(&cmd[1], env_lst);
	dup2(fd.pure_stdout, STDOUT_FILENO);
}
