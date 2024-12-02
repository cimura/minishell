/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:32 by cimy              #+#    #+#             */
/*   Updated: 2024/12/02 14:13:31 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	check_syntax_before_parser(char *line)
{
	if (line[0] == '|' && (line[1] == '\0' || is_whitespace(line[1])))
	{
		ft_putendl_fd("syntax error", STDERR_FILENO);
		return (2);
	}
	if (check_quotation(line) == 1)
	{
		ft_putendl_fd("syntax error", STDERR_FILENO);
		return (2);
	}
	return (0);
}

int	check_syntax(t_command_lst *per_pipe)
{
	int	i;
	int	ret;

	while (per_pipe != NULL)
	{
		i = 0;
		if (per_pipe->command_line[0] == NULL)
			return (ft_putendl_fd("syntax error", STDERR_FILENO), 2);
		ret = check_permission(per_pipe);
		if (ret != 0)
			return (ret);
		while (per_pipe->command_line[i] != NULL)
		{
			ret = pipe_redirect_combination_error(per_pipe->command_line[i],
					per_pipe->command_line[i + 1]);
			if (ret != 0)
				return (ret);
			i++;
		}
		per_pipe = per_pipe->next;
	}
	return (0);
}
