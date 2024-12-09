/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:32 by cimy              #+#    #+#             */
/*   Updated: 2024/12/09 18:23:03 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	is_all_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_whitespace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

int	check_syntax_before_parser(char *line, int *status)
{
	if (line[0] == '|' && (line[1] == '\0' || is_whitespace(line[1])))
	{
		print_error_msg("", false, "", "syntax error");
		*status = 2;
		return (CONTINUE);
	}
	if (check_quotation(line) == 1)
	{
		print_error_msg("", false, "", "syntax error");
		*status = 2;
		return (CONTINUE);
	}
	if (is_all_whitespace(line))
		return (CONTINUE);
	return (0);
}

int	check_syntax(t_command_lst *per_pipe, t_env *env_lst)
{
	int	i;
	int	ret;

	while (per_pipe != NULL)
	{
		i = 0;
		if (per_pipe->command_line[0] == NULL)
			return (ft_putendl_fd("syntax error", STDERR_FILENO), 2);
		while (per_pipe->command_line[i] != NULL)
		{
			ret = pipe_redirect_combination_error(per_pipe->command_line[i],
					per_pipe->command_line[i + 1], env_lst);
			if (ret != 0)
				return (ret);
			i++;
		}
		per_pipe = per_pipe->next;
	}
	return (0);
}
