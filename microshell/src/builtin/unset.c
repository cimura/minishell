/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:05:59 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/12 13:51:06 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	case_unset_head_node(t_env *env_lst)
{
	t_env	*next_node;
	t_env	*current;
	char	*key;
	char	*value;

	current = env_lst;
	next_node = current->next;
	key = ft_strdup(next_node->key);
	if (key == NULL)
		return (1);
	value = ft_strdup(next_node->value);
	if (value == NULL)
		return (free(key), 1);
	free(current->key);
	free(current->value);
	current->key = key;
	current->value = value;
	current->next = next_node->next;
	free(next_node->key);
	free(next_node->value);
	free(next_node);
	return (0);
}

static int	delete_env_from_lst(char *arg, t_env *env_lst)
{
	t_env	*prev;

	prev = NULL;
	while (env_lst != NULL)
	{
		if (ft_strncmp(env_lst->key, arg, ft_strlen(env_lst->key) + 1) == 0)
		{
			if (prev)
				prev->next = env_lst->next;
			else
				return (case_unset_head_node(env_lst));
			free(env_lst->key);
			free(env_lst->value);
			free(env_lst);
			return (0);
		}
		prev = env_lst;
		env_lst = env_lst->next;
	}
	return (0);
}

int	unset(char **args, t_env *env_lst)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (delete_env_from_lst(args[i], env_lst) != 0)
			return (1);
		i++;
	}
	return (0);
}

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

//	env_lstclear(&env_lst);
// 	return (0);
// }
