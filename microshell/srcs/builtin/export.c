/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:50 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 18:57:29 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// // 1 -> not found 0 -> found
// int    ft_strstr(char *haystack, char *needle)
// {
//     int    i;

//     i = 0;
//     if (needle[i] == '\0' || !haystack || *haystack == '\0')
//         return (1);
//     while (needle[i] != '\0')
//     {
//         if (strchr(haystack, needle[i]) != NULL)
//             return (0);
//         i++;
//     }
//     return (1);
// }

int	check_keyname(char *arg)
{
	int		i;

	if (!(arg[0] >= 'A' && arg[0] <= 'Z') && arg[0] != '_'
		&& !(arg[0] >= 'a' && arg[0] <= 'z'))
		return (0);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!(arg[i] >= 'A' && arg[i] <= 'Z') && arg[i] != '_'
			&& !(arg[i] >= 'a' && arg[i] <= 'z')
			&& !(arg[i] >= '0' && arg[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

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

int	set_key_value_registered(t_env *new, char *arg)
{
	int	klen;
	int	vlen;

	vlen = ft_strlen(ft_strchr(arg, '=') + 1);
	klen = ft_strlen(arg) - vlen - 1;
	new->key = malloc(klen + 1);
	if (!new->key)
		return (free(new), new = NULL, 1);
	new->value = malloc(vlen + 1);
	if (!new->value)
		return (free(new->key), new->key = NULL, free(new), new = NULL, 1);
	new->key = ft_memmove(new->key, arg, klen);
	new->key[klen] = '\0';
	new->value = ft_memmove(new->value, (ft_strchr(arg, '=') + 1), vlen);
	new->value[vlen] = '\0';
	return (0);
}

int	export(char *arg, t_env *env_lst)
{
	t_env	*new;

	if (!arg || *arg == '\0')
		return (0);
	if (!ft_strchr(arg, '='))
		return (0);
	if (!check_keyname(arg))
		return (0);
	new = get_node_having_same_key(arg, env_lst);
	if (new)
	{
		if (set_key_value_registered(new, arg) != 0)
			return (1);
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (new == NULL)
			return (1);
		if (set_key_value_registered(new, arg) != 0)
			return (free(new), new = NULL, 1);
		new->next = NULL;
		env_lstadd_back(&env_lst, new);
	}
	return (0);
}

// int    main(int argc, char *argv[], char *envp[])
// {
// 	int	i;
// 	t_env	*head;
// 	t_env	*env_lst;

// 	if (argc != 2)
// 		return (1);
// 	env_lst = create_env_lst(envp);
// 	if (!env_lst)
// 		return (1);
// 	int status = export(argv[1], env_lst);
// 	head = env_lst;
// 	i = 0;
// 	while (env_lst != NULL)
// 	{
// 		printf("%s=%s\n", env_lst->key, env_lst->value);
// 		env_lst = env_lst->next;
// 	}
// 	env_lstclear(&head, free_env_node);
// 	return (status);
// }
