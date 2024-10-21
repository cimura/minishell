/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:51:37 by cimy              #+#    #+#             */
/*   Updated: 2024/10/18 17:05:18 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	clear_exit(int argc, int status)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		wait(NULL);
		i++;
	}
	exit(WEXITSTATUS(status));
}

static void	first_command(char *argv[], char *envp[], t_file *file)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(file->in, STDIN_FILENO);
		if (file->in != -1)
			execute_cmd(argv[2], envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	mid_command(char *command, char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_cmd(command, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static int	last_command(char *argv[], int argc, char *envp[], t_file *file)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	status = 0;
	if (pipe(fd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		dup2(file->out, STDOUT_FILENO);
		if (file->out != -1)
			execute_cmd(argv[argc - 2], envp);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (status);
}

void	loop_execute(char *argv[], int argc, char *envp[], t_file *file)
{
	int	i;
	int	status;

	i = 3;
	first_command(argv, envp, file);
	while (i < argc - 2)
	{
		mid_command(argv[i], envp);
		i++;
	}
	status = last_command(argv, argc, envp, file);
	clear_exit(argc, status);
}
