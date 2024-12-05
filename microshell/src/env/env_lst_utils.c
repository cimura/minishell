/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:45:02 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/05 16:45:35 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_lst.h"

char	*get_value_from_key(t_env *env_lst, char *key)
{
	int	longer;

	if (ft_strlen(key) > ft_strlen(env_lst->key))
		longer = ft_strlen(key);
	else
		longer = ft_strlen(env_lst->key);
	while (env_lst != NULL)
	{
		if (ft_strncmp(key, env_lst->key, longer + 1) == 0
			&& env_lst->value != NULL)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return ("");
}

bool	is_envnode_exist(t_env *env_lst, char *key)
{
	int	longer;

	if (ft_strlen(key) > ft_strlen(env_lst->key))
		longer = ft_strlen(key);
	else
		longer = ft_strlen(env_lst->key);
	while (env_lst != NULL)
	{
		if (ft_strncmp(key, env_lst->key, longer + 1) == 0
			&& env_lst->value != NULL)
			return (true);
		env_lst = env_lst->next;
	}
	return (false);
}
