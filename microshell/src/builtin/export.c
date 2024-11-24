/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:00:50 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/24 19:45:09 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_env	*create_new_env_node(char *arg)
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

static int	parse_argument(char *arg, int *status)
{
	int	i;

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
	if (arg[0] == '\0' || ft_strchr(arg, '=') == NULL)
		return (1);
	return (0);
}

static int	register_new_env(char *arg, t_env *env_lst)
{
	t_env	*target;

	target = env_lst;
	while (target != NULL)
	{
		if (ft_strncmp(arg, target->key, ft_strlen(target->key)) == 0)
			break ;
		target = target->next;
	}
	if (target == NULL)
	{
		target = create_new_env_node(arg);
		if (target == NULL)
			return (1);
		env_lstadd_back(&env_lst, target);
	}
	else
	{
		free(target->value);
		target->value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (target->value == NULL)
			return (1);
	}
	return (0);
}

void	no_args(t_env *env_lst)
{
	int		i;
	char	*old_min;
	t_env	*max_node;
	t_env	*head;
	t_env	*min_env_lst;

	head = env_lst;
	min_env_lst = env_lst;
	max_node = get_max_key(env_lst);
	old_min = "\0";
	i = 0;
	while (i < count_env_lst(env_lst))
	{
		min_env_lst->key = max_node;
		while (env_lst != NULL)
		{
			if (ft_strncmp(env_lst->key, old_min, 4096) > 0
				&& ft_strncmp(env_lst->key, max_node->key, 4096) < 0)
				min_env_lst = env_lst;
			env_lst = env_lst->next;
		}
		print_with_format(min_env_lst);
		env_lst = head;
		old_min = min_env_lst->key;
		i++;
	}
}

int	with_args(char **args, t_env *env_lst)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[i] != NULL)
	{
		if (parse_argument(args[i], &status) == 1)
		{
			if (status == 1)
				ft_putendl_fd(" not a valid identifier", STDERR_FILENO);
			i++;
			continue ;
		}
		if (register_new_env(args[i], env_lst) == 1)
			return (1);
		i++;
	}
	return (status);
}

int	export(char **args, t_env *env_lst)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (args[0] == NULL)
		no_args(env_lst);
	else
		status = with_args(args, env_lst);
	// while (args[i] != NULL)
	// {
	// 	if (parse_argument(args[i], &status) == 1)
	// 	{
	// 		if (status == 1)
	// 			ft_putendl_fd(" not a valid identifier", STDERR_FILENO);
	// 		i++;
	// 		continue ;
	// 	}
	// 	if (register_new_env(args[i], env_lst) == 1)
	// 		return (1);
	// 	i++;
	// }
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
// 	env_lstclear(&head);
// 	return (status);
// }
