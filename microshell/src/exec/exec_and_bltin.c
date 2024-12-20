/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_bltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/12/13 12:45:17 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handler.h"
#include "builtin.h"
#include "utils.h"

bool	is_executable(t_cmd_data *until_redirection, t_env *env_lst,
			int *end_status)
{
	int	tmp_status;

	if (until_redirection->cmd == NULL || until_redirection->cmd[0] == NULL)
		return (false);
	if (is_envnode_exist(env_lst, "PATH")
		&& access(until_redirection->cmd[0], F_OK) != 0
		&& until_redirection->path == NULL
		&& ft_strchr(until_redirection->cmd[0], '/') == NULL)
	{
		print_error_msg_non_shellname(until_redirection->cmd[0],
			"command not found");
		*end_status = 127;
		return (false);
	}
	tmp_status = check_permission(until_redirection->cmd);
	if (tmp_status != 0)
	{
		*end_status = tmp_status;
		return (false);
	}
	return (true);
}

bool	is_builtin(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
		return (false);
	return (ft_strncmp(cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd[0], "echo", 5) == 0
		|| ft_strncmp(cmd[0], "env", 4) == 0
		|| ft_strncmp(cmd[0], "exit", 5) == 0
		|| ft_strncmp(cmd[0], "export", 7) == 0
		|| ft_strncmp(cmd[0], "pwd", 4) == 0
		|| ft_strncmp(cmd[0], "unset", 6) == 0);
}

void	execute_external_command(t_cmd_data *until_redirection,
		t_file_descripter fd, int *end_status, char **envp)
{
	pid_t	pid;

	ft_child_signal();
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		execve_command(until_redirection, fd, end_status, envp);
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

void	execve_command(t_cmd_data *until_redirection,
		t_file_descripter fd, int *end_status, char **envp)
{
	char	*err_msg;

	close_purefd(fd);
	if (execve(until_redirection->path,
			until_redirection->cmd, envp) == -1)
	{
		err_msg = ft_strjoin("minishell: ", until_redirection->cmd[0]);
		if (err_msg == NULL)
			*end_status = 1;
		else
			perror(err_msg);
		free(err_msg);
	}
	*end_status = 127;
}

void	execute_builtin_command(char **cmd, t_env *env_lst,
				t_file_descripter fd, t_mobile *mobile)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		mobile->status = cd(&cmd[1], env_lst, mobile);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		mobile->status = echo(&cmd[1]);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		mobile->status = env(env_lst);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit(&cmd[1], &mobile->status, WITHPIPE);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		mobile->status = export(&cmd[1], env_lst);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		mobile->status = pwd(mobile->cwd);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		mobile->status = unset(&cmd[1], env_lst);
	if (dup2(fd.pure_stdout, STDOUT_FILENO) == -1)
		perror("dup2");
}
