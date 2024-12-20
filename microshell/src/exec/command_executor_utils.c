/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:02:34 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/11 13:13:35 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_purefd(t_file_descripter fd)
{
	close(fd.pure_stdin);
	close(fd.pure_stdout);
}

void	initialize_fd(t_file_descripter *fd)
{
	fd->pure_stdin = dup(STDIN_FILENO);
	fd->pure_stdout = dup(STDOUT_FILENO);
	fd->now_in = STDIN_FILENO;
	fd->now_out = STDOUT_FILENO;
}

int	command_lstsize(t_command_lst *per_pipe)
{
	int	c;

	c = 0;
	while (per_pipe != NULL)
	{
		c++;
		per_pipe = per_pipe->next;
	}
	return (c);
}

void	wait_all_commands(t_command_lst *head, int *end_status)
{
	while (head != NULL)
	{
		if (head->pid > 0)
			waitpid(head->pid, end_status, 0);
		if (WIFEXITED(*end_status))
			*end_status = WEXITSTATUS(*end_status);
		else if (WIFSIGNALED(*end_status))
			*end_status = 128 + WTERMSIG(*end_status);
		head = head->next;
	}
}

void	print_error_msg_non_shellname(char *cmd_name, char *err_msg)
{
	int	pure_stdout;

	pure_stdout = dup(STDOUT_FILENO);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		perror("dup2");
	printf("%s: %s\n", cmd_name, err_msg);
	if (dup2(pure_stdout, STDOUT_FILENO) == -1)
		perror("dup2");
	close(pure_stdout);
}
