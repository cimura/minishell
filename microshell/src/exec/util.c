/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:54:54 by cimy              #+#    #+#             */
/*   Updated: 2024/11/20 16:37:05 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// /bin/cat Makefile > out1 > out2
int	count_until_redirection(char **cmdline)
{
	int	count;

	count = 0;
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
	pid_t	pid;
	int		status = 0;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler_child);

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (ft_strncmp(cmd[0], "cd", 3) == 0)
			status = cd(&cmd[1], env_lst);
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
			status = echo(&cmd[1]);
		else if (ft_strncmp(cmd[0], "env", 4) == 0)
			status = env(env_lst);
		else if (ft_strncmp(cmd[0], "exit", 5) == 0)
			status = ft_exit(&cmd[1], &status);
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			status = export(&cmd[1], env_lst);
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			status = pwd();
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
			status = unset(&cmd[1], env_lst);
		exit(status);
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
	dup2(fd.pure_stdout, STDOUT_FILENO);
}
