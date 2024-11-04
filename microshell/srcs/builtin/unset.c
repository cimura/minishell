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

void	delete_env_from_lst(char *arg, t_env *env_lst)
{
	t_env	*prev;

	prev = NULL;
	while (env_lst != NULL)
	{
		if (!ft_strncmp(env_lst->key, arg, ft_strlen(env_lst->key) + 1))
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

void	unset(char **args, t_env *env_lst)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		delete_env_from_lst(args[i], env_lst);
		i++;
	}
}

//t_env	*get_node_having_same_key(char *arg, t_env *env_lst)
//{
//	while (env_lst != NULL)
//	{
//		if (ft_strncmp(arg, env_lst->key, ft_strlen(env_lst->key)) == 0)
//			return (env_lst);
//		env_lst = env_lst->next;
//	}
//	return (NULL);
//}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_env	*env_lst;

//	if (argc <= 1)
//		return (0);
// 	env_lst = create_env_lst(envp);

//	int	i = 1;
//	int	is_exist[argc - 1];
//	while (argv[i] != NULL)
//	{
//		if (get_node_having_same_key(argv[i], env_lst) == NULL)
//			is_exist[i - 1] = 0;
//		else
//			is_exist[i - 1] = 1;
//		i++;
//	}
//	// check
//	unset(&argv[1], env_lst);

//	i = 1;
//	while (argv[i] != NULL)
//	{
//		while (env_lst != NULL)
//		{
//			if (strcmp(env_lst->key, argv[i]) == 0) {
//	printf("\x1b[31mKO\x1b[0m: \x1b[33m%s\x1b[0m was not deleted.\n", argv[i]);
//	break ;
//	}
//			env_lst = env_lst->next;
//		}
//		if (is_exist[i - 1] == 1) {
//	printf("\x1b[32mOK\x1b[0m: \x1b[33m%s\x1b[0m was deleted.\n", argv[i]);
//	}
//		else {
//		printf("\x1b[32mOK\x1b[0m: \x1b[33m%s\x1b[0m is not exist.\n", argv[i]);
//	}
//		i++;
//	}

//	env_lstclear(&env_lst, free_env_node);
// 	return (0);
// }
