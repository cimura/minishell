/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:24:16 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/08 19:28:02 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	if (s1 == NULL || s2 == NULL)
		return (1);
	n = ft_strlen(s1);
	i = ft_strlen(s2);
	if (n < i)
		n = i;
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	set_array_argument(char *expand, t_command_lst *per_pipe, int i)
{
	if (expand && ft_strcmp(per_pipe->command_line[i], expand) != 0)
		per_pipe->is_expanded[i] = true;
	if (expand == NULL)
		return (1);
	free(per_pipe->command_line[i]);
	per_pipe->command_line[i] = expand;
	return (0);
}

static int	handle_quotes_env_variable(t_env *env_lst,
	t_command_lst *per_pipe, int end_status)
{
	int		i;
	char	*expand;
	char	*tmp;

	i = 0;
	while (per_pipe->command_line[i] != NULL)
	{
		if (per_pipe->command_line[i + 1] != NULL
			&& ft_strncmp(per_pipe->command_line[i], "<<", 3) == 0)
			expand = remove_quotes(per_pipe->command_line[++i]);
		else if (ft_strncmp(per_pipe->command_line[i], "~", 2) == 0)
			expand = ft_strdup(get_value_from_key(env_lst, "HOME"));
		else
		{
			tmp = expand_env_variable(env_lst,
					per_pipe->command_line[i], end_status);
			expand = remove_quotes(tmp);
			free(tmp);
		}
		if (set_array_argument(expand, per_pipe, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	expander(t_env *env_lst, t_command_lst *per_pipe, int end_status)
{
	while (per_pipe != NULL)
	{
		if (handle_quotes_env_variable(env_lst, per_pipe,
				end_status) == 1)
			return (1);
		per_pipe = per_pipe->next;
	}
	return (0);
}
