/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:54:54 by cimy              #+#    #+#             */
/*   Updated: 2024/11/15 17:54:05 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_status;

// /bin/cat Makefile > out1 > out2
int count_until_redirection(char **cmdline)
{
	int count = 0;
	while (cmdline[count] != NULL)
	{
	if (ft_strncmp(cmdline[count], ">", 2) == 0
		|| ft_strncmp(cmdline[count], ">>", 3) == 0
		|| ft_strncmp(cmdline[count], "<", 2) == 0
		|| ft_strncmp(cmdline[count], "<<", 3) == 0)
		return (count);
	count++;
	}
	return (count);
}

void	print_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i++]);
	}
}

void	free_cmd_data(t_cmd_data *data)
{
	free(data->path);
	data->path = NULL;
	free_commands(data->cmd);
	free(data);
	data = NULL;
}

bool  is_builtin(char **cmd)
{
	return (ft_strncmp(cmd[0], "cd", 3) == 0 ||
			ft_strncmp(cmd[0], "echo", 5) == 0 ||
			ft_strncmp(cmd[0], "env", 4) == 0 ||
			ft_strncmp(cmd[0], "exit", 5) == 0 ||
			ft_strncmp(cmd[0], "export", 6) == 0 ||
			ft_strncmp(cmd[0], "pwd", 4) == 0 ||
			ft_strncmp(cmd[0], "unset", 6) == 0);
}

void	builtin_command(char **cmd, t_env *env_lst, t_file_descripter fd)
{
	if (fd.write_to != STDOUT_FILENO)
		dup2(fd.write_to, STDOUT_FILENO);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		g_status = cd(&cmd[1], env_lst);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		g_status = echo(&cmd[1]);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		g_status = env(env_lst);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		g_status = ft_exit(&cmd[1]);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		g_status = export(&cmd[1], env_lst);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		g_status = pwd();
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		g_status = unset(&cmd[1], env_lst);
	dup2(fd.pure_stdout, STDOUT_FILENO);
}
