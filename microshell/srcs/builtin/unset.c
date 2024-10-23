/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:05:59 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 18:59:11 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	unset(t_env *env_lst, char *key)
{
	t_env	*prev;

	prev = NULL;
	while (env_lst != NULL)
	{
		if (!ft_strncmp(env_lst->key, key, ft_strlen(env_lst->key) + 1))
		{
			prev->next = env_lst->next;
			free(env_lst->key);
			env_lst->key = NULL;
			free(env_lst->value);
			env_lst->value = NULL;
			free(env_lst);
			env_lst = NULL;
			return ;
		}
		prev = env_lst;
		env_lst = env_lst->next;
	}
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_env	*env_lst;

// 	env_lst = create_env_lst(envp);
// 	printf("--- Before ---\n\n");
// 	env(env_lst);
// 	if (argv[1])
// 		unset(env_lst, argv[1]);
// 	printf("--- After ---\n");
// 	env(env_lst);
// 	return (0);
// }
