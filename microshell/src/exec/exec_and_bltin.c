/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/11/20 15:27:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_executable(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
		return (false);
	return (true);
}

void	execve_command(t_cmd_data *until_redirection, char **envp)
{
	if (execve(until_redirection->path, until_redirection->cmd, envp) == -1)
	{
		ft_putstr_fd(until_redirection->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	exit(127);
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
	exit(*end_status);
}
