/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:32 by cimy              #+#    #+#             */
/*   Updated: 2024/11/27 13:42:27 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool is_redirection(char *arg)
{
	if (ft_strncmp(arg, ">", 2) == 0
		|| ft_strncmp(arg, ">>", 3) == 0
		|| ft_strncmp(arg, "<", 2) == 0
		|| ft_strncmp(arg, "<<", 3) == 0)
		return (true);
	else
		return (false);
}

static int	white_space(char check_chr)
{
	if (check_chr == ' ' || check_chr == '\t' || check_chr == '\n' || \
		check_chr == '\v' || check_chr == '\f' || check_chr == '\r')
		return (1);
	else
		return (0);
}

int check_quotation(char *line)
{
	int i;
	int s_flag;
	int d_flag;

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

int check_syntax_before_lexer(char *line)
{
	if (line[0] == '|' && (line[1] == '\0' || white_space(line[1])))
	{
		ft_putendl_fd("syntax error", STDERR_FILENO);
		return (1);
	}
	if (check_quotation(line) == 1)
	{
		ft_putendl_fd("syntax error", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_permission(t_token *token)
{
	struct stat	st;

	if (token->command_line[0]  == NULL || ft_strchr(token->command_line[0], '/') == NULL)
		return (0);
	if (stat(token->command_line[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(token->command_line[0], 2);
			ft_putendl_fd(": Is a directory", 2);
			return (126);
		}
		else if (access(token->command_line[0], X_OK) != 0)
		{
			ft_putstr_fd(token->command_line[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			return (126);
		}
	}
	if (access(token->command_line[0], F_OK) != 0)
	{
		ft_putstr_fd(token->command_line[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	return (0);
}

int check_syntax(t_token *token, t_env *env_lst)
{
	int i;
	int j;
	int	permission_result;
	(void)env_lst;

	while (token != NULL)
	{
		i = 0;
		if (token->command_line[0] == NULL)
		{
			ft_putendl_fd("syntax error", STDERR_FILENO);
			return (2);
		}
	permission_result = check_permission(token);
	if (permission_result != 0)
		return (permission_result);
	while (token->command_line[i] != NULL)
	{
		if (is_redirection(token->command_line[i]) && token->command_line[i + 1] == NULL)
		{
			ft_putendl_fd("syntax error", STDERR_FILENO);
			return (2);
		}
		j = 0;
		while (token->command_line[i][j] != '\0')
		{
			if (ft_strncmp(&token->command_line[i][j], ">|", 2) == 0
					|| ft_strncmp(&token->command_line[i][j], "<|", 2) == 0
					|| ft_strncmp(&token->command_line[i][j], "|<", 2) == 0
					|| ft_strncmp(&token->command_line[i][j], "|>", 2) == 0
					|| ft_strncmp(&token->command_line[i][j], ">>>", 3) == 0
					|| ft_strncmp(&token->command_line[i][j], "<>", 2) == 0
					|| ft_strncmp(&token->command_line[i][j], "><", 2) == 0)
			{
				ft_putendl_fd("syntax error", STDERR_FILENO);
				return (2);
			}
			j++;
		}
		i++;
	}
		token = token->next;
	}
	return (0);
}
