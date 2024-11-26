/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:04:16 by cimy              #+#    #+#             */
/*   Updated: 2024/11/26 17:24:53 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_open(char *path, int oflag, int to_dup)
{
	int	redirect_fd;

	redirect_fd = open(path, oflag, 0644);
	if (redirect_fd == -1)
	{
		perror(path);
		return (-1);
	}
	dup2(redirect_fd, to_dup);
	close(redirect_fd);
	return (0);
}

static int	handle_redirect(char **command_line, int i, t_file_descripter fd)
{
	if (ft_strncmp(command_line[i], ">", 2) == 0)
	{
		if (ft_open(command_line[i + 1],
				O_CREAT | O_WRONLY | O_TRUNC, fd.write_to) == -1)
			return (-1);
	}
	else if (ft_strncmp(command_line[i], ">>", 3) == 0)
	{
		if (ft_open(command_line[i + 1],
				O_CREAT | O_WRONLY | O_APPEND, fd.write_to) == -1)
			return (-1);
	}
	else if (ft_strncmp(command_line[i], "<", 2) == 0)
	{
		if (ft_open(command_line[i + 1],
				O_RDONLY, fd.read_from) == -1)
			return (-1);
	}
	return (0);
}

int	redirect(t_token *token, t_env *env_lst,
			t_file_descripter fd, int *end_status)
{
	int	i;
	int	local_status;

	local_status = 0;
	i = 0;
	while (token->command_line[i] != NULL)
	{
		if (handle_redirect(token->command_line, i, fd) == -1)
		{
			*end_status = 1;
			return (-1);
		}
		else if (ft_strncmp(token->command_line[i], "<<", 3) == 0)
		{
			local_status = here_doc(token->command_line[i + 1],
					env_lst, fd, end_status);
			if (local_status == 1)
				return (1);
		}
		i++;
	}
	return (local_status);
}
