/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:50 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/03 16:58:40 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// // 1 -> not found 0 -> found
// int    ft_strstr(char *haystack, char *needle)
// { //     int    i;

//	 i = 0;
//	 if (needle[i] == '\0' || !haystack || *haystack == '\0')
//		 return (1);
//	 while (needle[i] != '\0')
//	 {
//		 if (strchr(haystack, needle[i]) != NULL)
//			 return (0);
//		 i++;
//	 }
//	 return (1);
// }

t_env	*get_node_having_same_key(char *arg, t_env *env_lst)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(arg, env_lst->key, ft_strlen(env_lst->key)) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_env	*create_new_env_node(char *arg)
{
	t_env	*new;
	int		klen;
	int		vlen;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	vlen = ft_strlen(ft_strchr(arg, '=') + 1);
	klen = ft_strlen(arg) - vlen - 1;
	new->key = malloc(klen + 1);
	if (!new->key)
		return (free(new), new = NULL, NULL);
	new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new), new = NULL, free(new->key), new->key = NULL, NULL);
	new->key = ft_memmove(new->key, arg, klen);
	new->key[klen] = '\0';
	new->value = ft_memmove(new->value, (ft_strchr(arg, '=') + 1), vlen);
	new->value[vlen] = '\0';
	new->next = NULL;
	return (new);
}

int	parse_argument(char *arg, int *status)
{
	int	i;

	if (arg[0] == '\0' || ft_strchr(arg, '=') == NULL)
		return (1);
	if (!(arg[0] >= 'A' && arg[0] <= 'Z') && arg[0] != '_'
		&& !(arg[0] >= 'a' && arg[0] <= 'z'))
	{
		*status = 1;
		return (1);
	}
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!(arg[i] >= 'A' && arg[i] <= 'Z') && arg[i] != '_'
			&& !(arg[i] >= 'a' && arg[i] <= 'z')
			&& !(arg[i] >= '0' && arg[i] <= '9'))
		{
			*status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	register_new_env(char *arg, t_env *env_lst)
{
	t_env	*target;

	target = get_node_having_same_key(arg, env_lst);
	if (target)
	{
		free(target->value);
		target->value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (target->value == NULL)
			return (1);
	}
	else
	{
		target = create_new_env_node(arg);
		if (target == NULL)
			return (1);
		env_lstadd_back(&env_lst, target);
	}
	return (0);
}

int	export(char **args, t_env *env_lst)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (parse_argument(args[i], &status) != 0)
		{
			i++;
			continue ;
		}
		if (register_new_env(args[i], env_lst) != 0)
		{
			status = 1;
			return (status);
		}
		i++;
	}
	return (status);
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;

// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 		return (1);
// 	int status = export(&argv[1], env_lst);
// 	head = env_lst;
// 	i = 0;
// 	while (env_lst)
// 	{
// 		printf("%s=%s\n", env_lst->key, env_lst->value);
// 		env_lst = env_lst->next;
// 	}
// 	env_lstclear(&head, free_env_node);
// 	return (status);
// }
