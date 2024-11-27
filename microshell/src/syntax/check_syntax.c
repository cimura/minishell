/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:32 by cimy              #+#    #+#             */
/*   Updated: 2024/11/27 16:24:06 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	check_syntax_before_lexer(char *line)
{
	if (line[0] == '|' && (line[1] == '\0' || white_space(line[1])))
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

int	check_syntax(t_token *token)
{
	int	i;
	int	ret;

	while (token != NULL)
	{
		i = 0;
		if (token->command_line[0] == NULL)
			return (ft_putendl_fd("syntax error", STDERR_FILENO), 2);
		ret = check_permission(token);
		if (ret != 0)
			return (ret);
		while (token->command_line[i] != NULL)
		{
			ret = pipe_redirect_combination_error(token->command_line[i],
					token->command_line[i + 1]);
			if (ret != 0)
				return (ret);
			i++;
		}
		token = token->next;
	}
	return (0);
}
