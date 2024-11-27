/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:32:36 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/26 15:53:52 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	count_until_char(char *line, char *needle)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(needle, line[i]) != NULL)
			return (i);
		i++;
	}
	return (i);
}

int	count_key_size(char *line_ptr)
{
	int	size;

	size = 0;
	if (line_ptr[0] == '?')
		return (1);
	if (!(line_ptr[0] >= 'A' && line_ptr[0] <= 'Z') && line_ptr[0] != '_'
		&& !(line_ptr[0] >= 'a' && line_ptr[0] <= 'z'))
		return (size);
	while (line_ptr[size] != '\0' && line_ptr[size] != '=')
	{
		if (!(line_ptr[size] >= 'A' && line_ptr[size] <= 'Z')
			&& line_ptr[size] != '_'
			&& !(line_ptr[size] >= 'a' && line_ptr[size] <= 'z')
			&& !(line_ptr[size] >= '0' && line_ptr[size] <= '9'))
			return (size);
		size++;
	}
	return (size);
}

char	*get_value_from_key(t_env *env_lst, char *key)
{
	int	longer;

	if (ft_strlen(key) > ft_strlen(env_lst->key))
		longer = ft_strlen(key);
	else
		longer = ft_strlen(env_lst->key);
	while (env_lst != NULL)
	{
		if (ft_strncmp(key, env_lst->key, longer) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return ("");
}
