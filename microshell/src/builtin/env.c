/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:32:43 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/10 17:39:40 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env(t_env *env_lst)
{
	while (env_lst != NULL)
	{
		if (env_lst->value)
			printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
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
// 	env_lstclear(&head);
// }
