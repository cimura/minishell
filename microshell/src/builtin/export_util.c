/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:55:45 by sshimura          #+#    #+#             */
/*   Updated: 2024/11/26 14:26:31 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*get_max_key(t_env *env_lst)
{
	char	*max;
	t_env	*save;

	max = "";
	while (env_lst != NULL)
	{
		if (ft_strncmp(env_lst->key, max, 4096) > 0)
		{
			max = env_lst->key;
			save = env_lst;
		}
		env_lst = env_lst->next;
	}
	return (save);
}

t_env	*get_min_key(t_env *env_lst)
{
	char	*min;
	t_env	*save;

	min = get_max_key(env_lst)->key;
	while (env_lst != NULL)
	{
		if (ft_strncmp(env_lst->key, min, 4096) < 0)
		{
			min = env_lst->key;
			save = env_lst;
		}
		env_lst = env_lst->next;
	}
	return (save);
}

int	count_env_lst(t_env *env_lst)
{
	int	size;

	size = 0;
	while (env_lst != NULL)
	{
		size++;
		env_lst = env_lst->next;
	}
	return (size);
}

void	print_with_format(t_env *env_lst)
{
	if (ft_strncmp(env_lst->key, "_", 2) == 0)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env_lst->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd(env_lst->value, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
}
