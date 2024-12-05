/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:20:02 by cimy              #+#    #+#             */
/*   Updated: 2024/12/05 15:55:46 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include "utils.h"

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

static int	check_redirection_token(char *arg, char *next, t_env *env_lst)
{
	if (is_redirection(arg))
	{
		if (next == NULL)
		{
			print_error_msg(NULL, NULL,
				"syntax error near unexpected token `newline'");
			return (2);
		}
		else if (next[0] == '$' && !is_envnode_exist(env_lst, &next[1]))
		{
			print_error_msg(NULL, next, "ambiguous redirect");
			return (1);
		}
	}
	return (0);
}

int	pipe_redirect_combination_error(char *arg, char *next, t_env *env_lst)
{
	int	i;
	int	redirect_status;

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
		redirect_status = check_redirection_token(arg, next, env_lst);
		if (redirect_status != 0)
			return (redirect_status);
		// if (is_redirection(arg) && next == NULL)
		// 	return (ft_putendl_fd("syntax error", STDERR_FILENO), 2);
		i++;
	}
	return (0);
}
