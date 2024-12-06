/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/12/06 14:08:21 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static int	ft_open(char *target, int oflag, int to_dup)
{
	int	redirect_fd;

	redirect_fd = open(target, oflag, 0644);
	if (redirect_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(target);
		return (-1);
	}
	dup2(redirect_fd, to_dup);
	close(redirect_fd);
	return (0);
}

static int	handle_redirect(t_command_lst *per_pipe, int i)
{
	if (!per_pipe->is_expanded[i]
		&& ft_strncmp(per_pipe->command_line[i], ">", 2) == 0)
	{
		if (ft_open(per_pipe->command_line[i + 1],
				O_CREAT | O_WRONLY | O_TRUNC, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (!per_pipe->is_expanded[i]
		&& ft_strncmp(per_pipe->command_line[i], ">>", 3) == 0)
	{
		if (ft_open(per_pipe->command_line[i + 1],
				O_CREAT | O_WRONLY | O_APPEND, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (!per_pipe->is_expanded[i]
		&& ft_strncmp(per_pipe->command_line[i], "<", 2) == 0)
	{
		if (ft_open(per_pipe->command_line[i + 1],
				O_RDONLY, STDIN_FILENO) == -1)
			return (-1);
	}
	return (0);
}

#define NO_SUCH_FILE 127

int	redirect(t_command_lst *per_pipe, t_env *env_lst,
			t_file_descripter fd, int *end_status)
{
	int	i;
	int	local_status;

	local_status = 0;
	i = 0;
	while (per_pipe->command_line[i] != NULL)
	{
		if (handle_redirect(per_pipe, i) == -1)
		{
			*end_status = 1;
			return (NO_SUCH_FILE);
		}
		else if (ft_strncmp(per_pipe->command_line[i], "<<", 3) == 0)
		{
			local_status = here_doc(per_pipe->command_line[i + 1],
					env_lst, fd, end_status);
			if (local_status == 1)
				return (1);
		}
		i++;
	}
	return (local_status);
}
