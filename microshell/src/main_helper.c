/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:12:06 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/29 16:54:53 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_lst.h"
#include "exec.h"
#include "expander.h"
#include "lexer.h"
#include "signal_handler.h"
#include "utils.h"
#include "syntax.h"
#include "libft.h"

void	clear_exit(t_env *env_lst, t_token *token, int exit_status)
{
	env_lstclear(&env_lst);
	token_lstclear(&token);
	exit(exit_status);
}

int	handle_quotes_env_variable(t_env *env_lst,
	char **command_line, int end_status)
{
	int		i;
	char	*expand;
	char	*tmp;

	i = 0;
	while (command_line[i] != NULL)
	{
		if (command_line[i + 1] != NULL
			&& ft_strncmp(command_line[i], "<<", 3) == 0)
			expand = remove_quotes(command_line[++i]);
		else
		{
			tmp = expand_env_variable(env_lst, command_line[i], end_status);
			expand = remove_quotes(tmp);
			free(tmp);
		}
		if (expand == NULL)
			return (1);
		free(command_line[i]);
		command_line[i] = expand;
		i++;
	}
	return (0);
}

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe, int end_status)
{
	while (per_pipe != NULL)
	{
		if (handle_quotes_env_variable(env_lst, per_pipe->command_line,
				end_status) == 1)
			return (1);
		per_pipe = per_pipe->next;
	}
	return (0);
}
