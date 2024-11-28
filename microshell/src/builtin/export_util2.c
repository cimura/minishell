/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:34:41 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/28 18:37:00 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_max_key(t_env *env_lst)
{
	char	*max;

	max = "";
	while (env_lst != NULL)
	{
		if (ft_strncmp(env_lst->key, max, 4096) > 0)
		{
			max = env_lst->key;
		}
		env_lst = env_lst->next;
	}
	return (max);
}

// t_env	*get_node_having_same_key(char *arg, t_env *env_lst)
// {
// 	while (env_lst != NULL)
// 	{
// 		if (ft_strncmp(arg, env_lst->key, ft_strlen(env_lst->key)) == 0
// 			&& (size_t)count_key_size(arg) == ft_strlen(env_lst->key))
// 			return (env_lst);
// 		env_lst = env_lst->next;
// 	}
// 	return (NULL);
// }

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
	if (env_lst->value)
	{
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(env_lst->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}
