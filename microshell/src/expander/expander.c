/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:24:16 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/03 23:37:25 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	handle_quotes_env_variable(t_env *env_lst,
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
		else if (ft_strncmp(command_line[i], "~", 2) == 0)
			expand = ft_strdup(get_value_from_key(env_lst, "HOME"));
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

int	expander(t_env *env_lst, t_command_lst *per_pipe, int end_status)
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
