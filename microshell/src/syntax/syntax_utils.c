/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:20:02 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 14:23:17 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	is_redirection(char *arg)
{
	if (ft_strncmp(arg, ">", 2) == 0
		|| ft_strncmp(arg, ">>", 3) == 0
		|| ft_strncmp(arg, "<", 2) == 0
		|| ft_strncmp(arg, "<<", 3) == 0)
		return (true);
	else
		return (false);
}

int	check_quotation(char *line)
{
	int	i;
	int	s_flag;
	int	d_flag;

	i = 0;
	s_flag = 0;
	d_flag = 0;
	while (line[i] != '\0')
	{
		if (s_flag == 0 && d_flag == 0 && line[i] == '\'')
			s_flag = 1;
		else if (s_flag == 0 && d_flag == 0 && line[i] == '\"')
			d_flag = 1;
		else if (s_flag == 1 && line[i] == '\'')
			s_flag = 0;
		else if (d_flag == 1 && line[i] == '\"')
			d_flag = 0;
		i++;
	}
	if (s_flag == 1 || d_flag == 1)
	{
		return (1);
	}
	return (0);
}

int	dir_permission(char *arg)
{
	struct stat	st;

	if (stat(arg, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
			return (126);
		}
		else if (access(arg, X_OK) != 0)
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
			return (126);
		}
	}
	return (0);
}

int	pipe_redirect_combination_error(char *arg, char *next)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_strncmp(&arg[i], ">|", 2) == 0
			|| ft_strncmp(&arg[i], "<|", 2) == 0
			|| ft_strncmp(&arg[i], "|<", 2) == 0
			|| ft_strncmp(&arg[i], "|>", 2) == 0
			|| ft_strncmp(&arg[i], ">>>", 3) == 0
			|| ft_strncmp(&arg[i], "<>", 2) == 0
			|| ft_strncmp(&arg[i], "><", 2) == 0)
		{
			ft_putendl_fd("syntax error", STDERR_FILENO);
			return (2);
		}
		if (is_redirection(arg) && next == NULL)
			return (ft_putendl_fd("syntax error", STDERR_FILENO), 2);
		i++;
	}
	return (0);
}

int	check_permission(t_command_lst *per_pipe)
{
	int	dir_perm;

	if (per_pipe->command_line[0] == NULL
		|| ft_strchr(per_pipe->command_line[0], '/') == NULL)
		return (0);
	dir_perm = dir_permission(per_pipe->command_line[0]);
	if (dir_perm != 0)
		return (dir_perm);
	if (access(per_pipe->command_line[0], F_OK) != 0)
	{
		ft_putstr_fd(per_pipe->command_line[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (127);
	}
	return (0);
}
