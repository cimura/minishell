/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:20:02 by cimy              #+#    #+#             */
/*   Updated: 2024/12/09 18:14:20 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include "utils.h"

#define SINGLE '\''
#define DOUBLE '\"'
#define OUT	'\0'

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
		if (s_flag == 0 && d_flag == 0 && line[i] == SINGLE)
			s_flag = 1;
		else if (s_flag == 0 && d_flag == 0 && line[i] == DOUBLE)
			d_flag = 1;
		else if (s_flag == 1 && line[i] == SINGLE)
			s_flag = 0;
		else if (d_flag == 1 && line[i] == DOUBLE)
			d_flag = 0;
		i++;
	}
	if (s_flag == 1 || d_flag == 1)
		return (1);
	return (0);
}

static int	check_redirection_token(char *arg, char *next, t_env *env_lst)
{
	if (is_redirection(arg))
	{
		if (next == NULL)
		{
			print_error_msg("", false, "", "syntax error");
			return (2);
		}
		else if (next[0] == '$' && \
			((!is_envnode_exist(env_lst, &next[1]) && \
					ft_strncmp(arg, "<<", 3)) || \
				(is_ifs_in_str(env_lst, get_value_from_key(env_lst, &next[1]))
					&& ft_strncmp(arg, "<<", 2))))
		{
			print_error_msg("", false, next, "ambiguous redirect");
			return (1);
		}
	}
	return (0);
}

static void	flag_manager(char c, char *is_in_quote)
{
	if (*is_in_quote == SINGLE && c == SINGLE)
		*is_in_quote = OUT;
	else if (*is_in_quote == DOUBLE && c == DOUBLE)
		*is_in_quote = OUT;
	else if (*is_in_quote == OUT && c == SINGLE)
		*is_in_quote = SINGLE;
	else if (*is_in_quote == OUT && c == DOUBLE)
		*is_in_quote = DOUBLE;
}

int	pipe_redirect_combination_error(char *arg, char *next, t_env *env_lst)
{
	int		i;
	int		redirect_status;
	char	is_in_quote;

	i = 0;
	is_in_quote = '\0';
	while (arg[i] != '\0')
	{
		flag_manager(arg[i], &is_in_quote);
		if (!is_in_quote && (ft_strncmp(&arg[i], ">|", 2) == 0
				|| ft_strncmp(&arg[i], "<|", 2) == 0
				|| ft_strncmp(&arg[i], "|<", 2) == 0
				|| ft_strncmp(&arg[i], "|>", 2) == 0
				|| ft_strncmp(&arg[i], ">>>", 3) == 0
				|| ft_strncmp(&arg[i], "<>", 2) == 0
				|| ft_strncmp(&arg[i], "><", 2) == 0))
			return (ft_putendl_fd("syntax error", STDERR_FILENO), 2);
		redirect_status = check_redirection_token(arg, next, env_lst);
		if (redirect_status != 0)
			return (redirect_status);
		i++;
	}
	return (0);
}
