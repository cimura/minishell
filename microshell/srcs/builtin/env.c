/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:32:43 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 16:28:59 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env(t_env *env_lst)
{
	int	i;

	i = 0;
	while (env_lst != NULL)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;

// 	env_lst = create_env_lst(envp);
// 	if (!env_lst)
// 		return (1);
// 	head = env_lst;
// 	i = 0;

// 	env(env_lst);
// //   if (argc == 1)
// //     env_with_arg(NULL, NULL, env_lst, envp);
// //   else if (argc == 2)
// //     env_with_arg(argv[1], NULL, env_lst, envp);
// //   else if (argc == 3)
// //     env_with_arg(argv[1], argv[2], env_lst, envp);

// 	// while (env_lst != NULL)
// 	// {
// 	// 	printf("%s=%s\n", env_lst->key, env_lst->value);
// 	// 	env_lst = env_lst->next;
// 	// }
// 	env_lstclear(&head, free_env_node);
// }
